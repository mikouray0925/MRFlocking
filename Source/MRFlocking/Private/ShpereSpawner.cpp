// Fill out your copyright notice in the Description page of Project Settings.


#include "ShpereSpawner.h"

// Sets default values
AShpereSpawner::AShpereSpawner()
{
    PrimaryActorTick.bCanEverTick = false;  // 不需要每幀更新
    Radius = 500.0f;  // Unreal 使用公分單位
}




