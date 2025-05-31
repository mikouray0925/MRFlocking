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

    // �y��b�|
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
    float Radius = 500.f;  // ���� Unity �� 5f (���G����)

    // �O�_ø�sGizmos
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
    bool bDrawGizmos = true;

protected:
    virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

};
