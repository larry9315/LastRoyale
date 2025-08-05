// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "CharacterCardWidget.h"
#include "FCharacterData.h"

#include "LCharacterSelectMenu.generated.h"




UCLASS()
class LASTROYALE_API ULCharacterSelectMenu : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;
    
protected:
    // Ready/Unselect buttons (already present)
    UPROPERTY(meta = (BindWidget))
    UButton* ReadyButton;

    UPROPERTY(meta = (BindWidget))
    UButton* UnselectButton;

    // Character grid panel in the widget (must be named "CharacterGridPanel" in UMG)
    UPROPERTY(meta = (BindWidget))
    UUniformGridPanel* CharacterGridPanel;

    // The card widget blueprint class to spawn (assign in defaults)
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UCharacterCardWidget> CharacterCardWidgetClass;

    // Store spawned character cards
    UPROPERTY()
    TArray<UCharacterCardWidget*> CharacterCardWidgets;

    // Array of available characters for selection
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
    TArray<FCharacterData> CharacterDataArray;

    // Currently selected index (if any)
    int32 SelectedCharacterIndex = INDEX_NONE;

    UFUNCTION()
    void OnReadyClicked();

    UFUNCTION()
    void OnUnselectClicked();

    // Called when a card is selected
    UFUNCTION()
    void OnCharacterCardSelected(int32 CardIndex);

    // Helper: Populate the grid with cards
    void PopulateCharacterGrid();
};
