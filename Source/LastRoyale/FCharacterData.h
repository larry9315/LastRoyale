#pragma once

#include "CoreMinimal.h"
#include "FCharacterData.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData 
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText CharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Portrait;

    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // TSubclassOf<APawn> CharacterClass;
};
