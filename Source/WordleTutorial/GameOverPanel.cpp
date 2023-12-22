// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverPanel.h"

#include <Internationalization/Text.h>
#include <Components/TextBlock.h>
#include "Containers/UnrealString.h"


void UGameOverPanel::SetGameOverDetailText(FText GoalWordText)
{
	if(Details == nullptr)
		return;

	const FString GoalWordString = GoalWordText.ToString();
	FString DetailsString = Details->GetText().ToString();
	int OutIndex = -1;
	
	FString RightStr;
	FString LeftStr;
	
	DetailsString.Split(TEXT("#"), &RightStr, &LeftStr);
	
	
	Details->SetText(FText::FromString( RightStr + GoalWordString + LeftStr));
}
