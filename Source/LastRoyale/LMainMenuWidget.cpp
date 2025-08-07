#include "LMainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void ULMainMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (PlayButton)
    {
        PlayButton->OnClicked.AddDynamic(this, &ULMainMenuWidget::OnPlayClicked);
    }

    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &ULMainMenuWidget::OnQuitClicked);
    }
}

void ULMainMenuWidget::OnPlayClicked()
{
    OnPlayButtonClicked.Broadcast();
    if (CharacterSelectMenuClass)
    {
        UUserWidget* CharacterSelectMenu = CreateWidget<UUserWidget>(GetWorld(), CharacterSelectMenuClass);

        if (CharacterSelectMenu)
        {
            RemoveFromParent();

            CharacterSelectMenu->AddToViewport();

            APlayerController* PC = GetWorld()->GetFirstPlayerController();
            if (PC)
            {
                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(CharacterSelectMenu->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PC->SetInputMode(InputMode);
                PC->bShowMouseCursor = true;
            }
        }
    }
}

void ULMainMenuWidget::OnQuitClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}