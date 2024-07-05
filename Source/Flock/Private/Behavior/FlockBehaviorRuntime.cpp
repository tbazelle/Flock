#include "Behavior/FlockBehaviorRuntime.h"

#include "Bird/BirdData.h" 

void UFlockBehaviorRuntime::RegisterBird(const TWeakObjectPtr<AActor>& Bird, const TWeakObjectPtr<UBirdData>& BirdData)
{
	// Here we don't do anything but this is the place to do a "per actor" init
}

void UFlockBehaviorRuntime::UnregisterBird(const TWeakObjectPtr<AActor>& Bird)
{
	// Here we don't do anything but this is the place to do a "per actor" deinit
}

void UFlockBehaviorRuntime::UpdateBirds(TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData>& Birds, const double WorldTime)
{
	// Idle behavior
}
