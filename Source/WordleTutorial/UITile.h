// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Internationalization/Text.h>
#include <Engine/EngineTypes.h>

#include "UITile.generated.h"

class UButton;
class UTextBlock;
class UWidgetAnimation;

/**
 * 
 */
UCLASS()
class WORDLETUTORIAL_API UUITile : public UUserWidget
{
	GENERATED_BODY()
	

public:
//Couldn't create this
	//UUITile(FText InLetter)
	//: Letter(InLetter)
	//{
	//
	//}

	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidget))
		TObjectPtr<class UButton> TileButton;
	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidget))
		TObjectPtr<class UTextBlock> TileLetter;
	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
		TObjectPtr<class UWidgetAnimation> TileRotateAnimation;

	UFUNCTION(BlueprintCallable)
		void SetTileLetter(const FText InLetter);
	UFUNCTION(BlueprintCallable)
		void AnimateTileWithDelay(const float StartDelay);
	UFUNCTION(BlueprintCallable)
		FText GetTileLetter();
	/* Changes tile color to green*/
	UFUNCTION(BlueprintCallable)
		void ChangeTileToWinningColor();

protected:
	
	void NativeConstruct() override;

	void StartAnimation();
	
	FText Letter;

	FTimerHandle AnimationDelayHandle;
};
