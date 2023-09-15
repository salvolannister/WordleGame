// Fill out your copyright notice in the Description page of Project Settings.


#include "WordlePawn.h"

#include <GameFramework/GameModeBase.h>
#include "WordleGameModeBase.h"

void AWordlePawn::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	/*EnableInput(GetWorld()->GetFirstPlayerController());*/
}

void AWordlePawn::SetupPlayerInputComponent(UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);
	InInputComponent->BindAction("OnKeyboard", IE_Released, this, &AWordlePawn::ReadKey);
}

void AWordlePawn::ReadKey(FKey Key)
{
	if(AWordleGameModeBase* GameMode = Cast<AWordleGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->ConsumeInput(Key);
	}

}