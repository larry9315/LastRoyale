// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "LMainMenuGameMode.generated.h"


/**
 *
 */
UCLASS()
class LASTROYALE_API ALMainMenuGameMode : public AGameModeBase {
    GENERATED_BODY()

  public:
    ALMainMenuGameMode();

  protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> MainMenuWidgetClass;

  private:
    UPROPERTY()
    UUserWidget* MainMenuInstance;
};
