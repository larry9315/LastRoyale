// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCardWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCharacterCardWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (SelectButtonBG)
        SelectButtonBG->OnClicked.AddDynamic(this, &UCharacterCardWidget::HandleCardClicked);
}

void UCharacterCardWidget::InitWithData(const FCharacterData& InData, int32 InCardIndex)
{
    CardIndex = InCardIndex;

    if (NameText)
        NameText->SetText(InData.CharacterName);

    if (PortraitImage && InData.Portrait)
        PortraitImage->SetBrushFromTexture(InData.Portrait); // Portrait: UTexture2D* in FCharacterData
}

void UCharacterCardWidget::SetIsSelected(bool bSelected)
{
    bIsSelected = bSelected;

}

void UCharacterCardWidget::HandleCardClicked()
{
    OnCardSelected.Broadcast(CardIndex);
}