// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tetris3DTetromino.generated.h"

UCLASS()
class TETRIS3D_API ATetris3DTetromino : public AActor
{
	GENERATED_BODY()
	
  /** Dummy root component */
  UPROPERTY(Category = Tetromino, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  class USceneComponent* DummyRoot;

  TArray<class UStaticMeshComponent*> BlockArray;

  int32 Id;
  bool bEnable;
  float StepTime;
  float ElapsedTime;
  class ATetris3DBlockGrid* Grid;
  class ATetris3DSpawner* Spawner;

protected:
  /** StaticMesh components */
  UPROPERTY(Category = Block, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UStaticMeshComponent* Block0;
  UPROPERTY(Category = Block, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UStaticMeshComponent* Block1;
  UPROPERTY(Category = Block, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UStaticMeshComponent* Block2;
  UPROPERTY(Category = Block, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
  class UStaticMeshComponent* Block3;

public:	
	// Sets default values for this actor's properties
	ATetris3DTetromino();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  /** Returns DummyRoot subobject **/
  FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	
  /** Returns BlockArray subobject **/
  FORCEINLINE TArray<class UStaticMeshComponent*> GetBlockMesh() const { return BlockArray; }

  FORCEINLINE void SetId(const int32 Index) { Id = Index; }
};
