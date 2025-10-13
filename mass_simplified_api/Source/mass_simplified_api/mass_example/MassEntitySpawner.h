#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MassArchetypeTypes.h"
#include "MassEntityTypes.h"

#include "MassEntitySpawner.generated.h"

class UMassEntitySubsystem;

UCLASS()
class AMassEntitySpawner : public AActor {
    GENERATED_BODY()
  public:
    AMassEntitySpawner();

    // Shared velocity for all spawned entities
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mass Entity")
    FVector EntityVelocity{100.0f, 0.0f, 0.0f};
  protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
  private:
    void CreateArchetype(UMassEntitySubsystem& MassEntitySubsystem,
                         FMassEntityManager& EntityManager);
    void CreateSharedValues(FMassEntityManager& EntityManager);
    void SpawnEntity(UMassEntitySubsystem& MassEntitySubsystem, FMassEntityManager& EntityManager);

    FMassArchetypeHandle Archetype{};
    FMassArchetypeSharedFragmentValues SharedValues{};
};
