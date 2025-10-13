#include "MassEntitySpawner.h"

#include "MassArchetypeTypes.h"
#include "MassEntitySubsystem.h"
#include "MassFragments.h"

AMassEntitySpawner::AMassEntitySpawner() {
    // Enable ticking
    PrimaryActorTick.bCanEverTick = true;

    // Set tick interval to 0.05 seconds (20 Hz)
    PrimaryActorTick.TickInterval = 0.05f;
}

void AMassEntitySpawner::BeginPlay() {
    Super::BeginPlay();

    auto MassEntitySubsystem{GetWorld()->GetSubsystem<UMassEntitySubsystem>()};
    if (!MassEntitySubsystem) {
        UE_LOG(LogTemp, Error, TEXT("MassEntitySubsystem not found!"));
        return;
    }
    auto& EntityManager{MassEntitySubsystem->GetMutableEntityManager()};

    CreateArchetype(*MassEntitySubsystem, EntityManager);
    CreateSharedValues(EntityManager);
}

void AMassEntitySpawner::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    auto MassEntitySubsystem{GetWorld()->GetSubsystem<UMassEntitySubsystem>()};
    if (!MassEntitySubsystem) {
        UE_LOG(LogTemp, Error, TEXT("MassEntitySubsystem not found!"));
        return;
    }
    auto& EntityManager{MassEntitySubsystem->GetMutableEntityManager()};

    // Spawn one entity every tick
    SpawnEntity(*MassEntitySubsystem, EntityManager);
}

void AMassEntitySpawner::CreateArchetype(UMassEntitySubsystem& MassEntitySubsystem,
                                         FMassEntityManager& EntityManager) {
    auto Descriptor{FMassArchetypeCompositionDescriptor{}};
    Descriptor.Fragments.Add(*FMassTransformFragment::StaticStruct());

    Descriptor.ConstSharedFragments.Add(*FMassVelocityConstSharedFragment::StaticStruct());

    auto CreationParams{FMassArchetypeCreationParams{}};
    CreationParams.DebugName = FName(TEXT("bullet_archetype"));

    Archetype = EntityManager.CreateArchetype(Descriptor, CreationParams);
}
void AMassEntitySpawner::CreateSharedValues(FMassEntityManager& EntityManager) {
    auto const VelocityHandle{
        EntityManager.GetOrCreateConstSharedFragment<FMassVelocityConstSharedFragment>(
            EntityVelocity)};

    SharedValues.Add(VelocityHandle);
    SharedValues.Sort();
}
void AMassEntitySpawner::SpawnEntity(UMassEntitySubsystem& MassEntitySubsystem,
                                     FMassEntityManager& EntityManager) {
    FMassEntityHandle EntityHandle{EntityManager.CreateEntity(Archetype, SharedValues)};
    {
        auto& TransformFragment{
            EntityManager.GetFragmentDataChecked<FMassTransformFragment>(EntityHandle)};
        TransformFragment.Transform = GetActorTransform();
    }
}
