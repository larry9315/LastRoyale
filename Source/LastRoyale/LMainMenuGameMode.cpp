// Fill out your copyright notice in the Description page of Project Settings.


#include "LMainMenuGameMode.h"

#include "LMainMenuWidget.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"


ALMainMenuGameMode::ALMainMenuGameMode()
{
}

void ALMainMenuGameMode::DestroyRotatingGun()
{
    if (RotatingGunActor)
    {
        RotatingGunActor->Destroy();
        RotatingGunActor = nullptr;
    }
}

void ALMainMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (MainMenuWidgetClass)
    {
        MainMenuInstance = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
        
        ULMainMenuWidget* MainMenu = Cast<ULMainMenuWidget>(MainMenuInstance);
        
        if (MainMenu)
        {
            MainMenu->OnPlayButtonClicked.AddDynamic(this, &ALMainMenuGameMode::DestroyRotatingGun);
            MainMenu->AddToViewport();

            APlayerController* PC = GetWorld()->GetFirstPlayerController();
            if (PC)
            {
                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(MainMenu->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PC->SetInputMode(InputMode);
                PC->bShowMouseCursor = true;

                TArray<AActor*> Cameras;
                UGameplayStatics::GetAllActorsOfClass(this, ACameraActor::StaticClass(), Cameras);
                if (Cameras.Num() > 0)
                {
                    PC->SetViewTargetWithBlend(Cameras[0]);
                }
            }
        }
    }

    if (RotatingGunClass)
    {
        // Spawn the rotating gun in front of the camera/menu
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        FVector SpawnLocation = FVector(10, 20, 200); // Adjust as needed
        FRotator SpawnRotation = FRotator::ZeroRotator;

        RotatingGunActor = GetWorld()->SpawnActor<AActor>(
            RotatingGunClass,
            SpawnLocation,
            SpawnRotation,
            SpawnParams
        );
    }
}