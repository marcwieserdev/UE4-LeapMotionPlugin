#include "LeapMotionPrivatePCH.h"

ULeapImage::ULeapImage(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

ULeapImage::~ULeapImage()
{
}

//Not properly supported at this time
/*UTexture2D* ULeapImage::LeapDataToTexture(const int32 SrcWidth, const int32 SrcHeight, const TArray<int8> &SrcData, const bool UseAlpha)
{
	// Create the texture
	UTexture2D* LeapTexture = UTexture2D::CreateTransient(SrcWidth, SrcHeight, PF_B8G8R8A8);

	// Lock the texture so it can be modified
	
	//Todo: fix error that occurs here
	/*uint8* MipData = (uint8*)(LeapTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	//FColor* MipData = static_cast<FColor*>(LeapTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	//FColor* MipData = static_cast<FColor*>(LeapTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	// Create base mip.
	uint8* DestPtr = NULL;
	//FColor* DestPtr = NULL;
	const int8* SrcPtr = NULL;
	//const FColor* SrcPtr = NULL;

	for (int32 y = 0; y<SrcHeight; y++)
	{
		DestPtr = &MipData[(SrcHeight - 1 - y) * SrcWidth * sizeof(FColor)];
		SrcPtr = (&SrcData[(SrcHeight - 1 - y) * SrcWidth]);//const_cast<FColor*>
		for (int32 x = 0; x<SrcWidth; x++)
		{
			*DestPtr++ = *SrcPtr;
			*DestPtr++ = *SrcPtr;
			*DestPtr++ = *SrcPtr;
			if (UseAlpha)
			{
				*DestPtr++ = *SrcPtr;
			}
			else
			{
				*DestPtr++ = 0xFF;	//(FColor)
			}
			SrcPtr++;
		}
	}

	// Unlock the texture
	LeapTexture->PlatformData->Mips[0].BulkData.Unlock();
	LeapTexture->UpdateResource();
	return LeapTexture;
}*/

/*UTexture2D* ULeapImage::GetTexture()
{
	if (!IsValid()) return 0;

	TArray<int8> imageData;
	int width = Width();
	int height = Height();
	//This is a copy!, terrible performance-wise. See if you can't to a cast
	for (int32 i = 0; i < width * height; i++)
	{
		imageData.Add(_leapImage.data()[i]);
	}

	return LeapDataToTexture(Width(), Height(), imageData, false);
}*/

const float* ULeapImage::Distortion() const
{
	return (_leapImage.distortion());
}

int ULeapImage::DistortionHeight() const
{
	return (_leapImage.distortionHeight());
}

int ULeapImage::DistortionWidth() const
{
	return (_leapImage.distortionWidth());
}

int ULeapImage::Height()
{
	return (_leapImage.height());
}

int32 ULeapImage::Id() const
{
	return (_leapImage.id());
}

bool ULeapImage::IsValid() const
{
	return (_leapImage.isValid());
}

float ULeapImage::RayOffsetX() const
{
	return (_leapImage.rayOffsetX());
}


float ULeapImage::RayOffsetY() const
{
	return (_leapImage.rayOffsetY());
}

float ULeapImage::RayScaleX() const
{
	return (_leapImage.rayScaleX());
}

float ULeapImage::RayScaleY() const
{
	return (_leapImage.rayScaleY());
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

int ULeapImage::Width()
{
	return (_leapImage.width());
}

void ULeapImage::setLeapImage(const Leap::Image &LeapImage)
{
	_leapImage = LeapImage;
}