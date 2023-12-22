// Fill out your copyright notice in the Description page of Project Settings.



#include "WordleGameModeBase.h"

#include <Kismet/KismetSystemLibrary.h>
#include <Blueprint/UserWidget.h>
#include <Camera/CameraStackTypes.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/InputSettings.h>

#include "WordleLibrary.h"
#include "UIBoard.h"
#include "UITile.h"
#include "UIStartMenu.h"
#include "GameOverPanel.h"


void AWordleGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UWordleLibrary::LoadWordsFromFile("words1.txt", 3, AWordleGameModeBase::Words);
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (UIBackgroundPanelInstanceWidget = Cast<UUserWidget>(CreateWidget(PlayerController, UIBackgroundPanelWidget)))
	{
		UIBackgroundPanelInstanceWidget.Get()->AddToPlayerScreen(0);
		PlayerController->bShowMouseCursor = true;
	}
	OnStartMenu();
}

void AWordleGameModeBase::OnStartMenu_Implementation()
{
	 APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	 if (StartMenuInstance = Cast<UUIStartMenu>(CreateWidget(PlayerController, UIStartMenuClass)))
	 {
		StartMenuInstance.Get()->AddToPlayerScreen(0);
		PlayerController->bShowMouseCursor = true;
	 }
		
}

void AWordleGameModeBase::StartRound(const int InWordLength,const int InNumberOfGuesses)
{
	if (!ensure(!Words.IsEmpty()))
		return;
	
	NumberOfGuesses = InNumberOfGuesses;
	WordLength = InWordLength; 
	CurrentGuessIndex = 0;
	CurrentLetterIndex = 0;
	IsGameOver = false;
	
	// Can't apply ensure here maybe it doesn't work
	if (FStringArray* WordsArray = Words.Find(WordLength))
	{
		if (!WordsArray->Strings.IsEmpty())
		{
			int32 RandomIndex = FMath::RandRange(0, WordsArray->Strings.Num() - 1);
			GoalWord = WordsArray->Strings[RandomIndex];
			UE_LOG(LogClass, Log, TEXT("The word chosen is %s"), *GoalWord);
			UIBackgroundPanelInstanceWidget->SetRenderOpacity(0.5f);
			SpawnBoard();

			if (!ensure(UIBoardInstanceWidget))
				return;

		}
	}
		
	
}

void AWordleGameModeBase::QuitRound()
{
	APlayerController* PlayerController  = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(),PlayerController, EQuitPreference::Quit, true);
}

void AWordleGameModeBase::SpawnBoard()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(UIBoardInstanceWidget = Cast<UUIBoard>(CreateWidget(PlayerController, UIBoardClass))))
		return;

	UIBoardInstanceWidget->SpawnBoard(NumberOfGuesses, WordLength);
	UIBoardInstanceWidget->AddToPlayerScreen(0);
	PlayerController->bShowMouseCursor = true;

	
}

int32 AWordleGameModeBase::GetCorrectLetterNumber()
{
	int32 CorrectLetterNum = 0;
	if(GuessWordArray.Len() < WordLength)
		return CorrectLetterNum;

	float AnimationDelay = 0.f;
	int32 OutCharIndex = 0;
	for (int32 i = 0; i < WordLength; i++)
	{
		int32 TileStateChange = -1;
		if (GuessWordArray.GetCharArray()[i] == GoalWord.GetCharArray()[i])
		{
			TileStateChange = 0; // winning
			CorrectLetterNum += 1;
		}
		else if (GoalWord.FindChar(GuessWordArray.GetCharArray()[i], OutCharIndex))
		{
			TileStateChange = 1; // in wrong position
		}
		else
		{
			TileStateChange = 2; // wrong
		}

		OnTileChange.Broadcast(CurrentGuessIndex, i,TileStateChange);
		
	}

	return CorrectLetterNum;
}

void AWordleGameModeBase::ConsumeInput(FKey Key)
{
	bool IsDeleteKey = Key == EKeys::BackSpace || Key == EKeys::Delete;

	if(IsDeleteKey && !IsGameOver) 
	{
		if(CurrentLetterIndex - 1 >= 0)
		{
			OnLetterInput.Broadcast(CurrentGuessIndex, CurrentLetterIndex - 1, FText::GetEmpty());
			GuessWordArray.RemoveAt(CurrentLetterIndex - 1, 1, true);
			CurrentLetterIndex == 0 ? 0 : CurrentLetterIndex--;
		}
	}
	else if (Key == EKeys::Enter)
	{
		bool IsCorrectMatch = false;
		if (CurrentLetterIndex == WordLength)
		{

			if (GetCorrectLetterNumber() == WordLength)
			{
				IsCorrectMatch = true;
				
				UE_LOG(LogClass, Log, TEXT("YOU WON"));
				return;
			}

			if (CurrentGuessIndex + 1 == NumberOfGuesses)
			{
				IsGameOver = true;
				OpenGameOverPanel();
			}
			else
			{
				CurrentGuessIndex += 1;
				CurrentLetterIndex = 0;
				GuessWordArray.Empty();
			}
		}

		OnLetterCheck.Broadcast(IsCorrectMatch);
	}
	else
	{

		const FString KeyString = Key.ToString();
		if (CurrentLetterIndex < WordLength && UWordleLibrary::IsLetter(KeyString))
		{
			GuessWordArray.AppendChar(KeyString.GetCharArray()[0]);
			OnLetterInput.Broadcast(CurrentGuessIndex, CurrentLetterIndex, FText::FromString(KeyString));
			CurrentLetterIndex += 1;
		}
		
	}
	
}

void AWordleGameModeBase::OpenGameOverPanel()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (GameOverPanelInstance = Cast<UGameOverPanel>(CreateWidget(PlayerController, UIGameOverPanelClass)))
	{
		GameOverPanelInstance->SetGameOverDetailText(FText::FromString(GoalWord));
		UIBackgroundPanelInstanceWidget->SetRenderOpacity(1.f);
		GameOverPanelInstance.Get()->AddToPlayerScreen(0);
		PlayerController->bShowMouseCursor = true;
	}
}

