// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WordleLibrary.generated.h"


USTRUCT(BlueprintType)
struct FStringArray
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		TArray<FString> Strings;
};
/**
 * 
 */
UCLASS()
class WORDLETUTORIAL_API UWordleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "WordleLibrary")
		static bool LoadWordsFromFile(FString FileName, int32 RequireWorldLength, TMap<int32, FStringArray>& words);
	UFUNCTION(BlueprintCallable, Category = "WordleLibrary")
		static bool IsLetter(FString InString);
};
