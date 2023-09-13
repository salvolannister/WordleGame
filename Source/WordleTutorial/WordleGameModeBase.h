// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/GameModeBase.h>

#include "WordleLibrary.h"

#include "WordleGameModeBase.generated.h"

class UUIStartMenu;
/**
 * 
 */
UCLASS()
class WORDLETUTORIAL_API AWordleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category ="Widgets")
		TSubclassOf<class UUIStartMenu> UIStartMenuClass;

		virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StartMenu")
		void OnStartMenu();

		virtual void OnStartMenu_Implementation();

	UFUNCTION(BlueprintCallable)
		void StartRound(const int InWordLength,const int InNumberOfGuesses);

	UFUNCTION(BlueprintCallable)
		void QuitRound();
protected:
	
	UPROPERTY(VisibleAnywhere, Transient)
		FString GoalWord;
	TObjectPtr<class UUIStartMenu> StartMenuInstance;
	int WordLength;
	int NumberOfGuesses;
	int CurrentLetterIndex;
	int CurrentGuessIndex;
	UFUNCTION(BlueprintCallable)
		void SpawnBoard();

private:
	TMap<int32, FStringArray> Words;

};
