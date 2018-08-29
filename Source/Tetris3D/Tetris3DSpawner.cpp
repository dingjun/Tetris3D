// Fill out your copyright notice in the Description page of Project Settings.

#include "Tetris3DSpawner.h"
#include "Tetris3DTetromino.h"
#include "Tetris3DGameMode.h"
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

  GameMode = (ATetris3DGameMode*)(GetWorld()->GetAuthGameMode());
}

void ATetris3DSpawner::SpawnTetromino()
{
  if (GameMode->GetCurrentState() != ETetris3DPlayState::EPlaying)
  {
    return;
  }

  ATetris3DTetromino* Tetromino;
  int32 RandIndex = FMath::RandHelper(3);
  switch (RandIndex)
  {
  case 0:
    Tetromino = GetWorld()->SpawnActor<ATetris3DTetromino>(TetrominoI, GetActorLocation(), FRotator(0, 0, 0));
    break;
  case 1:
    Tetromino = GetWorld()->SpawnActor<ATetris3DTetromino>(TetrominoO, GetActorLocation(), FRotator(0, 0, 0));
    break;
  case 2:
    Tetromino = GetWorld()->SpawnActor<ATetris3DTetromino>(TetrominoT, GetActorLocation(), FRotator(0, 0, 0));
    break;
  }
  TetrominoArray.Push(Tetromino);
}

void ATetris3DSpawner::Init()
{
  for (auto Tetromino : TetrominoArray)
  {
    Tetromino->Destroy();
  }
  TetrominoArray.SetNum(0);
  SpawnTetromino();
}

void ATetris3DSpawner::MoveActiveTetrominoLeft()
{
  TetrominoArray.Top()->MoveLeft();
}

void ATetris3DSpawner::MoveActiveTetrominoRight()
{
  TetrominoArray.Top()->MoveRight();
}

void ATetris3DSpawner::MoveActiveTetrominoDown()
{
  TetrominoArray.Top()->MoveDown();
}
