// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FlockAgentSettings.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MRFLOCKING_API UFlockAgentSettings : public UDataAsset
{
    GENERATED_BODY()

public:
    // Detection
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
    float DetectionRadius = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
    TArray<TEnumAsByte<ECollisionChannel>> DetectionChannels;

    // Movement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float BaseSpeed = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MaxSpeed = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MaxAcceleration = 40.f;
};
