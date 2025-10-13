#include "MassVelocityProcessor.h"

#include "MassCommonTypes.h"
#include "MassExecutionContext.h"

void FMassVelocityExecutor::Execute(FMassExecutionContext& Context) {
    constexpr auto Executor{[](FMassExecutionContext& context, Query& query) {
        auto const N{context.GetNumEntities()};
        auto const DeltaTime{context.GetDeltaTimeSeconds()};
        auto const Transforms{context.GetMutableFragmentView<FMassTransformFragment>()};
        auto const& Velocity{context.GetConstSharedFragment<FMassVelocityConstSharedFragment>()};

        auto const displacement{Velocity.Velocity * DeltaTime};
        for (int32 i{0}; i < N; ++i) {
            Transforms[i].Transform.AddToTranslation(displacement);
        }
    }};

    ForEachEntityChunk(Context, Accessors, std::move(Executor));
}

UMassVelocityProcessor::UMassVelocityProcessor()
    : EntityQuery(*this)
    , Executor(UE::Mass::FQueryExecutor::CreateQuery<FMassVelocityExecutor>(EntityQuery, this)) {
    AutoExecuteQuery = Executor;

    ExecutionOrder.ExecuteInGroup = UE::Mass::ProcessorGroupNames::Movement;
    SetProcessingPhase(EMassProcessingPhase::PrePhysics);
    ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::AllWorldModes);
    bAutoRegisterWithProcessingPhases = true;
}
