// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Tetris3DGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ATetris3DGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATetris3DGameMode();

  /** Remove the current menu widget and create a new one from the specified class, if provided. */
  UFUNCTION(BlueprintCallable, Category = "UMG Game")
  void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
  /** Called when the game starts. */
  virtual void BeginPlay() override;

  /** The widget class we will use as our menu when the game starts. */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
  TSubclassOf<UUserWidget> StartingWidgetClass;

  /** The widget instance that we are using as our menu. */
  UPROPERTY()
  UUserWidget* CurrentWidget;
};



