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

    // �b�������]�w�n�ͦ������� (�Źϥi��)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    TSubclassOf<AActor> TargetPrefab;

    // ���w������ (�Źϥi��)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    AActor* TargetParent;

    // �b�| (�Źϥi��)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    float Radius = 500.0f;
};
