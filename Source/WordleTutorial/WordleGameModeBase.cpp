// Fill out your copyright notice in the Description page of Project Settings.



#include "WordleGameModeBase.h"

#include <Blueprint/UserWidget.h>
#include <Camera/CameraStackTypes.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/InputSettings.h>

#include "WordleLibrary.h"
#include "UIBoard.h"
#include "UITile.h"
#include "UIStartMenu.h"


void AWordleGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	/*Words = new TMap<int32, FStringArray>();*/
	UWordleLibrary::LoadWordsFromFile("words1.txt", 3, AWordleGameModeBase::Words);
	OnStartMenu();
}

void AWordleGameModeBase::OnStartMenu_Implementation()
{
	 APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	 if (StartMenuInstance = Cast<UUIStartMenu>(CreateWidget(PlayerController, UIStartMenuClass)))
	 {
		StartMenuInstance.Get()->AddToPlayerScreen(0);
		//PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
	 }
		
}

void AWordleGameModeBase::StartRound(const int InWordLength,const int InNumberOfGuesses)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	NumberOfGuesses = InNumberOfGuesses;
	WordLength = InWordLength; 
	CurrentGuessIndex = 0;
	CurrentLetterIndex = 0;
	IsGameOver = false;
	
	if (!Words.IsEmpty())
	{
		if (FStringArray* WordsArray = Words.Find(WordLength))
		{
			if (WordsArray->Strings.IsValidIndex(0))
			{
				int32 RandomIndex = FMath::RandRange(0, WordsArray->Strings.Num() - 1);
				GoalWord = WordsArray->Strings[RandomIndex];
				UE_LOG(LogClass, Log, TEXT("The word chosen is %s"), *GoalWord);
			}
		}
		
	}

	SpawnBoard();
}

void AWordleGameModeBase::QuitRound()
{
	
}

void AWordleGameModeBase::SpawnBoard()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (BoardInstance = Cast<UUIBoard>(CreateWidget(PlayerController, UIBoardClass)))
	{
		BoardInstance->SpawnBoard(NumberOfGuesses, WordLength);

		BoardInstance.Get()->AddToPlayerScreen(0);
		//PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = true;
	}

}

int AWordleGameModeBase::GetCorrectLetterNumber()
{
	int CorrectLetterNum = 0;
	if(GuessWordArray.Num() < WordLength)
		return CorrectLetterNum;

	float AnimationDelay = 0.f;

	for (int32 i = 0; i < WordLength; i++)
	{
		if (UUITile* Tile = BoardInstance->GetTileAt(CurrentGuessIndex, i))
		{
			if (GuessWordArray[i] == GoalWord.GetCharArray()[i])
			{
				Tile->AnimateTileWithDelay(AnimationDelay);
				Tile->ChangeTileColorTo(BoardInstance->WinningColor);
				AnimationDelay += BoardInstance->DELAY_BETWEEN_ANIMATIONS;
				CorrectLetterNum += 1;
			}
			else
			{
				// Is word present elsewhere?
				Tile->ChangeTileColorTo(BoardInstance->WrongColor);
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
			UUITile* Tile = BoardInstance->GetTileAt(CurrentGuessIndex, CurrentLetterIndex - 1);
			Tile->SetTileLetter(FText::GetEmpty());
			GuessWordArray.RemoveAt(CurrentLetterIndex - 1);
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
				UE_LOG(LogClass, Log, TEXT("Game Over"));
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

			if (UUITile* Tile = BoardInstance->GetTileAt(CurrentGuessIndex, CurrentLetterIndex))
			{
				GuessWordArray.Add(KeyString.GetCharArray()[0]);
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

