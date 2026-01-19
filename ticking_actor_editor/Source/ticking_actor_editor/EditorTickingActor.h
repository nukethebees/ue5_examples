// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "EditorTickingActor.generated.h"

UCLASS()
class AEditorTickingActor : public AActor {
    GENERATED_BODY()
  public:
    AEditorTickingActor();

    virtual void Tick(float delta_time) override;

#if WITH_EDITOR
    virtual bool ShouldTickIfViewportsOnly() const override { return true; }
#endif
};
