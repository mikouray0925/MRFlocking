// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShpereSpawner.generated.h"

UCLASS()
class MRFLOCKING_API AShpereSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShpereSpawner();

    // 在場景中設定要生成的物件 (藍圖可見)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    TSubclassOf<AActor> TargetPrefab;

    // 指定父物件 (藍圖可見)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    AActor* TargetParent;

    // 半徑 (藍圖可見)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    float Radius = 500.0f;
};
