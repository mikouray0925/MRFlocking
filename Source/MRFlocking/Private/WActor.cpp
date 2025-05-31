// Fill out your copyright notice in the Description page of Project Settings.


#include "WActor.h"

// Sets default values
AWActor::AWActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto Rotation = FQuat(180.0f * DeltaTime);
	AddActorLocalRotation(Rotation);
}

