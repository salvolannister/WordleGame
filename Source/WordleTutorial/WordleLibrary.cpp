// Fill out your copyright notice in the Description page of Project Settings.


#include "WordleLibrary.h"
#include "Kismet/KismetStringLibrary.h"

bool static IsASCIILetter(char c)
{
	return (c >= 65 && c <= 90); 
}

bool UWordleLibrary::LoadWordsFromFile(FString FileName, int32 RequireWorldLength, TMap<int32, FStringArray>& Words)
{
	//Load the raw text from file
	FString parsedText;
	if (FFileHelper::LoadFileToString(parsedText, *(FPaths::ProjectContentDir() + FileName)) == false)
		return false;

	TArray<FString> parsedWords = UKismetStringLibrary::ParseIntoArray(parsedText, "\n");

	for (FString& word : parsedWords)
	{
		if(word.Len() < RequireWorldLength)
			continue;

		word.ToUpperInline();

		bool containsOnlyValidCharacter = true;
		for (const auto& letter : word.GetCharArray())
		{
			if (letter != '\0' && IsASCIILetter(letter) == false)
			{
				containsOnlyValidCharacter = false;
				break;
			}
		}
		if(containsOnlyValidCharacter == true)
			Words.FindOrAdd(word.Len()).Strings.Add(word);
	}

	return true;
}
