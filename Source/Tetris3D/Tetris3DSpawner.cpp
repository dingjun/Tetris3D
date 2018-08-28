// Fill out your copyright notice in the Description page of Project Settings.

#include "Tetris3DSpawner.h"
#include "Tetris3DTetromino.h"
#include "Engine/World.h"

// Sets default values
ATetris3DSpawner::ATetris3DSpawner()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = false;

  // Create dummy root scene component
  DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
  RootComponent = DummyRoot;
}

// Called when the game starts or when spawned
void ATetris3DSpawner::BeginPlay()
{
  Super::BeginPlay();

  SpawnTetromino();
}

void ATetris3DSpawner::SpawnTetromino()
{
  int32 RandIndex = FMath::RandHelper(3);
  switch (RandIndex)
  {
  case 0:
    ActiveTetromino = GetWorld()->SpawnActor<ATetris3DTetromino>(TetrominoI, GetActorLocation(), FRotator(0, 0, 0));
    break;
  case 1:
    ActiveTetromino = GetWorld()->SpawnActor<ATetris3DTetromino>(TetrominoO, GetActorLocation(), FRotator(0, 0, 0));
    break;
  case 2:
    ActiveTetromino = GetWorld()->SpawnActor<ATetris3DTetromino>(TetrominoT, GetActorLocation(), FRotator(0, 0, 0));
    break;
  }
}

void ATetris3DSpawner::MoveActiveTetrominoLeft()
{
  ActiveTetromino->MoveLeft();
}

void ATetris3DSpawner::MoveActiveTetrominoRight()
{
  ActiveTetromino->MoveRight();
}

void ATetris3DSpawner::MoveActiveTetrominoDown()
{
  ActiveTetromino->MoveDown();
}
