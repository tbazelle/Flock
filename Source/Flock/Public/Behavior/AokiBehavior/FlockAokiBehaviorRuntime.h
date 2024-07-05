#pragma once

#include "CoreMinimal.h"
#include "Behavior/RandomBehavior/FlockRandomBehaviorRuntime.h"
#include "FlockAokiBehaviorRuntime.generated.h"

class UFlockAokiBehaviorData;

UCLASS()
class FLOCK_API UFlockAokiBehaviorRuntime : public UFlockRandomBehaviorRuntime
{
	GENERATED_BODY()

	// Ctor & Dtor
public:
	UFlockAokiBehaviorRuntime() = default;
	virtual ~UFlockAokiBehaviorRuntime() override = default;

	// UFlockRandomBehaviorRuntime
public:
	virtual void RegisterBird(const TWeakObjectPtr<AActor>& Bird, const TWeakObjectPtr<UBirdData>& BirdData) override;
	virtual void UnregisterBird(const TWeakObjectPtr<AActor>& Bird) override;
	virtual void UpdateBirds(TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData>& Birds, const double WorldTime) override;

	// Method
private:
	void UpdateBird(const TWeakObjectPtr<AActor>& Bird, TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData>& Birds, float DeltaTime) const;

	// Member
public:
	TWeakObjectPtr<UFlockAokiBehaviorData> AokiData;
	double LastUpdateTime = 0;
	
private:
	TArray<TWeakObjectPtr<AActor>> AokiBirds;
};
