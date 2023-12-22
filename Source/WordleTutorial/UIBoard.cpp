// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBoard.h"

#include <Components/UniformGridPanel.h>
#include <Internationalization/Text.h>

#include "WordleTutorial/WordleGameModeBase.h"
#include "WordleTutorial/UITile.h"

void UUIBoard::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (IsDesignTime())
	{
		ClearBoard();
		SpawnBoard(RowIndexTest, ColIndexTest);
	}
}


void UUIBoard::NativeConstruct()
{
	Super::NativeConstruct();

	AWordleGameModeBase* GameMode = Cast<AWordleGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!ensure(GameMode))
		return;

	GameMode->OnTileChange.AddDynamic(this, &UUIBoard::HandleTileChange);
	GameMode->OnLetterInput.AddDynamic(this, &UUIBoard::HandleLetterInput);
	GameMode->OnLetterCheck.AddDynamic(this, &UUIBoard::HandleLetterCheck);
	DelayBetweenTileAnimations = 0.f;
}

void UUIBoard::NativeDestruct()
{
	Super::NativeDestruct();
	
	AWordleGameModeBase* GameMode = Cast<AWordleGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!ensure(GameMode))
		return;

	GameMode->OnTileChange.RemoveDynamic(this, &UUIBoard::HandleTileChange);
	GameMode->OnLetterInput.RemoveDynamic(this, &UUIBoard::HandleLetterInput);
	GameMode->OnLetterCheck.RemoveDynamic(this, &UUIBoard::HandleLetterCheck);

}

void UUIBoard::SpawnBoard(const int NRow, const int NColumn)
{
	DimCol = NColumn;
	DimRow = NRow;
	
	for (int32 i = 0; i < NRow; i++)
	{
		for (int32 ii = 0; ii < NColumn; ii++)
		{
			UUITile* TempTile = Cast<UUITile>(CreateWidget(GetWorld(), TileClass));
			TileGrid->AddChildToUniformGrid(TempTile, i, ii);
		}
	}

}

void UUIBoard::ClearBoard()
{
	TileGrid->ClearChildren();
}

void UUIBoard::HandleTileChange(int32 IndexRow, int32 IndexColumn, int32 TileChangeType)
{
	UUITile* Tile = GetTileAt(IndexRow, IndexColumn);
	if(!ensure(Tile))
		return;

	switch (TileChangeType)
	{
		case 0: // Winning match
			Tile->AnimateTileWithDelay(DelayBetweenTileAnimations);
			Tile->ChangeTileColorTo(WinningColor);
			DelayBetweenTileAnimations += DelayBetweenAnimations;
			break;
		case 1: // Letter present but in wrong position
			Tile->ChangeTileColorTo(WrongPositionColor);
			break;
		case 2:
			Tile->ChangeTileColorTo(WrongColor);
			break;

	}
}

FText UUIBoard::GetTileWordAt(int IndexRow, int IndexColumn) const
{
	UUITile* Tile = GetTileAt(IndexRow, IndexColumn);
	return Tile->GetTileLetter();
}

UUITile* UUIBoard::GetTileAt(int IndexRow, int IndexColumn) const
{
	UUITile* Tile = nullptr;
	int TilePosIndex = (IndexRow*DimCol) + IndexColumn;
	if (UWidget* Widget = TileGrid->GetChildAt(TilePosIndex))
	{
		Tile = Cast<UUITile>(Widget);
	}
	return Tile;
}

void UUIBoard::HandleLetterInput(int32 IndexRow, int32 IndexColumn, FText InLetter)
{
	UUITile* Tile = GetTileAt(IndexRow, IndexColumn);
	if (!ensure(Tile))
		return;

	Tile->SetTileLetter(InLetter);
	
}

void UUIBoard::HandleLetterCheck(bool bIsCorrectMatch)
{
	DelayBetweenTileAnimations = 0.f;
}

