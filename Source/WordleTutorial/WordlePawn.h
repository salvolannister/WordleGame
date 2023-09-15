// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "InputCoreTypes.h"

#include "WordlePawn.generated.h"

/**
 * 
 */
UCLASS()
class WORDLETUTORIAL_API AWordlePawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	void ReadKey(FKey Key);

protected:
	void BeginPlay() override;

private:
	void SetupPlayerInputComponent(UInputComponent* InInputComponent) override;

};
