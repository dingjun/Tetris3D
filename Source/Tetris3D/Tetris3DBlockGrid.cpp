// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Tetris3DBlockGrid.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ATetris3DBlockGrid::ATetris3DBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Width = 10;
	Height = 15;
	BlockSpacing = 150.f;
}


void ATetris3DBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Width * Height;

	// Loop to spawn each block
	/*for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex/Width) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Width) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		ATetris3DBlock* NewBlock = GetWorld()->SpawnActor<ATetris3DBlock>(BlockLocation, FRotator(0,0,0));

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
		}
	}*/

  GridArray.Init(NULL, NumBlocks);
}


void ATetris3DBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));
}


int32 ATetris3DBlockGrid::GetGridIndex(FVector Block) const
{
  Block = (Block - GetActorLocation()) / BlockSpacing;
  if (Block.Y < 0 || Block.Y >= Width || Block.X < 0)
  {
    return -1;
  }
  return Block.X * Width + Block.Y;
}


bool ATetris3DBlockGrid::IsFullRow(const int32& Row) const
{
  for (int32 i = 0; i < Width; ++i)
  {
    int32 GridIndex = GetGridIndex(i, Row);
    if (GridArray[GridIndex] == NULL)
    {
      return false;
    }
  }
  return true;
}


void ATetris3DBlockGrid::DeleteRow(const int32& Row)
{
  for (int32 i = 0; i < Width; ++i)
  {
    int32 GridIndex = GetGridIndex(i, Row);
    GridArray[GridIndex]->DestroyComponent();
    GridArray[GridIndex] = NULL;
  }
}


void ATetris3DBlockGrid::MoveRowsDown(const int32& StartingRow)
{
  for (int32 Row = StartingRow; Row < Height; ++Row)
  {
    for (int32 Column = 0; Column < Width; ++Column)
    {
      int32 GridIndex = GetGridIndex(Column, Row);
      if (GridArray[GridIndex] != NULL)
      {
        int32 NewGridIndex = GetGridIndex(Column, Row - 1);
        GridArray[NewGridIndex] = GridArray[GridIndex];
        GridArray[GridIndex] = NULL;
        GridArray[NewGridIndex]->AddRelativeLocation(FVector(-BlockSpacing, 0.0f, 0.0));
      }
    }
  }
}


bool ATetris3DBlockGrid::IsValid(const UStaticMeshComponent* Block, const FVector& Location) const
{
  const int32 GridIndex = GetGridIndex(Location);
  return !(GridIndex < 0 || GridArray[GridIndex] != NULL && GridArray[GridIndex]->GetOwner() != Block->GetOwner());
}


void ATetris3DBlockGrid::Update(UStaticMeshComponent* Block, const FVector& Location)
{
  const int32 GridIndex = GetGridIndex(Location);
  GridArray[GridIndex] = Block;
}


void ATetris3DBlockGrid::CheckFullRows()
{
  for (int32 i = 0; i < Height; ++i)
  {
    if (IsFullRow(i))
    {
      DeleteRow(i);
      MoveRowsDown(i + 1);
      --i;
    }
  }
}

#undef LOCTEXT_NAMESPACE
