// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tetris3DSpawner.generated.h"

UCLASS()
class TETRIS3D_API ATetris3DSpawner : public AActor
{
	GENERATED_BODY()
	
  /** Dummy root component */
  UPROPERTY(Category = Spawner, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  class USceneComponent* DummyRoot;

  class ATetris3DGameMode* GameMode;
  TArray<class ATetris3DTetromino*> TetrominoArray;
  
protected:
  /** The tetromino to spawn */
  UPROPERTY(Category = Spawner, EditAnywhere)
  TSubclassOf<class ATetris3DTetromino> TetrominoI;
  UPROPERTY(Category = Spawner, EditAnywhere)
  TSubclassOf<class ATetris3DTetromino> TetrominoO;
  UPROPERTY(Category = Spawner, EditAnywhere)
  TSubclassOf<class ATetris3DTetromino> TetrominoT;

public:	
	// Sets default values for this actor's properties
	ATetris3DSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
  /** Returns DummyRoot subobject **/
  FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

  UFUNCTION(BlueprintCallable, Category = Spawner)
  void Init();

  /** Handle spawning a new tetromino **/
  UFUNCTION(BlueprintCallable, Category = Spawner)
  void SpawnTetromino();
	
  void MoveActiveTetrominoLeft();
  void MoveActiveTetrominoRight();
  void MoveActiveTetrominoDown();
};
