#include "FlockAgent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/OverlapResult.h"

// Sets default values for this component's properties
UFlockAgent::UFlockAgent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UFlockAgent::BeginPlay()
{
    Super::BeginPlay();

    // Find collider (assumes the root or first primitive)
    AgentCollider = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    Context.NearbyColliders = NearbyColliders;
}

// Called every frame
void UFlockAgent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Debug visualization
    if (Behaviour)
    {
        Behaviour->DrawGizmos(GetWorld(), GetOwner()->GetActorLocation(), AgentSettings ? AgentSettings->DetectionRadius : 100.f);
    }
}

void UFlockAgent::UpdateContext(float DeltaTime, const FlocksContext& FlocksContext)
{
    AActor* Owner = GetOwner();
    if (!Owner || !AgentSettings) return;

    Context.Position = Owner->GetActorLocation();
    Context.Forward = Owner->GetActorForwardVector();
    Context.Up = Owner->GetActorUpVector();
    Context.Transform = Owner;

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
        if (Result.Component.Get() != AgentCollider && Result.GetActor() != GetOwner())
        {
            NearbyColliders.Add(Result.Component.Get());
        }
    }

    Context.NearbyColliders = NearbyColliders;
    Context.NearbyCollidersCount = NearbyColliders.Num();
}

void UFlockAgent::UpdateVelocity(float DeltaTime, const FlocksContext& FlocksContext)
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
    AActor* Owner = GetOwner();
    if (Owner)
    {
        FVector NewPosition = Owner->GetActorLocation() + Velocity * DeltaTime;
        Owner->SetActorLocation(NewPosition);

        if (Velocity.Size() > KINDA_SMALL_NUMBER)
        {
            Owner->SetActorRotation(Velocity.Rotation());
        }
    }
}

void UFlockAgent::UpdateColliderArrayLength(int NewLength)
{
    NearbyColliders.SetNum(NewLength);
    Context.NearbyColliders = NearbyColliders;
}