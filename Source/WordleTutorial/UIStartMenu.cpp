// Fill out your copyright notice in the Description page of Project Settings.


#include "UIStartMenu.h"

#include "Components/Button.h"
#include "EntitySystem/MovieSceneEntityFactoryTemplates.h"
#include "Components/TextBlock.h"
#include "Internationalization/Text.h"
#include "Kismet/GameplayStatics.h"

#include "WordleGameModeBase.h"

void UUIStartMenu::NativeConstruct()
{
	Super::NativeConstruct();

	WorldLength = 8;
	GuessesNumber = 10;

	if (DownWordLenghtButton)
	{
		DownWordLenghtButton->OnClicked.AddDynamic(this, &UUIStartMenu::OnDownWordLenButtonPressed);
	}

	if (UpWordLenghtButton)
	{
		UpWordLenghtButton->OnClicked.AddDynamic(this, &UUIStartMenu::OnUpWordLenButtonPressed);
	}

	if (DownWordGuessesButton)
	{
		DownWordGuessesButton->OnClicked.AddDynamic(this, &UUIStartMenu::OnDownWordGuessesButtonPressed);
	}

	if (UpWordGuessesButton)
	{
		UpWordGuessesButton->OnClicked.AddDynamic(this, &UUIStartMenu::OnUpWordGuessesButtonPressed);
	}


	WorldLengthText->SetText(FText::AsNumber(WorldLength));
	GuessesNumberText->SetText(FText::AsNumber(GuessesNumber));
}

void UUIStartMenu::OnDownWordLenButtonPressed()
{
	if(WorldLength <= 3)
		return;
	
	WorldLength--;
	WorldLengthText->SetText(FText::AsNumber(WorldLength));
		
}

void UUIStartMenu::OnUpWordLenButtonPressed()
{
	if(WorldLength >= 10)
		return;

	WorldLength++;
	WorldLengthText->SetText(FText::AsNumber(WorldLength));
}

void UUIStartMenu::OnDownWordGuessesButtonPressed()
{
	if (GuessesNumber <= 3)
		return;

	GuessesNumber--;
	GuessesNumberText->SetText(FText::AsNumber(GuessesNumber));

}

void UUIStartMenu::OnUpWordGuessesButtonPressed()
{
	if (GuessesNumber >= 10)
		return;

	GuessesNumber++;
	GuessesNumberText->SetText(FText::AsNumber(GuessesNumber));
}

void UUIStartMenu::OnPlayButtonPressed()
{
	if (AWordleGameModeBase* GameMode = Cast<AWordleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->StartRound(WorldLength, GuessesNumber);
	}
  
}

void UUIStartMenu::OnQuitButtonPressed()
{

	if (AWordleGameModeBase* GameMode = Cast<AWordleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->QuitRound();
	}
}
