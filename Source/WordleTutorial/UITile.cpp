// Fill out your copyright notice in the Description page of Project Settings.



#include "UITile.h"

#include <Components/TextBlock.h>
#include <Animation/WidgetAnimation.h>
#include <Components/Button.h>
#include <Brushes/SlateColorBrush.h>

void UUITile::AnimateTileWithDelay(const float StartDelay)
{	
	if (StartDelay == 0.f)
	{
		StartAnimation();
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(AnimationDelayHandle, this, &UUITile::StartAnimation, StartDelay, false);

}

FText UUITile::GetTileLetter()
{
	return Letter;
}


void UUITile::ChangeTileColorTo(const FLinearColor Color)
{

	FButtonStyle OldButtonStyle = TileButton->WidgetStyle.SetDisabled(FSlateColorBrush(Color));
	TileButton->SetStyle(OldButtonStyle);
}

void UUITile::NativeConstruct()
{
	Super::NativeConstruct();

	if (TileLetter)
	{
		Letter = FText::FromString(" ");
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


void UUITile::StartAnimation()
{
	UUserWidget::PlayAnimation(TileRotateAnimation);

}
