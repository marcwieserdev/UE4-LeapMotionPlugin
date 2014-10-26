#include "LeapMotionPrivatePCH.h"

class PrivateLeapImage
{
public:
	Leap::Image leapImage;

	UTexture2D* imagePointer = NULL;
	UTexture2D* imageR8Pointer = NULL;
	UTexture2D* distortionPointer = NULL;

	UTexture2D* validImagePointer(UTexture2D* pointer, int32 pWidth, int32 pHeight, EPixelFormat format);

	UTexture2D* Texture8FromLeapImage(int32 SrcWidth, int32 SrcHeight, uint8* imageBuffer);
	UTexture2D* Texture32FromLeapImage(int32 SrcWidth, int32 SrcHeight, uint8* imageBuffer);
	UTexture2D* Texture32FromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer);
	UTexture2D* TextureFFromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer);
	
	int32 invalidSizesReported = 0;
	bool ignoreTwoInvalidSizesDone = false;
	ULeapImage* self;
};

ULeapImage::ULeapImage(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateLeapImage())
{
	_private->self = this;
}

ULeapImage::~ULeapImage()
{
	delete _private;
}


UTexture2D* PrivateLeapImage::validImagePointer(UTexture2D* pointer, int32 pWidth, int32 pHeight, EPixelFormat format)
{
	//Make sure we're valid
	if (!self->IsValid) 
	{
		UE_LOG(LogClass, Error, TEXT("Warning! Invalid Image."));
		return NULL;
	}
	//Instantiate the texture if needed
	if (pointer == NULL)
	{
		if (pWidth == 0 || pHeight == 0)
		{
			//Spit out only valid errors, two size 0 textures will be attempted per pointer,
			//unable to filter the messages out without this (or a pointer to Leap Controller, but this uses less resources).
			if (ignoreTwoInvalidSizesDone)
			{
				UE_LOG(LogClass, Error, TEXT("Warning! Leap Image SDK access is denied, please enable image support from the Leap Controller before events emit (e.g. at BeginPlay)."));
			}
			else
			{
				invalidSizesReported++;

				if (invalidSizesReported == 2)
				{
					ignoreTwoInvalidSizesDone = true;
				}
			}
			
			return NULL;
		}
		UE_LOG(LeapPluginLog, Log, TEXT("Created Leap Image Texture Sized: %d, %d."), pWidth, pHeight);
		pointer = UTexture2D::CreateTransient(pWidth, pHeight, format); //PF_B8G8R8A8
	}
	//If the size changed, recreate the image
	if (pointer->PlatformData->SizeX != pWidth ||
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

/*Lossless distortion map attempts so far no good
UTexture2D* PrivateLeapImage::TextureFFromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer)
{
	int32 DestWidth = SrcWidth/2; // Put 2 floats in the R and G channels
	int32 DestHeight = SrcHeight;


	// Create the texture
	UTexture2D* LeapTexture = UTexture2D::CreateTransient(DestWidth, DestHeight, PF_A32B32G32R32F);

	// Lock the texture so it can be modified
	float* MipData = static_cast<float*>(LeapTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	// Create base mip.
	float* DestPtr = NULL;
	const float* SrcPtr = NULL;
	for (int32 y = 0; y<SrcHeight; y++)
	{
		DestPtr = &MipData[(DestHeight - 1 - y) * DestWidth * sizeof(float)*2];
		SrcPtr = const_cast<float*>(&imageBuffer[(SrcHeight - 1 - y) * SrcWidth]);
		for (int32 x = 0; x<SrcWidth; x++)
		{
			*DestPtr++ = 1.f;						//Full 255 alpha
			*DestPtr++ = 0.f;						//Black
			*DestPtr++ = (float)*SrcPtr++;//(uint8)(*SrcPtr++ * 0xFF); //Scale the float (0.0..1.0) to a uint8 (0..255)
			*DestPtr++ = (float)*SrcPtr++;//(uint8)(*SrcPtr++ * 0xFF);
		}
	}

	// Unlock the texture
	LeapTexture->PlatformData->Mips[0].BulkData.Unlock();
	LeapTexture->UpdateResource();

	return LeapTexture;
}*/

UTexture2D* PrivateLeapImage::Texture32FromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer)
{
	// Lock the texture so it can be modified
	if (distortionPointer == NULL)
		return NULL;

	int32 DestWidth = SrcWidth /2; // Put 2 floats in the R and G channels
	int32 DestHeight = SrcHeight;

	// Lock the texture so it can be modified
	uint8* MipData = static_cast<uint8*>(distortionPointer->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	// Create base mip.
	uint8* DestPtr = NULL;
	const float* SrcPtr = NULL;
	for (int32 y = 0; y<SrcHeight; y++)
	{
		DestPtr = &MipData[(DestHeight - 1 - y) * DestWidth * sizeof(FColor)];
		SrcPtr = const_cast<float*>(&imageBuffer[(SrcHeight - 1 - y) * SrcWidth]);
		for (int32 x = 0; x<SrcWidth; x++)
		{

			*DestPtr++ = (uint8)(*SrcPtr++ * 0xFF);	//Scale floats
			*DestPtr++ = (uint8)(*SrcPtr++ * 0xFF);
			*DestPtr++ = (uint8)0x00;						//Black
			*DestPtr++ = (uint8)0xFF;						//Full 255 alpha
		}
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
	_private->distortionPointer = _private->validImagePointer(_private->distortionPointer, DistortionWidth / 2, DistortionHeight, PF_B8G8R8A8);

	return _private->Texture32FromLeapDistortion(DistortionWidth, DistortionHeight, (float*)_private->leapImage.distortion());
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