// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASphereSpawner::ASphereSpawner()
{
    PrimaryActorTick.bCanEverTick = false;  // ���ݭn�C�V��s
    Radius = 500.0f;  // Unreal �ϥΤ������
    // �[�W RootComponent
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // �Ыعw���y��
    PreviewSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewSphere"));
    PreviewSphere->SetupAttachment(RootComponent);
    PreviewSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PreviewSphere->SetHiddenInGame(true);  // �u�b�s�边���i��
    PreviewSphere->SetVisibility(true);
}

void ASphereSpawner::Spawn()
{
    if (!TargetPrefab) return;

    FVector Position = GetActorLocation() + UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0, Radius);
    FRotator Rotation = UKismetMathLibrary::MakeRotFromZ(UKismetMathLibrary::RandomUnitVector());

    FActorSpawnParameters SpawnParams;
    if (TargetParent)
    {
        SpawnParams.Owner = TargetParent;
        AActor* Spawned = GetWorld()->SpawnActor<AActor>(TargetPrefab, Position, Rotation, SpawnParams);
        if (Spawned && TargetParent)
        {
            Spawned->AttachToActor(TargetParent, FAttachmentTransformRules::KeepWorldTransform);
        }
    }
    else
    {
        GetWorld()->SpawnActor<AActor>(TargetPrefab, Position, Rotation);
    }
}

void ASphereSpawner::SpawnMultiple(int32 Count)
{
    for (int32 i = 0; i < Count; ++i)
    {
        Spawn();
    }
}

void ASphereSpawner::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    float Scale = Radius / 50.0f;  // �򥻲y��b�|��50cm
    PreviewSphere->SetWorldScale3D(FVector(Scale));
    // ø�s�s�边�����y��]�N�� Gizmos�^
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 32, FColor::Green, false, -1.0f, 0, 2.0f);
}










