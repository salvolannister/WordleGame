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
			SpawnBoard();
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

	// subscribe BoardInstance to GameMode events here
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
		// better using events to manage user interface
		if (UUITile* Tile = UIBoardInstanceWidget->GetTileAt(CurrentGuessIndex, i))
		{
			if (GuessWordArray.GetCharArray()[i] == GoalWord.GetCharArray()[i])
			{
				Tile->AnimateTileWithDelay(AnimationDelay);
				Tile->ChangeTileColorTo(UIBoardInstanceWidget->WinningColor);
				AnimationDelay += UIBoardInstanceWidget->Delay_Between_Animations;
				CorrectLetterNum += 1;
			}
			else if (GoalWord.FindChar(GuessWordArray.GetCharArray()[i], OutCharIndex))
			{
				Tile->ChangeTileColorTo(UIBoardInstanceWidget->WrongPositionColor);
			}
			else
			{
				Tile->ChangeTileColorTo(UIBoardInstanceWidget->WrongColor);
			}

		}
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
			UUITile* Tile = UIBoardInstanceWidget->GetTileAt(CurrentGuessIndex, CurrentLetterIndex - 1);
			Tile->SetTileLetter(FText::GetEmpty());
			GuessWordArray.RemoveAt(CurrentLetterIndex - 1, 1, true);
			CurrentLetterIndex == 0 ? 0 : CurrentLetterIndex--;
		}
	}
	else if (Key == EKeys::Enter)
	{
		if (CurrentLetterIndex == WordLength)
		{

			if (GetCorrectLetterNumber() == WordLength)
			{
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
	}
	else
	{

		const FString KeyString = Key.ToString();
		if (CurrentLetterIndex < WordLength && UWordleLibrary::IsLetter(KeyString))
		{

			if (UUITile* Tile = UIBoardInstanceWidget->GetTileAt(CurrentGuessIndex, CurrentLetterIndex))
			{
				GuessWordArray.AppendChar(KeyString.GetCharArray()[0]);
				Tile->SetTileLetter(FText::FromString(KeyString));
				CurrentLetterIndex += 1;

			}
			else
			{
				UE_LOG(LogClass, Error, TEXT("Cant retrieve tile at r: %d c: %d "), CurrentGuessIndex, CurrentLetterIndex);

			}
		}
		
	}
	
}

void AWordleGameModeBase::OpenGameOverPanel()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (GameOverPanelInstance = Cast<UGameOverPanel>(CreateWidget(PlayerController, UIGameOverPanelClass)))
	{
		GameOverPanelInstance->SetGameOverDetailText(FText::FromString(GoalWord));

		GameOverPanelInstance.Get()->AddToPlayerScreen(0);
		PlayerController->bShowMouseCursor = true;
	}
}

