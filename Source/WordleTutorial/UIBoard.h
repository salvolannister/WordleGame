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
	
	UPROPERTY(EditDefaultsOnly)
		FLinearColor WinningColor;
	UPROPERTY(EditDefaultsOnly)
		FLinearColor WrongColor;
	UPROPERTY(EditDefaultsOnly)
		FLinearColor WrongPositionColor;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Tiles")
		TObjectPtr<UUniformGridPanel> TileGrid;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
		TSubclassOf<UUITile> TileClass;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
		float DelayBetweenAnimations;
	/* Spawn a board of NRow rows and NColumn columns creating the UI for the grid*/
	UFUNCTION(BlueprintCallable)
		void SpawnBoard(const int NRow, const int NColumn);
	UFUNCTION(BlueprintCallable)
		FText GetTileWordAt(int IndexRow, int IndexColumn) const;
	UFUNCTION(BlueprintCallable)
		UUITile* GetTileAt(int IndexRow, int IndexColumn) const;
	UFUNCTION(BlueprintCallable)
		void ClearBoard();
	/* Handle UI tile effects when TileChangeType happens*/
	UFUNCTION()
		void HandleTileChange(int32 IndexRow, int32 IndexColumn, int32 TileChangeType);
	/* Try to write inside TileGrid(indexRow, indexColumn) the Text InLetter*/
	UFUNCTION()
		void HandleLetterInput(int32 IndexRow, int32 IndexColumn, FText InLetter);
	UFUNCTION()
		void HandleLetterCheck(bool bIsCorrectMatch);
protected:
	/* Dimension of the columns for the board*/
	int32 DimCol;
	/* Dimension of the rows for the board*/
	int32 DimRow;
	void NativePreConstruct() override;
	void NativeConstruct() override;
	void NativeDestruct() override;

private:
	/*Row index number to test the creation of the columns in the UI grid*/
	UPROPERTY(EditAnywhere, Category = "Debug")
		int32 RowIndexTest;
	/*Col index number to test the creation of the columns in the UI grid*/
	UPROPERTY(EditAnywhere, Category = "Debug")
		int32 ColIndexTest;
	/*Cumulative delay between tile animations, updated at runtime */
	float DelayBetweenTileAnimations;
};
