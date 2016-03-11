// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "LeapMotionPublicPCH.h"
#include "ILeapMotionPlugin.h"
#include "IInputDeviceModule.h"



/**
 * The public interface to this module.  In most cases, this interface is only public to sibling modules 
 * within this plugin.
 */
class LEAPMOTION_API ILeapMotionPlugin : public IInputDeviceModule
{

public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline ILeapMotionPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked< ILeapMotionPlugin >( "LeapMotion" );
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "LeapMotion" );
	}

	//These are typically called by a wrapped class such as LeapController (Actor Component)

	/** Get raw reference to the data and settings toggles*/
	virtual struct LeapControllerData* ControllerData(){ return nullptr; };
	
	/** Attach an event delegate to the leap input device loop*/
	virtual void AddEventDelegate(UObject* EventDelegate) {};

	/** Remove an event delegate from the leap input device loop*/
	virtual void RemoveEventDelegate(UObject* EventDelegate) {};
};

