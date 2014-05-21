// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../Public/ILeapMotion.h"

/**
 * The public interface to this module.  In most cases, this interface is only public to sibling modules 
 * within this plugin.
 */
class FLeapMotion : public ILeapMotion
{
public:

	virtual void StartupModule() OVERRIDE;
	virtual void ShutdownModule() OVERRIDE;
};
