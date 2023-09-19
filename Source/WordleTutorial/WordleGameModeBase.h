// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/GameModeBase.h>

#include "WordleLibrary.h"
#include "UIBoard.h"

#include "WordleGameModeBase.generated.h"

class UUIStartMenu;
class UUIBoard;
class UGameOverPanel;
/**
 * 
 */
UCLASS()
class WORDLETUTORIAL_API AWordleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
		virtual void OnStartMenu_Implementation();
		
		virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UUIStartMenu> UIStartMenuClass;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUIBoard> UIBoardClass;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UGameOverPanel> UIGameOverPanelClass;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StartMenu")
		void OnStartMenu();
	UFUNCTION(BlueprintCallable)
		void StartRound(const int InWordLength, const int InNumberOfGuesses);
	UFUNCTION(BlueprintCallable)
		void QuitRound();
	UFUNCTION(BlueprintCallable)
		void ConsumeInput(FKey Key);
	UFUNCTION(BlueprintCallable)
		void OpenGameOverPanel();
protected:
	
	UFUNCTION(BlueprintCallable)
		void SpawnBoard();
	UFUNCTION(BlueprintCallable)
		int GetCorrectLetterNumber();
	UPROPERTY(VisibleAnywhere, Transient)
		FString GoalWord;

	TObjectPtr<class UUIStartMenu> StartMenuInstance;
	TObjectPtr<class UUIBoard> BoardInstance;
	TObjectPtr<class UGameOverPanel> GameOverPanelInstance;

	int WordLength;
	int NumberOfGuesses;
	int CurrentLetterIndex;
	int CurrentGuessIndex;
	bool IsGameOver;
	TArray<char> GuessWordArray;

private:
	TMap<int32, FStringArray> Words;

};
