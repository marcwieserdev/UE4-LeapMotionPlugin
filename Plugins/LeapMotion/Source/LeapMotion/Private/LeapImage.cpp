#include "LeapMotionPrivatePCH.h"

class PrivateLeapImage
{
public:
	~PrivateLeapImage()
	{
		if (!cleanupCalled)
		Cleanup();
	}
	void Cleanup()
	{
		//Ensures our rooted objects are unrooted so they can be GC'd
		if (imagePointer)
			imagePointer->RemoveFromRoot();
		if (imageR8Pointer)
			imageR8Pointer->RemoveFromRoot();
		if (distortionPointer)
			distortionPointer->RemoveFromRoot();
		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::Image leapImage;

	UTexture2D* imagePointer = NULL;
	UTexture2D* imageR8Pointer = NULL;
	UTexture2D* distortionPointer = NULL;

	UTexture2D* validImagePointer(UTexture2D* pointer, int32 pWidth, int32 pHeight, EPixelFormat format, bool gammaCorrectionUsed = true);

	UTexture2D* Texture8FromLeapImage(int32 SrcWidth, int32 SrcHeight, uint8* imageBuffer);
	UTexture2D* Texture32FromLeapImage(int32 SrcWidth, int32 SrcHeight, uint8* imageBuffer);
	UTexture2D* Texture32FromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer);		//optimized, requires shader channel flipping
	UTexture2D* Texture32PrettyFromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer);	//unoptimized roughly +1ms
	UTexture2D* Texture128FromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer);		//4x float 32
	UTexture2D* TextureFFromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer);
	
	int32 invalidSizesReported = 0;
	bool ignoreTwoInvalidSizesDone = false;
	ULeapImage* self;
};

ULeapImage::ULeapImage(const FObjectInitializer &init) : UObject(init), _private(new PrivateLeapImage())
{
	_private->self = this;
}

ULeapImage::~ULeapImage()
{
	delete _private;
}

void ULeapImage::CleanupRootReferences()
{
	_private->Cleanup();
	this->RemoveFromRoot();
}


UTexture2D* PrivateLeapImage::validImagePointer(UTexture2D* pointer, int32 pWidth, int32 pHeight, EPixelFormat format, bool gammaCorrectionUsed)
{
	//Make sure we're valid
	if (!self->IsValid) 
	{
		UE_LOG(LeapPluginLog, Error, TEXT("Warning! Invalid Image."));
		return NULL;
	}
	//Instantiate the texture if needed
	if (pointer == nullptr)
	{
		if (pWidth == 0 || pHeight == 0)
		{
			//Spit out only valid errors, two size 0 textures will be attempted per pointer,
			//unable to filter the messages out without this (or a pointer to Leap Controller, but this uses less resources).
			if (ignoreTwoInvalidSizesDone)
			{
				UE_LOG(LeapPluginLog, Error, TEXT("Warning! Leap Image SDK access is denied, please enable image support from the Leap Controller before events emit (e.g. at BeginPlay)."));
			}
			else
			{
				invalidSizesReported++;

				if (invalidSizesReported == 2)
				{
					ignoreTwoInvalidSizesDone = true;
				}
			}
			
			return nullptr;
		}
		UE_LOG(LeapPluginLog, Log, TEXT("Created Leap Image Texture Sized: %d, %d, format %d"), pWidth, pHeight, (int)format);
		pointer = UTexture2D::CreateTransient(pWidth, pHeight, format); //PF_B8G8R8A8
		
		//change texture settings
		if (!gammaCorrectionUsed)
			pointer->SRGB = 0;
		pointer->SetFlags(RF_RootSet);	//to support more than one leap component, the pointer shouldn't be reclaimed by GC
	}

	//If the size changed, recreate the image (NB: GC may release the platform data in which case we need to recreate it (since 4.7)
	if (!UtilityPointerIsValid(pointer->PlatformData) ||
		pointer->PlatformData->SizeX != pWidth ||
		pointer->PlatformData->SizeY != pHeight)
	{
		UE_LOG(LeapPluginLog, Log, TEXT("ReCreated Leap Image Texture Sized: %d, %d. Old Size: %d, %d"), pWidth, pHeight, pointer->PlatformData->SizeX, pointer->PlatformData->SizeY);
		//pointer->ConditionalBeginDestroy();
		pointer = UTexture2D::CreateTransient(pWidth, pHeight, format);
	}
	return pointer;
}

//Single Channel texture
UTexture2D* PrivateLeapImage::Texture8FromLeapImage(int32 SrcWidth, int32 SrcHeight, uint8* imageBuffer)
{
	// Lock the texture so it can be modified
	if (imageR8Pointer == NULL)
		return NULL;

	// Lock the texture so it can be modified
	uint8* MipData = static_cast<uint8*>(imageR8Pointer->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	// Create base mip.
	uint8* DestPtr = NULL;
	uint8* SrcPtr = NULL;

	for (int32 y = 0; y<SrcHeight; y++)
	{
		DestPtr = &MipData[(SrcHeight - 1 - y) * SrcWidth * sizeof(uint8)];
		SrcPtr = (&imageBuffer[(SrcHeight - 1 - y) * SrcWidth]);
		for (int32 x = 0; x<SrcWidth; x++)
		{
			*DestPtr++ = *SrcPtr;
			SrcPtr++;
		}
	}

	// Unlock the texture
	imageR8Pointer->PlatformData->Mips[0].BulkData.Unlock();
	imageR8Pointer->UpdateResource();

	return imageR8Pointer;
}

//Grayscale average texture
UTexture2D* PrivateLeapImage::Texture32FromLeapImage(int32 SrcWidth, int32 SrcHeight, uint8* imageBuffer)
{
	// Lock the texture so it can be modified
	if (imagePointer == NULL)
		return NULL;

	uint8* MipData = static_cast<uint8*>(imagePointer->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	
	// Create base mip.
	uint8* DestPtr = NULL;
	const uint8* SrcPtr = NULL;

	for (int32 y = 0; y<SrcHeight; y++)
	{
		DestPtr = &MipData[(SrcHeight - 1 - y) * SrcWidth * sizeof(FColor)];
		SrcPtr = const_cast<uint8*>(&imageBuffer[(SrcHeight - 1 - y) * SrcWidth]);
		for (int32 x = 0; x<SrcWidth; x++)
		{
			//Grayscale, copy to all channels
			*DestPtr++ = *SrcPtr;
			*DestPtr++ = *SrcPtr;
			*DestPtr++ = *SrcPtr;
			*DestPtr++ = 0xFF;
			SrcPtr++;
		}
	}

	// Unlock the texture
	imagePointer->PlatformData->Mips[0].BulkData.Unlock();
	imagePointer->UpdateResource();

	return imagePointer;
}

//Lossless distortion map with no surplus channels, still not working properly, use the 128bit texture instead.
/*UTexture2D* PrivateLeapImage::TextureFFromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer)
{
	// Lock the texture so it can be modified
	if (distortionPointer == NULL)
		return NULL;

	int32 DestWidth = SrcWidth / 2; // Put 2 floats in the R and G channels
	int32 DestHeight = SrcHeight;

	// Lock the texture so it can be modified
	float* MipData = static_cast<float*>(distortionPointer->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	// Create base mip.
	float* DestPtr = NULL;
	const float* SrcPtr = imageBuffer;
	DestPtr = MipData;
	int32 length = SrcWidth * SrcHeight;

	for (int d = 0; d < length; d += 2)
	{
		float dX = imageBuffer[d];
		float dY = imageBuffer[d + 1];
		int destIndex = d * 2;

		//R
		DestPtr[destIndex] = dX;

		//G
		DestPtr[destIndex + 1] = dY;
	}

	// Unlock the texture
	distortionPointer->PlatformData->Mips[0].BulkData.Unlock();
	distortionPointer->UpdateResource();

	return distortionPointer;
}*/

//This gives a good looking distortion but it does not cull invalid values nor does it flip the V channel to UE format
//32bit, 8 per channel. Downsampled.
UTexture2D* PrivateLeapImage::Texture32PrettyFromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer)
{
	// Lock the texture so it can be modified
	if (distortionPointer == NULL)
		return NULL;

	int32 DestWidth = SrcWidth / 2; // Put 2 floats in the R and G channels
	int32 DestHeight = SrcHeight;

	// Lock the texture so it can be modified
	uint8* MipData = static_cast<uint8*>(distortionPointer->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	// Create base mip.
	uint8* DestPtr = NULL;
	const float* SrcPtr = imageBuffer;
	DestPtr = MipData;

	for (int d = 0; d < SrcWidth * SrcHeight; d += 2)
	{
		float dX = imageBuffer[d];
		float dY = imageBuffer[d + 1];
		int destIndex = d * 2;

		if (!((dX < 0) || (dX > 1)) && !((dY < 0) || (dY > 1))) {
			//R
			DestPtr[destIndex] = (uint8)FMath::Clamp<int32>(FMath::TruncToInt(dX *255.f), 0, 255);

			//G
			DestPtr[destIndex + 1] = (uint8)FMath::Clamp<int32>(255 - FMath::TruncToInt(dY *255.f), 0, 255);

			//B
			DestPtr[destIndex + 2] = 0;

			//A
			DestPtr[destIndex + 3] = 255;

			//if (d == (SrcHeight / 2) * SrcWidth + (SrcWidth / 2))
			//	UE_LOG(LeapPluginLog, Log, TEXT("(%d, %d, %d, %d), (%1.3f,%1.3f) @pos: %d"), DestPtr[destIndex], DestPtr[destIndex + 1], DestPtr[destIndex + 2], DestPtr[destIndex + 3],dX, dY, d);
		}
		else{
			//R
			DestPtr[destIndex] = 0;
			
			//G
			DestPtr[destIndex + 1] = 0;

			//B
			DestPtr[destIndex + 2] = 255;

			//A
			DestPtr[destIndex + 3] = 255;
		}
	}

	// Unlock the texture
	distortionPointer->PlatformData->Mips[0].BulkData.Unlock();
	distortionPointer->UpdateResource();

	return distortionPointer;
}

//Optimized 32bit format, downsampled to 8bits per channel.
UTexture2D* PrivateLeapImage::Texture32FromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer)
{
	// Lock the texture so it can be modified
	if (distortionPointer == NULL)
		return NULL;

	int32 DestWidth = SrcWidth / 2; // Put 2 floats in the R and G channels
	int32 DestHeight = SrcHeight;

	// Lock the texture so it can be modified
	uint8* MipData = static_cast<uint8*>(distortionPointer->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	// Create base mip.
	uint8* DestPtr = NULL;
	const float* SrcPtr = imageBuffer;
	DestPtr = MipData;
	int32 length = SrcWidth * SrcHeight;

	for (int d = 0; d < length; d += 2)
	{
		float dX = imageBuffer[d];
		float dY = imageBuffer[d + 1];
		int destIndex = d * 2;

		//R
		DestPtr[destIndex] = (uint8)(dX * 0xFF); //(uint8)FMath::Clamp<int32>(FMath::TruncToInt(dX *255.f), 0, 255);

		//G
		DestPtr[destIndex + 1] = (uint8)(dY * 0xFF); // (uint8)FMath::Clamp<int32>(255 - FMath::TruncToInt(dY *255.f), 0, 255);

		//B
		DestPtr[destIndex + 2] = 0x00;

		//A
		DestPtr[destIndex + 3] = 0xFF;
	}

	// Unlock the texture
	distortionPointer->PlatformData->Mips[0].BulkData.Unlock();
	distortionPointer->UpdateResource();

	return distortionPointer;
}

//Optimized 128bit format, one float per channel, two channels unused but the function works as expected.
UTexture2D* PrivateLeapImage::Texture128FromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer)
{
	// Lock the texture so it can be modified
	if (distortionPointer == NULL)
		return NULL;

	int32 DestWidth = SrcWidth / 2; // Put 2 floats in the R and G channels
	int32 DestHeight = SrcHeight;

	// Lock the texture so it can be modified
	float* MipData = static_cast<float*>(distortionPointer->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	// Create base mip.
	float* DestPtr = NULL;
	const float* SrcPtr = imageBuffer;
	DestPtr = MipData;
	int32 length = SrcWidth * SrcHeight;

	for (int d = 0; d < length; d += 2)
	{
		float dX = imageBuffer[d];
		float dY = imageBuffer[d + 1];
		int destIndex = d * 2;

		//R
		DestPtr[destIndex] = dX;

		//G
		DestPtr[destIndex + 1] = dY;

		//B
		DestPtr[destIndex + 2] = 0.f;

		//A
		DestPtr[destIndex + 3] = 0.f;
	}

	// Unlock the texture
	distortionPointer->PlatformData->Mips[0].BulkData.Unlock();
	distortionPointer->UpdateResource();

	return distortionPointer;
}

UTexture2D* ULeapImage::Texture()
{
	_private->imagePointer = _private->validImagePointer(_private->imagePointer, Width, Height, PF_B8G8R8A8);
	
	return _private->Texture32FromLeapImage(Width, Height, (uint8*)_private->leapImage.data());
}

UTexture2D* ULeapImage::R8Texture()
{
	_private->imageR8Pointer = _private->validImagePointer(_private->imageR8Pointer, Width, Height, PF_G8);

	return _private->Texture8FromLeapImage(Width, Height, (uint8*)_private->leapImage.data());
}

UTexture2D* ULeapImage::Distortion()
{
	//_private->distortionPointer = _private->validImagePointer(_private->distortionPointer, DistortionWidth / 2, DistortionHeight, PF_R8G8B8A8, false);	//8bit
	_private->distortionPointer = _private->validImagePointer(_private->distortionPointer, DistortionWidth / 2, DistortionHeight, PF_A32B32G32R32F);		//32bit per channel
	
	//return _private->Texture32FromLeapDistortion(DistortionWidth, DistortionHeight, (float*)_private->leapImage.distortion());	
	return _private->Texture128FromLeapDistortion(DistortionWidth, DistortionHeight, (float*)_private->leapImage.distortion());
}

UTexture2D* ULeapImage::DistortionUE()
{
	_private->distortionPointer = _private->validImagePointer(_private->distortionPointer, DistortionWidth / 2, DistortionHeight, PF_R8G8B8A8);

	return _private->Texture32PrettyFromLeapDistortion(DistortionWidth, DistortionHeight, (float*)_private->leapImage.distortion());
}


FVector ULeapImage::Rectify(FVector uv) const
{
	Leap::Vector vect = Leap::Vector(uv.X, uv.Y, uv.Z);
	vect = _private->leapImage.rectify(vect);
	return FVector(vect.x, vect.y, vect.z);
}

FVector ULeapImage::Warp(FVector xy) const
{
	Leap::Vector vect = Leap::Vector(xy.X, xy.Y, xy.Z);
	vect = _private->leapImage.warp(vect);
	return FVector(vect.x, vect.y, vect.z);
}

void ULeapImage::setLeapImage(const Leap::Image &LeapImage)
{
	_private->leapImage = LeapImage;

	DistortionHeight = _private->leapImage.distortionHeight();
	DistortionWidth = _private->leapImage.distortionWidth();
	Height = _private->leapImage.height();
	Id = _private->leapImage.id();
	IsValid = _private->leapImage.isValid();
	RayOffsetX = _private->leapImage.rayOffsetX();
	RayOffsetY = _private->leapImage.rayOffsetY();
	RayScaleX = _private->leapImage.rayScaleX();
	RayScaleY = _private->leapImage.rayScaleY();
	Width = _private->leapImage.width();
}