// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Internationalization/Text.h"

#include "UIStartMenu.generated.h"

class UButton;
class UTextBlock;




UCLASS()
class WORDLETUTORIAL_API UUIStartMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UButton> PlayButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UButton> QuitButton;	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UButton> DownWordLenghtButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UButton> UpWordLenghtButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UButton> DownWordGuessesButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UButton> UpWordGuessesButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UTextBlock> WorldLengthText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UTextBlock> GuessesNumberText;
	int WorldLength;
	int GuessesNumber;

protected:
	void NativeConstruct() override;
	UFUNCTION()
		void OnDownWordLenButtonPressed();
	UFUNCTION()
		void OnUpWordLenButtonPressed();
	UFUNCTION()
		void OnDownWordGuessesButtonPressed();
	UFUNCTION()
		void OnUpWordGuessesButtonPressed();
	UFUNCTION()
		void OnPlayButtonPressed();
	UFUNCTION()
		void OnQuitButtonPressed();
	
};
