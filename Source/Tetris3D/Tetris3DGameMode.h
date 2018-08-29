// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Tetris3DGameMode.generated.h"

/** Enum to store the current state of gameplay */
UENUM(BlueprintType)
enum class ETetris3DPlayState : uint8
{
  EReady,
  EPlaying,
  EWon,
  ELost,
  EUnknown
};

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ATetris3DGameMode : public AGameModeBase
{
	GENERATED_BODY()

  /** Keep track of the current playing state */
  ETetris3DPlayState CurrentState;

public:
	ATetris3DGameMode();

  /** Remove the current menu widget and create a new one from the specified class, if provided. */
  UFUNCTION(BlueprintCallable, Category = "Tetris 3D")
  void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
  
  /** Return the current playing state */
  UFUNCTION(BlueprintPure, Category = "Tetris 3D")
  FText GetCurrentStateText() const;

  /** Return the current playing state */
  UFUNCTION(BlueprintPure, Category = "Tetris 3D")
  ETetris3DPlayState GetCurrentState() const;

  /** Set a new playing state */
  UFUNCTION(BlueprintCallable, Category = "Tetris 3D")
  void SetCurrentState(ETetris3DPlayState NewState);

protected:
  /** Called when the game starts. */
  virtual void BeginPlay() override;

  /** The widget class we will use as our menu when the game starts. */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tetris 3D")
  TSubclassOf<UUserWidget> StartingWidgetClass;

  /** The widget instance that we are using as our menu. */
  UPROPERTY()
  UUserWidget* CurrentWidget;
};



