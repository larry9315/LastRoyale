// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FCharacterData.h"
#include "CharacterCardWidget.generated.h"


class UButton;
class UImage;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCardSelected, int32, CardIndex);

UCLASS()
class LASTROYALE_API UCharacterCardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    // Call this to set up the card’s visuals and store the index
    void InitWithData(const FCharacterData& InData, int32 InCardIndex);

    UFUNCTION(BlueprintCallable)
    void SetIsSelected(bool bSelected);
    
    // Bind this delegate from the parent to handle clicks
    UPROPERTY(BlueprintAssignable)
    FOnCardSelected OnCardSelected;

protected:
    virtual void NativeOnInitialized() override;

    UFUNCTION()
    void HandleCardClicked();
    
    UPROPERTY(meta = (BindWidget))
    UButton* SelectButtonBG;

    UPROPERTY(meta = (BindWidget))
    UImage* PortraitImage;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* NameText;

    // Store the index of this card
    int32 CardIndex;

    bool bIsSelected = false;

    
};
