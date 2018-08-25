// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Tetris3DPlayerController.h"

ATetris3DPlayerController::ATetris3DPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
