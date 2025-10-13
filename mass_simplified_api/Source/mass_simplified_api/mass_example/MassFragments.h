#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"

#include "MassFragments.generated.h"

// Regular fragment - holds per-entity transform data
USTRUCT()
struct FMassTransformFragment : public FMassFragment {
    GENERATED_BODY()

    FMassTransformFragment() = default;
    FMassTransformFragment(FTransform Transform)
        : Transform(Transform) {}

    UPROPERTY()
    FTransform Transform{};
};

// Shared fragment - velocity shared across multiple entities
USTRUCT()
struct FMassVelocityConstSharedFragment : public FMassConstSharedFragment {
    GENERATED_BODY()

    FMassVelocityConstSharedFragment() = default;
    FMassVelocityConstSharedFragment(FVector Velocity)
        : Velocity(Velocity) {}

    UPROPERTY()
    FVector Velocity{FVector::ZeroVector};
};
