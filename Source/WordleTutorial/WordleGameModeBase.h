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
 * The management of the different widgets could be moved inside a HUD class 
 * that just listen of the different states of the GameMode
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
		int32 GetCorrectLetterNumber();
	UPROPERTY(VisibleAnywhere, Transient)
		FString GoalWord;

	TObjectPtr<class UUIStartMenu> StartMenuInstance;
	TObjectPtr<class UUIBoard> UIBoardInstanceWidget;
	TObjectPtr<class UGameOverPanel> GameOverPanelInstance;

	
	int32 WordLength;
	int32 NumberOfGuesses;
	int32 CurrentLetterIndex;
	int32 CurrentGuessIndex;
	bool IsGameOver;
	FString GuessWordArray;

private:
	TMap<int32, FStringArray> Words;

};
