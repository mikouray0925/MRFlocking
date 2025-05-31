// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASphereSpawner::ASphereSpawner()
{
    PrimaryActorTick.bCanEverTick = false;  // 不需要每幀更新
    Radius = 500.0f;  // Unreal 使用公分單位
    // 加上 RootComponent
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // 創建預覽球體
    PreviewSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewSphere"));
    PreviewSphere->SetupAttachment(RootComponent);
    PreviewSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PreviewSphere->SetHiddenInGame(true);  // 只在編輯器中可見
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
    float Scale = Radius / 50.0f;  // 基本球體半徑約50cm
    PreviewSphere->SetWorldScale3D(FVector(Scale));
    // 繪製編輯器中的球體（代替 Gizmos）
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 32, FColor::Green, false, -1.0f, 0, 2.0f);
}










