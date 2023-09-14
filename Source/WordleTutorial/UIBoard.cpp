// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBoard.h"

#include <Components/UniformGridPanel.h>
#include <Internationalization/Text.h>

#include "WordleTutorial/UITile.h"

void UUIBoard::SpawnBoard(const int NRow, const int NColumn)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		for (int32 i = 0; i < NRow; i++)
		{
			for (int32 ii = 0; ii < NColumn; ii++)
			{
				UUITile* TempTile = Cast<UUITile>(CreateWidget(PlayerController, TileClass));
				TileGrid->AddChildToUniformGrid(TempTile, i, ii);
			}
		}
	}

}

FText UUIBoard::GetTileWordAt(int IndexRow, int IndecColumn) const
{
	return FText::FromString("A");
}
