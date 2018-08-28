// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Tetris3DPlayerController.h"
#include "Tetris3DSpawner.h"
#include "Engine.h"

ATetris3DPlayerController::ATetris3DPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATetris3DPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());

  TActorIterator<ATetris3DSpawner> ActorIteratorSpawner(GetWorld());
  Spawner = *ActorIteratorSpawner;
}

void ATetris3DPlayerController::SetupInputComponent()
{
  Super::SetupInputComponent();

  EnableInput(this);
  InputComponent->BindAction("MoveLeft", EInputEvent::IE_Pressed, this, &ATetris3DPlayerController::MoveLeft);
  InputComponent->BindAction("MoveLeft", EInputEvent::IE_Repeat, this, &ATetris3DPlayerController::MoveLeft);
  InputComponent->BindAction("MoveRight", EInputEvent::IE_Pressed, this, &ATetris3DPlayerController::MoveRight);
  InputComponent->BindAction("MoveRight", EInputEvent::IE_Repeat, this, &ATetris3DPlayerController::MoveRight);
  InputComponent->BindAction("MoveDown", EInputEvent::IE_Pressed, this, &ATetris3DPlayerController::MoveDown);
  InputComponent->BindAction("MoveDown", EInputEvent::IE_Repeat, this, &ATetris3DPlayerController::MoveDown);
}

void ATetris3DPlayerController::MoveLeft()
{
  Spawner->MoveActiveTetrominoLeft();
}

void ATetris3DPlayerController::MoveRight()
{
  Spawner->MoveActiveTetrominoRight();
}

void ATetris3DPlayerController::MoveDown()
{
  Spawner->MoveActiveTetrominoDown();
}
