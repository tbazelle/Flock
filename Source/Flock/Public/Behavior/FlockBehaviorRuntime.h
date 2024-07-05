#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FlockBehaviorRuntime.generated.h"

UCLASS()
class FLOCK_API UFlockBehaviorRuntime : public UObject
{
	GENERATED_BODY()

	// Method
public:
	virtual void RegisterBird(const TWeakObjectPtr<AActor>& Bird, const TWeakObjectPtr<UBirdData>& BirdData);
	virtual void UnregisterBird(const TWeakObjectPtr<AActor>& Bird);
	virtual void UpdateBirds(TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData>& Birds, const double WorldTime);
};
