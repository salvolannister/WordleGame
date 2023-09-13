// Fill out your copyright notice in the Description page of Project Settings.


#include "WordleGameModeBase.h"

#include <Blueprint/UserWidget.h>
#include <Camera/CameraStackTypes.h>
#include <Kismet/GameplayStatics.h>

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
		PlayerController->SetInputMode(FInputModeUIOnly());
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
}

void AWordleGameModeBase::QuitRound()
{
	
}

void AWordleGameModeBase::SpawnBoard()
{
	// Create widget 
	// Call spawn board on the UI widget 
}