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

  class ATetris3DGameMode* GameMode;

  TArray<class UStaticMeshComponent*> GridArray;
  int32 ScoreToWin;

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

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

  FORCEINLINE int32 GetGridIndex(const int32& Column, const int32& Row) const { return Row * Width + Column; }
  int32 GetGridIndex(FVector Block) const;
  bool IsFullRow(const int32& Row) const;
  void DeleteRow(const int32& Row);
  void MoveRowsDown(const int32& StartingRow);
  void AddScore(const int32& NumLines);

public:
  UFUNCTION(BlueprintPure, Category = Grid)
  FText GetCurrentScoreText() const;

  UFUNCTION(BlueprintCallable, Category = Grid)
  void Init();

	/** Handle the block being clicked */
	void AddScore();

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }

  FORCEINLINE float GetBlockSpacing() const { return BlockSpacing; }

  bool IsValid(const UStaticMeshComponent* Block, const FVector& Location) const;
  void Update(UStaticMeshComponent* Block, const FVector& Location);
  void CheckFullRows();
};



