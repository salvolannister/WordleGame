// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverPanel.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class WORDLETUTORIAL_API UGameOverPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
		void SetGameOverDetailText(FText GoalWordText);
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UTextBlock> Details;

};
