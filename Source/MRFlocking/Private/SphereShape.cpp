// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereShape.h"

ASphereShape::ASphereShape()
{
    PrimaryActorTick.bCanEverTick = false;

    // �[�W RootComponent
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ASphereShape::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bDrawGizmos)
    {
        // ø�s�b�z����߲y��
        DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 12, FColor(0, 255, 0, 64), false, -1.f, 0, 1.f);
        // ø�s���~�زy��
        DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 12, FColor::Green, false, -1.f, 0, 2.f);
    }
}

#if WITH_EDITOR
void ASphereShape::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    OnConstruction(GetActorTransform());
}
#endif

