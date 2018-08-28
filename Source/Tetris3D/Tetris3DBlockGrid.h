// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tetris3DBlockGrid.generated.h"

/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class ATetris3DBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;

  TArray<int32> GridArray;

public:
	ATetris3DBlockGrid();

	/** How many blocks have been clicked */
	int32 Score;

	/** Number of blocks in one row */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Width;

	/** Number of blocks in one column */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Height;

	/** Spacing of blocks */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

private:
  int32 GetGridIndex(FVector Block) const;

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

public:

	/** Handle the block being clicked */
	void AddScore();

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }

  bool IsValid(const int32& TetrominoId, const FVector& Block) const;

  void Update(const int32& TetrominoId, const FVector& Block);
};



