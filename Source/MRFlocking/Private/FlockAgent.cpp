#include "FlockAgent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/OverlapResult.h"

// Sets default values for this component's properties
AFlockAgent::AFlockAgent()
{
    PrimaryActorTick.bCanEverTick = true;

    // ¥[¤W RootComponent
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

// Called when the game starts
void AFlockAgent::BeginPlay()
{
    Super::BeginPlay();

    // Find collider (assumes the root or first primitive)
    AgentCollider = Cast<UPrimitiveComponent>(GetRootComponent());
    Context.NearbyColliders = NearbyColliders;
}

// Called every frame
void AFlockAgent::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Debug visualization
    if (bDrawGizmos)
    {
        Behaviour->DrawGizmos(GetWorld(), GetActorLocation(), AgentSettings ? AgentSettings->DetectionRadius : 100.f);
    }
}

void AFlockAgent::UpdateContext(float DeltaTime, const FlocksContext& FlocksContext)
{
    if (!AgentSettings) return;

    Context.Position = GetActorLocation();
    Context.Forward = GetActorForwardVector();
    Context.Up = GetActorUpVector();
    Context.Transform = this;

    Context.DetectionRadius = AgentSettings->DetectionRadius;
    Context.BaseSpeed = AgentSettings->BaseSpeed;
    Context.LastVelocity = Velocity;
    Context.LastDirection = Velocity.GetSafeNormal();

    // Collect nearby colliders
    NearbyColliders.Reset();
    TArray<FOverlapResult> Overlaps;
    FCollisionObjectQueryParams QueryParams;
    for (auto Channel : AgentSettings->DetectionChannels)
    {
        QueryParams.AddObjectTypesToQuery(Channel);
    }
    FCollisionShape Sphere = FCollisionShape::MakeSphere(AgentSettings->DetectionRadius);
    GetWorld()->OverlapMultiByObjectType(Overlaps, Context.Position, FQuat::Identity, QueryParams, Sphere);

    for (FOverlapResult& Result : Overlaps)
    { 
        if (Result.Component.Get() != AgentCollider && Result.GetActor() != this)
        {
            NearbyColliders.Add(Result.Component.Get());
        }
    }

    Context.NearbyColliders = NearbyColliders;
    Context.NearbyCollidersCount = NearbyColliders.Num();
}

void AFlockAgent::UpdateVelocity(float DeltaTime, const FlocksContext& FlocksContext)
{
    if (!Behaviour || !AgentSettings) return;

    FVector TargetVelocity = Behaviour->CalculateVelocity(DeltaTime, FlocksContext, Context);
    if (TargetVelocity.Size() > AgentSettings->MaxSpeed)
    {
        TargetVelocity = TargetVelocity.GetSafeNormal() * AgentSettings->MaxSpeed;
    }

    float MaxDeltaSpeed = AgentSettings->MaxAcceleration * DeltaTime;
    FVector DeltaVelocity = TargetVelocity - Velocity;
    if (DeltaVelocity.Size() > MaxDeltaSpeed)
    {
        DeltaVelocity = DeltaVelocity.GetSafeNormal() * MaxDeltaSpeed;
    }

    Velocity += DeltaVelocity;
    FVector NewPosition = GetActorLocation() + Velocity * DeltaTime;
    SetActorLocation(NewPosition);
    if (Velocity.Size() > KINDA_SMALL_NUMBER)
    {
        SetActorRotation(Velocity.Rotation());
    }
}

void AFlockAgent::UpdateColliderArrayLength(int NewLength)
{
    NearbyColliders.SetNum(NewLength);
    Context.NearbyColliders = NearbyColliders;
}