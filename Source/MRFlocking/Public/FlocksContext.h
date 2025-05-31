// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlocksContext.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MRFLOCKING_API FlocksContext
{
public:
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    TWeakObjectPtr<AActor> Confiner;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    FVector ConfinerRight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    FVector ConfinerUp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    FVector ConfinerForward;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    TArray<AActor*> TargetPoints;
};
