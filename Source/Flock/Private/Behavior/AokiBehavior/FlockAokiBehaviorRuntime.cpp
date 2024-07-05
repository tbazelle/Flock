#include "Behavior/AokiBehavior/FlockAokiBehaviorRuntime.h"

#include "Bird/BirdData.h"
#include "Behavior/AokiBehavior/FlockAokiBehaviorData.h"
#include "Behavior/FlockBehaviorHelper.h"

void UFlockAokiBehaviorRuntime::RegisterBird(const TWeakObjectPtr<AActor>& Bird, const TWeakObjectPtr<UBirdData>& BirdData)
{
	check(Bird.IsValid());
	AokiBirds.Add(Bird);
}

void UFlockAokiBehaviorRuntime::UnregisterBird(const TWeakObjectPtr<AActor>& Bird)
{
	check(Bird.IsValid());
	check(AokiBirds.Contains(Bird));
	AokiBirds.Remove(Bird);
}

void UFlockAokiBehaviorRuntime::UpdateBirds(TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData>& Birds, const double WorldTime)
{
	// Clean AokiBirds
	AokiBirds = AokiBirds.FilterByPredicate([&Birds](const TWeakObjectPtr<AActor>& elt)
	{
		return elt.IsValid() && Birds.Contains(elt);
	});

	if (!AokiData.IsValid())
	{
		return;
	}

	for (; LastUpdateTime < WorldTime; LastUpdateTime += AokiData->UpdateInterval)
	{
		// Update Bird
		for (TWeakObjectPtr<AActor>& bird : AokiBirds)
		{
			if (Birds[bird].LastUpdateTime < LastUpdateTime)
			{
				UpdateBird(bird, Birds, AokiData->UpdateInterval);
				Birds[bird].LastUpdateTime = LastUpdateTime;
			}
		}
	}
}

void UFlockAokiBehaviorRuntime::UpdateBird(const TWeakObjectPtr<AActor>& Bird, TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData>& Birds, float DeltaTime) const
{
	FVector influenceAccRe = FVector::Zero();
	FVector influenceAccAl = FVector::Zero();
	FVector influenceAccAt = FVector::Zero();
	const float rer = AokiData->RepulsionRadius;
	const float alr = AokiData->AlignmentRadius;
	const float atr = AokiData->AttractionRadius;

	FBirdRuntimeData& birdRuntimeData = Birds[Bird];

	for (const TTuple<TWeakObjectPtr<AActor>, float, float>& elt : FlockBehaviorHelper::GetClosestBirds(AokiData->MaxNumberOfInfluence, Bird, Birds, AokiData->VisionAngle))
	{
		FBirdRuntimeData& targetRuntimeData = Birds[elt.Get<0>()];
		const float& distance = elt.Get<1>();
		const FVector diff = (targetRuntimeData.BirdTransform.GetLocation() - birdRuntimeData.BirdTransform.GetLocation()).GetSafeNormal();  
		if (distance < rer)
		{
			influenceAccRe -= diff;
		}
		else if (distance < alr)
		{
			influenceAccAl += targetRuntimeData.BirdTransform.GetRotation().Vector();
		}
		else if (distance < atr)
		{
			influenceAccAt += diff;
		}
	}

	FVector influenceAcc = FVector::Zero();
	if (influenceAccRe.SquaredLength() > UE_SMALL_NUMBER)
	{
		influenceAcc = influenceAccRe;
	}
	else if (influenceAccAl.SquaredLength() > UE_SMALL_NUMBER || influenceAccAt.SquaredLength() > UE_SMALL_NUMBER)
	{
		influenceAcc = influenceAccAl + influenceAccAt;
	}

	FlockBehaviorHelper::RotateBirdToward(birdRuntimeData, influenceAcc, DeltaTime);
	FlockBehaviorHelper::MoveBirdForward(birdRuntimeData, DeltaTime);
}
