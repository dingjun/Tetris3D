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

void ATetris3DGameMode::BeginPlay()
{
  Super::BeginPlay();
  SetCurrentState(ETetris3DPlayState::EReady);
  ChangeMenuWidget(StartingWidgetClass);
}

void ATetris3DGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
  if (CurrentWidget != nullptr)
  {
    CurrentWidget->RemoveFromViewport();
    CurrentWidget = nullptr;
  }
  if (NewWidgetClass != nullptr)
  {
    CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
    if (CurrentWidget != nullptr)
    {
      CurrentWidget->AddToViewport();
    }
  }
}

FText ATetris3DGameMode::GetCurrentStateText() const
{
  FText StateText;
  switch (CurrentState)
  {
  case ETetris3DPlayState::EReady:
    StateText = FText::FromString("Ready?");
    break;
  case ETetris3DPlayState::EWon:
    StateText = FText::FromString("YOU WIN!");
    break;
  case ETetris3DPlayState::ELost:
    StateText = FText::FromString("GAME OVER!");
    break;
  }
  return StateText;
}

ETetris3DPlayState ATetris3DGameMode::GetCurrentState() const
{
  return CurrentState;
}

void ATetris3DGameMode::SetCurrentState(ETetris3DPlayState NewState)
{
  CurrentState = NewState;
}
