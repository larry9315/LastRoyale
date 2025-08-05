// Fill out your copyright notice in the Description page of Project Settings.


#include "LMainMenuGameMode.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"


ALMainMenuGameMode::ALMainMenuGameMode()
{
}

void ALMainMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (MainMenuWidgetClass)
    {
        MainMenuInstance = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
        if (MainMenuInstance)
        {
            MainMenuInstance->AddToViewport();

            APlayerController* PC = GetWorld()->GetFirstPlayerController();
            if (PC)
            {
                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(MainMenuInstance->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PC->SetInputMode(InputMode);
                PC->bShowMouseCursor = true;

                TArray<AActor*> Cameras;
                UGameplayStatics::GetAllActorsOfClass(this, ACameraActor::StaticClass(), Cameras);
                if (Cameras.Num() > 0) {
                    PC->SetViewTargetWithBlend(Cameras[0]);
                }
            }
        }
    }
}
