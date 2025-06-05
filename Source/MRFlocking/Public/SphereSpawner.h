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

    // 在場景中設定要生成的物件 (藍圖可見)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    TSubclassOf<AActor> TargetPrefab;

    // 指定父物件 (藍圖可見)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    AActor* TargetParent;

    // 半徑 (藍圖可見)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    float Radius;

    // 半徑 (藍圖可見)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    int DefaultSpawnNum = 1;

    UPROPERTY(EditAnywhere, Category = "Preview")
    UMaterialInterface* PreviewMaterial;

    UPROPERTY()
    UStaticMeshComponent* PreviewSphere;

    // 單個生成 (可在藍圖中呼叫)
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Spawner")
    void SpawnOne();

    void SpawnMultiple(int32 Count);

    // 批次生成 (可在藍圖中呼叫)
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Spawner")
    void Spawn();

protected:
    virtual void OnSpawn(AActor* Spawned) {};

    virtual void OnConstruction(const FTransform& Transform) override;  // 用於繪製編輯器中的球體
};
