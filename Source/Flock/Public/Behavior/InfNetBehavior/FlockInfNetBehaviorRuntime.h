#pragma once

#include "CoreMinimal.h"
#include "Behavior/RandomBehavior/FlockRandomBehaviorRuntime.h"
#include "FlockInfNetBehaviorRuntime.generated.h"

class UFlockInfNetBehaviorData;

UCLASS()
class FLOCK_API UFlockInfNetBehaviorRuntime : public UFlockRandomBehaviorRuntime
{
	GENERATED_BODY()

	// Ctor & Dtor
public:
	UFlockInfNetBehaviorRuntime() = default;
	virtual ~UFlockInfNetBehaviorRuntime() override = default;

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
	TWeakObjectPtr<UFlockInfNetBehaviorData> InfNetData;
	double LastUpdateTime = 0;
	
private:
	TArray<TWeakObjectPtr<AActor>> InfNetBirds;
};
