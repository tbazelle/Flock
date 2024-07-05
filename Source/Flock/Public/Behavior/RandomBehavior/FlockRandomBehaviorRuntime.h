#pragma once

#include "CoreMinimal.h"
#include "Behavior/FlockBehaviorRuntime.h"
#include "FlockRandomBehaviorRuntime.generated.h"

class UFlockRandomBehaviorData;

UCLASS()
class FLOCK_API UFlockRandomBehaviorRuntime : public UFlockBehaviorRuntime
{
	GENERATED_BODY()

	// Ctor & Dtor
public:
	UFlockRandomBehaviorRuntime() = default;
	virtual ~UFlockRandomBehaviorRuntime() override = default;

	// UFlockBehaviorRuntime
public:
	virtual void RegisterBird(const TWeakObjectPtr<AActor>& Bird, const TWeakObjectPtr<UBirdData>& BirdData) override;
	virtual void UnregisterBird(const TWeakObjectPtr<AActor>& Bird) override;
	virtual void UpdateBirds(TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData>& Birds, const double WorldTime) override;

	// Member
public:
	TWeakObjectPtr<UFlockRandomBehaviorData> RandomData;
	double LastUpdateTime = 0;
private:
	TArray<TWeakObjectPtr<AActor>> RandomBirds;
};
