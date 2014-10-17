#include "LeapMotionPrivatePCH.h"

ULeapImage::ULeapImage(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

ULeapImage::~ULeapImage()
{
}

//Not properly supported at this time
UTexture2D* ULeapImage::Texture8FromLeapImage(int32 SrcWidth, int32 SrcHeight, uint8* imageBuffer)
{
	// Create a 1-Channel texture
	UTexture2D* LeapTexture = UTexture2D::CreateTransient(SrcWidth, SrcHeight, PF_G8);

	// Lock the texture so it can be modified
	uint8* MipData = (uint8*)(LeapTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

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
	LeapTexture->PlatformData->Mips[0].BulkData.Unlock();
	LeapTexture->UpdateResource();

	return LeapTexture;
}

UTexture2D* ULeapImage::Texture32FromLeapImage(int32 SrcWidth, int32 SrcHeight, uint8* imageBuffer)
{
	// Lock the texture so it can be modified
	if (!imagePointer || !imagePointer->IsValidLowLevel())
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
UTexture2D* ULeapImage::TextureFFromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer)
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

UTexture2D* ULeapImage::Texture32FromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer)
{
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

bool ULeapImage::validImagePointer()
{
	//Make sure we're valid
	if (!IsValid) return false;
	if (imagePointer == NULL)
	{
		if (Width == 0 && Height == 0)
		{
			UE_LOG(LogClass, Error, TEXT("Warning! Leap Image SDK access is denied, please enable image support from the Leap Controller."));
			return false;
		}
		imagePointer = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
	}
	return true;
}

UTexture2D* ULeapImage::Texture()
{
	if (!validImagePointer())
		return NULL;

	return Texture32FromLeapImage(Width, Height, (uint8*)_leapImage.data());
}

UTexture2D* ULeapImage::R8Texture()
{
	if (!validImagePointer())	//doesn't use the image pointer, but this check is still useful
		return NULL;

	return Texture8FromLeapImage(Width, Height, (uint8*)_leapImage.data());
}

//Note that distortion is still sometimes unstables
UTexture2D* ULeapImage::Distortion()
{
	if (!IsValid) return NULL;
	if (distortionPointer == NULL)
	{
		if (Width == 0 && Height == 0)
		{
			UE_LOG(LogClass, Error, TEXT("Warning! Leap Image SDK access is denied, please enable image support from the Leap Controller."));
			return NULL;
		}
		distortionPointer = UTexture2D::CreateTransient(DistortionWidth / 2, DistortionHeight, PF_B8G8R8A8);
	}
	return Texture32FromLeapDistortion(DistortionWidth, DistortionHeight, (float*)_leapImage.distortion());
}


FVector ULeapImage::Rectify(FVector uv) const
{
	Leap::Vector vect = Leap::Vector(uv.X, uv.Y, uv.Z);
	vect = _leapImage.rectify(vect);
	return FVector(vect.x, vect.y, vect.z);
}

FVector ULeapImage::Warp(FVector xy) const
{
	Leap::Vector vect = Leap::Vector(xy.X, xy.Y, xy.Z);
	vect = _leapImage.warp(vect);
	return FVector(vect.x, vect.y, vect.z);
}

void ULeapImage::setLeapImage(const Leap::Image &LeapImage)
{
	_leapImage = LeapImage;

	DistortionHeight = _leapImage.distortionHeight();
	DistortionWidth = _leapImage.distortionWidth();
	Height = _leapImage.height();
	Id = _leapImage.id();
	IsValid = _leapImage.isValid();
	RayOffsetX = _leapImage.rayOffsetX();
	RayOffsetY = _leapImage.rayOffsetY();
	RayScaleX = _leapImage.rayScaleX();
	RayScaleY = _leapImage.rayScaleY();
	Width = _leapImage.width();
}