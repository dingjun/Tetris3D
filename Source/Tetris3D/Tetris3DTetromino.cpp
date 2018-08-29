// Fill out your copyright notice in the Description page of Project Settings.

#include "Tetris3DTetromino.h"
#include "Tetris3DBlockGrid.h"
#include "Tetris3DSpawner.h"
#include "Tetris3DGameMode.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ATetris3DTetromino::ATetris3DTetromino()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Create dummy root scene component
  DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
  RootComponent = DummyRoot;

  ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"));

  BlockArray.SetNum(4);
  for (int i = 0; i < BlockArray.Num(); ++i)
  {
    switch (i)
    {
    case 0:
      Block0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block0"));
      BlockArray[i] = Block0;
      break;
    case 1:
      Block1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block1"));
      BlockArray[i] = Block1;
      break;
    case 2:
      Block2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block2"));
      BlockArray[i] = Block2;
      break;
    case 3:
      Block3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block3"));
      BlockArray[i] = Block3;
      break;
    }
    
    BlockArray[i]->SetStaticMesh(PlaneMesh.Get());
    BlockArray[i]->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.25f));
    BlockArray[i]->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
    BlockArray[i]->SetupAttachment(DummyRoot);
  }
}

// Called when the game starts or when spawned
void ATetris3DTetromino::BeginPlay()
{
  Super::BeginPlay();
	
  bActive = true;
  StepTime = 1.0f;
  ElapsedTime = 0.0f;

  TActorIterator<ATetris3DBlockGrid> ActorIteratorGrid(GetWorld());
  Grid = *ActorIteratorGrid;

  TActorIterator<ATetris3DSpawner> ActorIteratorSpawner(GetWorld());
  Spawner = *ActorIteratorSpawner;

  // Check if in valid position
  for (auto Block : BlockArray)
  {
    if (Grid->IsValid(Block, Block->GetComponentLocation()) == false)
    {
      ATetris3DGameMode* GameMode = (ATetris3DGameMode*)(GetWorld()->GetAuthGameMode());
      GameMode->SetCurrentState(ETetris3DPlayState::ELost);
      return;
    }
  }
}

// Called every frame
void ATetris3DTetromino::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  if (bActive == false)
  {
    return;
  }

  ElapsedTime += DeltaTime;
  if (ElapsedTime > StepTime || Step.X != 0.0f || Step.Y != 0.0f)
  {
    if (ElapsedTime > StepTime)
    {
      Step = FVector(-1.0f, 0.0f, 0.0f);
    }

    FVector RealStep = Step * Grid->GetBlockSpacing();

    // Check if the step is valid
    for (auto Block : BlockArray)
    {
      if (Grid->IsValid(Block, Block->GetComponentLocation() + RealStep) == false)
      {
        if (Step.X != 0.0f)
        {
          bActive = false;
          Grid->CheckFullRows();
          Spawner->SpawnTetromino();
        }
        return;
      }
    }

    // Remove old position from Grid
    for (auto Block : BlockArray)
    {
      Grid->Update(NULL, Block->GetComponentLocation());
    }

    // Update position
    SetActorLocation(GetActorLocation() + RealStep);

    // Add new position to Grid
    for (auto Block : BlockArray)
    {
      Grid->Update(Block, Block->GetComponentLocation());
    }

    if (Step.X != 0.0f)
    {
      ElapsedTime = 0.0f;
    }
    Step = FVector(0.0f, 0.0f, 0.0f);
  }
}

void ATetris3DTetromino::MoveLeft()
{
  Step = FVector(0.0f, -1.0f, 0.0f);
}

void ATetris3DTetromino::MoveRight()
{
  Step = FVector(0.0f, 1.0f, 0.0f);
}

void ATetris3DTetromino::MoveDown()
{
  Step = FVector(-1.0f, 0.0f, 0.0f);
}
