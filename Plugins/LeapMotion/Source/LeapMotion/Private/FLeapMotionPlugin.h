// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "LeapMotionPrivatePCH.h"
#include "../Public/ILeapMotionPlugin.h"

/**
 * The public interface to this module.  In most cases, this interface is only public to sibling modules 
 * within this plugin.
 */
class FLeapMotionPlugin : public ILeapMotionPlugin
{
public:
	virtual TSharedPtr< class IInputDevice > CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler);

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual struct LeapControllerData* ControllerData() override;
	virtual void AddEventDelegate(UObject* EventDelegate) override;
	virtual void RemoveEventDelegate(UObject* EventDelegate) override;

	TSharedPtr< class FLeapMotionInputDevice > LeapInputDevice;
};
