#include "LCharacterSelectMenu.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "CharacterCardWidget.h"
#include "FCharacterData.h"

void ULCharacterSelectMenu::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ReadyButton)
        ReadyButton->OnClicked.AddDynamic(this, &ULCharacterSelectMenu::OnReadyClicked);

    if (UnselectButton)
        UnselectButton->OnClicked.AddDynamic(this, &ULCharacterSelectMenu::OnUnselectClicked);

    // Optionally populate the grid if CharacterDataArray is set in BP
    PopulateCharacterGrid();
}

void ULCharacterSelectMenu::PopulateCharacterGrid()
{
    if (!CharacterGridPanel || !CharacterCardWidgetClass) return;

    CharacterGridPanel->ClearChildren();
    CharacterCardWidgets.Empty();

    const int32 NumColumns = 4; // Change as needed for your layout
    int32 Row = 0, Col = 0;

    for (int32 i = 0; i < CharacterDataArray.Num(); ++i)
    {
        UCharacterCardWidget* CardWidget = CreateWidget<UCharacterCardWidget>(this, CharacterCardWidgetClass);
        if (CardWidget)
        {
            CardWidget->InitWithData(CharacterDataArray[i], i);
            CardWidget->OnCardSelected.AddDynamic(this, &ULCharacterSelectMenu::OnCharacterCardSelected);

            CharacterGridPanel->AddChildToUniformGrid(CardWidget, Row, Col);
            CharacterCardWidgets.Add(CardWidget);

            ++Col;
            if (Col >= NumColumns)
            {
                Col = 0;
                ++Row;
            }
        }
    }
}

void ULCharacterSelectMenu::OnCharacterCardSelected(int32 CardIndex)
{
    SelectedCharacterIndex = CardIndex;

    // Highlight selected card, remove highlight from others
    for (int32 i = 0; i < CharacterCardWidgets.Num(); ++i)
    {
        if (CharacterCardWidgets[i])
        {
            CharacterCardWidgets[i]->SetIsSelected(i == CardIndex);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Selected character index: %d"), CardIndex);
}

void ULCharacterSelectMenu::OnReadyClicked()
{
    if (SelectedCharacterIndex != INDEX_NONE && CharacterDataArray.IsValidIndex(SelectedCharacterIndex))
    {
        const FCharacterData& SelectedChar = CharacterDataArray[SelectedCharacterIndex];
        UE_LOG(LogTemp, Log, TEXT("Ready! Character: %s"), *SelectedChar.CharacterName.ToString());
        // TODO: Store selection and transition to game
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No character selected!"));
    }
}

void ULCharacterSelectMenu::OnUnselectClicked()
{
    // Deselect any selected character
    SelectedCharacterIndex = INDEX_NONE;
    for (UCharacterCardWidget* Card : CharacterCardWidgets)
    {
        if (Card)
            Card->SetIsSelected(false);
    }
    UE_LOG(LogTemp, Log, TEXT("Selection cleared."));
}
