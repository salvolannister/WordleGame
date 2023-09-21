// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Internationalization/Text.h>

#include "UIBoard.generated.h"

class UUITile;
class UUniformGridPanel;

/**
 * 
 */
UCLASS()
class WORDLETUTORIAL_API UUIBoard : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float RowIndexTest;
	UPROPERTY(EditAnywhere)
		float ColIndexTest;
	UPROPERTY(EditAnywhere)
		bool bWantsToDesign;
	UPROPERTY(EditDefaultsOnly)
		FLinearColor WinningColor;
	UPROPERTY(EditDefaultsOnly)
		FLinearColor WrongColor;
	//Remove In from the name cause it's confusing
	UPROPERTY(EditDefaultsOnly)
		FLinearColor WrongPositionColor;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UUniformGridPanel> TileGrid;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
		TSubclassOf<class UUITile> TileClass;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
		float DelayBetweenAnimations;
	UFUNCTION(BlueprintCallable)
		void SpawnBoard(const int NRow, const int NColumn);
	UFUNCTION(BlueprintCallable)
		FText GetTileWordAt(int IndexRow, int IndexColumn) const;
	UFUNCTION(BlueprintCallable)
		UUITile* GetTileAt(int IndexRow, int IndexColumn) const;
	UFUNCTION(BlueprintCallable)
		void ClearBoard();
	UFUNCTION()
		void HandleTileChange(int32 IndexRow, int32 IndexColumn, int32 TileChangeType);
	UFUNCTION()
		void HandleLetterInput(int32 IndexRow, int32 IndexColumn, FText InLetter);
	UFUNCTION()
		void HandleLetterCheck(bool bIsCorrectMatch);
protected:
	/* Dimension of the column for the board*/
	int32 DimCol;
	int32 DimRow;
	void NativePreConstruct() override;
	void NativeConstruct() override;
	float AnimationDelay;
	void NativeDestruct() override;

};
