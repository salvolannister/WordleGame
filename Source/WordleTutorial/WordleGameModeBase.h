// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/GameModeBase.h>

#include "WordleLibrary.h"
#include "UIBoard.h"

#include "WordleGameModeBase.generated.h"

class UUIStartMenu;
class UUIBoard;
/**
 * 
 */
UCLASS()
class WORDLETUTORIAL_API AWordleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UUIStartMenu> UIStartMenuClass;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUIBoard> UIBoardClass;

		virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StartMenu")
		void OnStartMenu();

		virtual void OnStartMenu_Implementation();

	UFUNCTION(BlueprintCallable)
		void StartRound(const int InWordLength,const int InNumberOfGuesses);

	UFUNCTION(BlueprintCallable)
		void QuitRound();
	UFUNCTION(BlueprintCallable)
		void ConsumeInput(FKey Key);
protected:
	
	UPROPERTY(VisibleAnywhere, Transient)
		FString GoalWord;

	TObjectPtr<class UUIStartMenu> StartMenuInstance;
	TObjectPtr<class UUIBoard> BoardInstance;

	int WordLength;
	int NumberOfGuesses;
	int CurrentLetterIndex;
	int CurrentGuessIndex;
	UFUNCTION(BlueprintCallable)
		void SpawnBoard();

private:
	TMap<int32, FStringArray> Words;

};
