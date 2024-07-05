#include "Behavior/RandomBehavior/FlockRandomBehaviorRuntime.h"

#include "Behavior/RandomBehavior/FlockRandomBehaviorData.h"
#include "Bird/BirdData.h"

void UFlockRandomBehaviorRuntime::RegisterBird(const TWeakObjectPtr<AActor>& Bird, const TWeakObjectPtr<UBirdData>& BirdData)
{
	check(Bird.IsValid());
	RandomBirds.Add(Bird);
}

void UFlockRandomBehaviorRuntime::UnregisterBird(const TWeakObjectPtr<AActor>& Bird)
{
	check(Bird.IsValid());
	check(RandomBirds.Contains(Bird));
	RandomBirds.Remove(Bird);
}

void UFlockRandomBehaviorRuntime::UpdateBirds(TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData>& Birds, const double WorldTime)
{
	// Clean AokiBirds
	RandomBirds = RandomBirds.FilterByPredicate([&Birds](const TWeakObjectPtr<AActor>& elt)
	{
		return elt.IsValid() && Birds.Contains(elt);
	});

	if (!RandomData.IsValid())
	{
		return;
	}

	for (; LastUpdateTime < WorldTime; LastUpdateTime += RandomData->UpdateInterval)
	{
		// Update Bird
		for (TWeakObjectPtr<AActor>& bird : RandomBirds)
		{
			FVector targetPosition = Birds[bird].BirdTransform.GetLocation() + (Birds[bird].BirdData->BirdSpeed * RandomData->UpdateInterval * FMath::VRand()); 
			Birds[bird].BirdTransform.SetLocation(targetPosition);

		}
	}
}
