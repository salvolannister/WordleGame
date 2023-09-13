// Fill out your copyright notice in the Description page of Project Settings.


#include "WordleGameModeBase.h"

#include <Blueprint/UserWidget.h>

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
	 StartMenuInstance = Cast<UUIStartMenu>(CreateWidget(PlayerController, UIStartMenuClass));
	 StartMenuInstance.Get()->AddToPlayerScreen(0);
	 PlayerController->SetInputMode(FInputModeUIOnly());
	 PlayerController->bShowMouseCursor = true;
}

void AWordleGameModeBase::StartRound(const int InWordLength,const int InNumberOfGuesses)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	/*PlayerController->SetInputMode(F)*/
	if (StartMenuInstance)
	{
		
	}

	NumberOfGuesses = InNumberOfGuesses;
	WordLength = InWordLength; 
}

void AWordleGameModeBase::QuitRound()
{
	
}

