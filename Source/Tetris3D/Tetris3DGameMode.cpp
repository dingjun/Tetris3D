// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Tetris3DGameMode.h"
#include "Tetris3DPlayerController.h"
#include "Tetris3DPawn.h"

ATetris3DGameMode::ATetris3DGameMode()
{
	// no pawn by default
	DefaultPawnClass = ATetris3DPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ATetris3DPlayerController::StaticClass();
}
