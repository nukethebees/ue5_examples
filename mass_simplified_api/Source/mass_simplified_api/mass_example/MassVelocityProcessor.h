#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "MassQueryExecutor.h"

#include "MassFragments.h"

#include "MassVelocityProcessor.generated.h"

// Query executor that performs the actual entity processing
struct FMassVelocityExecutor : public UE::Mass::FQueryExecutor {
    FMassVelocityExecutor() = default;

    // Define which fragments we need and how we access them
    using Query = UE::Mass::FQueryDefinition<
        UE::Mass::FMutableFragmentAccess<FMassTransformFragment>,
        UE::Mass::FConstSharedFragmentAccess<FMassVelocityConstSharedFragment>>;

    Query Accessors{*this};

    virtual void Execute(FMassExecutionContext& Context) override;
};

// The processor that runs the velocity executor
UCLASS()
class MASS_SIMPLIFIED_API_API UMassVelocityProcessor : public UMassProcessor {
    GENERATED_BODY()
  public:
    UMassVelocityProcessor();
  private:
    FMassEntityQuery EntityQuery;
    TSharedPtr<FMassVelocityExecutor> Executor;
};
