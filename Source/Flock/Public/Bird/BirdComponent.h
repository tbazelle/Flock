#pragma once

#include "CoreMinimal.h"

#include "BirdComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FLOCK_API UBirdComponent : public UActorComponent
{
	GENERATED_BODY()

	// Ctor & Dtor
public:
	UBirdComponent();
	virtual ~UBirdComponent() override = default;

	// UActorComponent
public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
