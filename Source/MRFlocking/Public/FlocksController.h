// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlocksContext.h"
#include "FlockAgent.h"
#include "FlocksController.generated.h"

UCLASS(Blueprintable)
class MRFLOCKING_API AFlocksController : public AActor
{
	GENERATED_BODY()
	
public:
    AFlocksController();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common")
    AActor* Confiner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common")
    TArray<AActor*> TargetPoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agents")
    TArray<AFlockAgent*> Agents;

    UPROPERTY()
    FlocksContext Context;

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Common")
    void GetAgentsFromChildren();

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Common")
    void DestroyAllAgents();

};
