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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr<class UUniformGridPanel> TileGrid;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
		TSubclassOf<class UUITile> TileClass;
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
		float DELAY_BETWEEN_ANIMATIONS;
	UFUNCTION(BlueprintCallable)
		void SpawnBoard(const int NRow, const int NColumn);
	UFUNCTION(BlueprintCallable)
		FText GetTileWordAt(int IndexRow, int IndexColumn) const;
	UFUNCTION(BlueprintCallable)
		UUITile* GetTileAt(int IndexRow, int IndexColumn) const;

protected:
	/* Dimension of the column for the board*/
	int DimCol;
};
