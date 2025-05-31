// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SphereSpawner.generated.h"

UCLASS()
class MRFLOCKING_API ASphereSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASphereSpawner();

    // �b�������]�w�n�ͦ������� (�Źϥi��)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    TSubclassOf<AActor> TargetPrefab;

    // ���w������ (�Źϥi��)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    AActor* TargetParent;

    // �b�| (�Źϥi��)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    float Radius;

    UPROPERTY(EditAnywhere, Category = "Preview")
    UMaterialInterface* PreviewMaterial;

    UPROPERTY()
    UStaticMeshComponent* PreviewSphere;

    // ��ӥͦ� (�i�b�ŹϤ��I�s)
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Spawner")
    void Spawn();

    // �妸�ͦ� (�i�b�ŹϤ��I�s)
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Spawner")
    void SpawnMultiple(int32 Count);

protected:
    virtual void OnConstruction(const FTransform& Transform) override;  // �Ω�ø�s�s�边�����y��
};
