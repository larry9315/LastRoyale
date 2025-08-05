#include "LMainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void ULMainMenuWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();

    if (PlayButton) {
        PlayButton->OnClicked.AddDynamic(this, &ULMainMenuWidget::OnPlayClicked);
    }

    if (QuitButton) {
        QuitButton->OnClicked.AddDynamic(this, &ULMainMenuWidget::OnQuitClicked);
    }
}

void ULMainMenuWidget::OnPlayClicked() {
    if (CharacterSelectMenuClass) {
        UUserWidget* CharacterSelectMenu = CreateWidget<UUserWidget>(GetWorld(), CharacterSelectMenuClass);

        
        
    }
}

void ULMainMenuWidget::OnQuitClicked() {
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
