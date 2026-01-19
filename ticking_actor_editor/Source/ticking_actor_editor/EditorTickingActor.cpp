#include "ticking_actor_editor/EditorTickingActor.h"

#include "Components/SceneComponent.h"

AEditorTickingActor::AEditorTickingActor() {
#if WITH_EDITOR
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
#else
    PrimaryActorTick.bCanEverTick = false;
#endif

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void AEditorTickingActor::Tick(float delta_time) {
    Super::Tick(delta_time);

#if WITH_EDITOR
    UE_LOG(LogTemp, Warning, TEXT("I'm ticking in the editor!"));
#endif
}
