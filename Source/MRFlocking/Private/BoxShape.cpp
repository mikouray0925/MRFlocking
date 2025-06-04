// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxShape.h"

// Sets default values
ABoxShape::ABoxShape()
{
    PrimaryActorTick.bCanEverTick = false;

    // ¥[¤W RootComponent
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

FVector ABoxShape::GetWorldSize() const
{
    return GetActorTransform().TransformVectorNoScale(Size);
}

void ABoxShape::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bDrawGizmos)
    {
        const FVector Origin = GetActorLocation();
        const FVector WorldExtent = GetWorldSize() * 0.5f;

        // Filled box (translucent green)
        // DrawDebugBox(GetWorld(), FBox::BuildAABB(Origin, WorldExtent), FColor(0, 255, 0, 50), false, -1, 0);

        // Wireframe box (green)
        DrawDebugBox(GetWorld(), Origin, WorldExtent, GetActorRotation().Quaternion(), FColor::Green, false, -1, 0, 2.0f);
    }
}

#if WITH_EDITOR
void ABoxShape::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    OnConstruction(GetActorTransform());
}
#endif

