// Fill out your copyright notice in the Description page of Project Settings.


#include "WordleGameModeBase.h"



void AWordleGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	/*Words = new TMap<int32, FStringArray>();*/
	UWordleLibrary::LoadWordsFromFile("words1.txt", 3, AWordleGameModeBase::Words);
	OnStartMenu();
}

void AWordleGameModeBase::OnStartMenu_Implementation()
{
	//CreateWidget(this, UUIStartMenu);
}
