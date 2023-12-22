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
class UUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTileChange, int32, ColumnIndex, int32, RowIndex, int32, ChangeTypeIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLetterInput, int32, ColumnIndex, int32, RowIndex, FText, TileLetter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLetterCheck, bool, bIsCorrectMatch);
/**
 * The management of the different widgets could be moved inside a HUD class 
 * that just listen of the different states of the GameMode
 */
UCLASS()
class WORDLETUTORIAL_API AWordleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	
		
	UPROPERTY(BlueprintAssignable)
		FTileChange OnTileChange;
	UPROPERTY(BlueprintAssignable)
		FLetterInput OnLetterInput;
	/* This event is triggered during testing to determine whether the letter in the tile
	   shares both the same position and character as the letter at the corresponding 
	   position in the word to be guessed. */
	UPROPERTY(BlueprintAssignable)
		FOnLetterCheck OnLetterCheck;

		virtual void OnStartMenu_Implementation();
		
		virtual void BeginPlay() override;
		 
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UUserWidget> UIBackgroundPanelWidget;
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
	TObjectPtr<class UUserWidget> UIBackgroundPanelInstanceWidget;
	
	int32 WordLength;
	int32 NumberOfGuesses;
	int32 CurrentLetterIndex;
	int32 CurrentGuessIndex;
	bool IsGameOver;
	FString GuessWordArray;

private:
	TMap<int32, FStringArray> Words;

};
