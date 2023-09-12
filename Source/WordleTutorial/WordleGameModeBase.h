// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/GameModeBase.h>

#include "WordleLibrary.h"

#include "WordleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WORDLETUTORIAL_API AWordleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
		virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StartMenu")
		void OnStartMenu();

		virtual void OnStartMenu_Implementation();
private:

	TMap<int32, FStringArray> Words;
};
