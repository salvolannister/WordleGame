// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "UIStartMenu.generated.h"
//
//class UButton;
//class FOnButtonClickedEvent;
/**
 * 
 */
UCLASS()
class WORDLETUTORIAL_API UUIStartMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UButton> PlayButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UButton> QuitButton;	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UButton> DownWordLenghtButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UButton> UpWordLenghtButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UButton> DownWordGuessesButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<UButton> UpWordGuessesButton;

	int WorldLength;
	int GuessesNumber;

protected:
	void NativeConstruct() override;
	UFUNCTION()
		void OnDownWordLenButtonPressed();
	UFUNCTION()
		void OnUpWordButtonPressed();
	
};
