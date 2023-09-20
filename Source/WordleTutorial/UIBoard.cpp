// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBoard.h"

#include <Components/UniformGridPanel.h>
#include <Internationalization/Text.h>

#include "WordleTutorial/UITile.h"

void UUIBoard::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (IsDesignTime() && bWantsToDesign)
	{
		ClearBoard();
		SpawnBoard(RowIndexTest, ColIndexTest);
	}
}


void UUIBoard::NativeConstruct()
{
	Super::NativeConstruct();

	/*ClearBoard();*/
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

