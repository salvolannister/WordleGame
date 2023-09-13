// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Internationalization/Text.h>

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
	//}

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UButton> TileButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UTextBlock> TileLetter;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UWidgetAnimation> TileAnimnation;

	UFUNCTION(BlueprintCallable)
		void SetTileLetter(const FText InLetter);
	UFUNCTION(BlueprintCallable)
		void AnimateTile();
protected:
	
	void NativeConstruct() override;
	
	FText Letter;


};
