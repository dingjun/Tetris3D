// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tetris3DPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class ATetris3DPlayerController : public APlayerController
{
	GENERATED_BODY()

  class ATetris3DSpawner* Spawner;

public:
	ATetris3DPlayerController();

	virtual void BeginPlay() override;

  virtual void SetupInputComponent() override;

protected:
  void MoveLeft();
  void MoveRight();
  void MoveDown();
};


