// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxShape.generated.h"

UCLASS()
class MRFLOCKING_API ABoxShape : public AActor
{
	GENERATED_BODY()
	
public:	

	/** Local space size of the box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Shape")
	FVector Size = FVector(1000.0f);

	/** Whether to draw debug box in editor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Shape")
	bool bDrawGizmos = true;

	/** Get the size of the box in world space */
	UFUNCTION(BlueprintCallable, Category = "Box Shape")
	FVector GetWorldSize() const;

	// Sets default values for this actor's properties
	ABoxShape();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

};
