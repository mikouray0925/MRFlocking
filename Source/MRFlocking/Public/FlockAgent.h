#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlocksContext.h"
#include "FlockAgentContext.h"
#include "FlockAgentSettings.h"
#include "FlockBehaviour.h"
#include "FlockAgent.generated.h"

UCLASS(ClassGroup = (Custom))
class MRFLOCKING_API AFlockAgent : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    AFlockAgent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    /** Settings */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Properties")
    UFlockAgentSettings* AgentSettings;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Properties")
    UFlockBehaviour* Behaviour;

    /** Context */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flock|Context")
    FVector Velocity = FVector::ZeroVector;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flock|Context")
    FlockAgentContext Context;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flock|Context")
    TArray<UPrimitiveComponent*> NearbyColliders;

    void UpdateContext(float DeltaTime, const FlocksContext& FlocksContext);
    void UpdateVelocity(float DeltaTime, const FlocksContext& FlocksContext);

private:
    UPROPERTY()
    UObject* AgentCollider;

    void UpdateColliderArrayLength(int NewLength);
};