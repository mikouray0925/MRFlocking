// Fill out your copyright notice in the Description page of Project Settings.


#include "FlocksController.h"
#include "Kismet/GameplayStatics.h"

AFlocksController::AFlocksController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AFlocksController::BeginPlay()
{
    Super::BeginPlay();
    // ªì©l¤Æ Context
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

    for (UFlockAgent* Agent : Agents)
    {
        if (Agent)
        {
            Agent->UpdateContext(DeltaTime, Context);
        }
    }

    for (UFlockAgent* Agent : Agents)
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
        if (UFlockAgent* Agent = Cast<UFlockAgent>(Child))
        {
            Agents.Add(Agent);
        }
    }
}

void AFlocksController::DestroyAllAgents()
{
    for (UFlockAgent* Agent : Agents)
    {
        if (Agent)
        {
            Agent->GetOwner()->Destroy();
        }
    }
    Agents.Empty();
}

