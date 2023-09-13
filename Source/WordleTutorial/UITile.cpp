// Fill out your copyright notice in the Description page of Project Settings.


#include "UITile.h"

#include <Components/TextBlock.h>
#include <Animation/WidgetAnimation.h>


void UUITile::AnimateTile()
{
	if (TileAnimnation == nullptr)
		return;

	UUserWidget::PlayAnimation(TileAnimnation);
}

void UUITile::NativeConstruct()
{
	Super::NativeConstruct();

	if (TileLetter)
	{
		Letter = FText::FromString("A");
		TileLetter->SetText(Letter);
	}
}

void UUITile::SetTileLetter(const FText InLetter)
{
	Letter = InLetter;
	if (TileLetter)
	{
		TileLetter->SetText(Letter);
	}
}

