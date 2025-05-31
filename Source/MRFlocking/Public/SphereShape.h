// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SphereShape.generated.h"

UCLASS()
class MRFLOCKING_API ASphereShape : public AActor
{
	GENERATED_BODY()
	
public:
    ASphereShape();

    // 球體半徑
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
    float Radius = 500.f;  // 對應 Unity 的 5f (單位：公尺)

    // 是否繪製Gizmos
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
    bool bDrawGizmos = true;

protected:
    virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

};
