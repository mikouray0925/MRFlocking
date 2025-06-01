// Fill out your copyright notice in the Description page of Project Settings.


#include "FlocksController.h"
#include "Kismet/GameplayStatics.h"

AFlocksController::AFlocksController()
{
    PrimaryActorTick.bCanEverTick = true;

    // 加上 RootComponent
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void AFlocksController::BeginPlay()
{
    Super::BeginPlay();
    // 初始化 Context
    Context.TargetPoints = TargetPoints;
}

void AFlocksController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Context.Confiner = Confiner;
    if (Confiner)
    {
        Context.ConfinerRight = Confiner->GetActorRightVector();
        Context.ConfinerUp = Confiner->GetActorUpVector();
        Context.ConfinerForward = Confiner->GetActorForwardVector();
    }
    else
    {
        Context.ConfinerRight = FVector::ZeroVector;
        Context.ConfinerUp = FVector::ZeroVector;
        Context.ConfinerForward = FVector::ZeroVector;
    }

    for (AFlockAgent* Agent : Agents)
    {
        if (Agent)
        {
            Agent->UpdateContext(DeltaTime, Context);
        }
    }

    for (AFlockAgent* Agent : Agents)
    {
        if (Agent)
        {
            Agent->UpdateVelocity(DeltaTime, Context);
        }
    }
}

void AFlocksController::GetAgentsFromChildren()
{
    Agents.Empty();
    TArray<AActor*> ChildActors;
    GetAttachedActors(ChildActors);

    for (AActor* Child : ChildActors)
    {
        if (AFlockAgent* Agent = Cast<AFlockAgent>(Child))
        {
            Agents.Add(Agent);
        }
    }
}

void AFlocksController::DestroyAllAgents()
{
    for (AFlockAgent* Agent : Agents)
    {
        if (Agent)
        {
            Agent->Destroy();
        }
    }
    Agents.Empty();
}

