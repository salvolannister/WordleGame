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
		DownWordLenghtButton->OnClicked.AddDynamic(this, &UUIStartMenu::OnDownWordLenButtonClicked);
	}

	if (UpWordLenghtButton)
	{
		UpWordLenghtButton->OnClicked.AddDynamic(this, &UUIStartMenu::OnUpWordLenButtonClicked);
	}

	if (DownWordGuessesButton)
	{
		DownWordGuessesButton->OnClicked.AddDynamic(this, &UUIStartMenu::OnDownWordGuessesButtonClicked);
	}

	if (UpWordGuessesButton)
	{
		UpWordGuessesButton->OnClicked.AddDynamic(this, &UUIStartMenu::OnUpWordGuessesButtonClicked);
	}

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UUIStartMenu::OnPlayButtonClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UUIStartMenu::OnQuitButtonClicked);
	}

	WordLengthText->SetText(FText::AsNumber(WorldLength));
	GuessesNumberText->SetText(FText::AsNumber(GuessesNumber));
}

void UUIStartMenu::OnDownWordLenButtonClicked()
{
	if(WorldLength <= 3)
		return;
	
	WorldLength--;
	WordLengthText->SetText(FText::AsNumber(WorldLength));
		
}

void UUIStartMenu::OnUpWordLenButtonClicked()
{
	if(WorldLength >= 10)
		return;

	WorldLength++;
	WordLengthText->SetText(FText::AsNumber(WorldLength));
}

void UUIStartMenu::OnDownWordGuessesButtonClicked()
{
	if (GuessesNumber <= 3)
		return;

	GuessesNumber--;
	GuessesNumberText->SetText(FText::AsNumber(GuessesNumber));

}

void UUIStartMenu::OnUpWordGuessesButtonClicked()
{
	if (GuessesNumber >= 10)
		return;

	GuessesNumber++;
	GuessesNumberText->SetText(FText::AsNumber(GuessesNumber));
}

void UUIStartMenu::OnPlayButtonClicked()
{
	if (AWordleGameModeBase* GameMode = Cast<AWordleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		
		GameMode->StartRound(WorldLength, GuessesNumber);
		
		SetVisibility(ESlateVisibility::Collapsed); // hidden calculates the dimension of the widget
		SetIsEnabled(false);
	}
  
}

void UUIStartMenu::OnQuitButtonClicked()
{

	if (AWordleGameModeBase* GameMode = Cast<AWordleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->QuitRound();
	}
}
