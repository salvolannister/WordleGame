// Fill out your copyright notice in the Description page of Project Settings.


#include "UIStartMenu.h"

void UUIStartMenu::NativeConstruct()
{
	Super::NativeConstruct();

	WorldLength = 8;
	GuessesNumber = 10;

	if (DownWordLenghtButton)
	{
		DownWordLenghtButton->OnClicked.AddDynamic(this, &UUIStartMenu::OnDownWordLenButtonPressed);
	}
}


void UUIStartMenu::OnDownWordLenButtonPressed()
{
	if(WorldLength <= 3)
		return;
	
	WorldLength--;
	
	//DownWordLenghtButton->SetText(FText::FromString(FString::FromInt(WorldLength)));
	/*if (FText* TextToChange = DownWordLenghtButton->GetChildComponent())
	{
	}*/
		
}

void UUIStartMenu::OnUpWordButtonPressed()
{
	if(WorldLength >= 10)
		return;

	WorldLength++;

	//UpWordLenghtButton->SetText(FText(TEXT("T"));
	//if (FText* TextToChange = ButtonToChange->GetChildComponent())
	//{
	//	TextToChange->SetText(FText::FromString(FString::FromInt(WorldLength)));
	//}
}