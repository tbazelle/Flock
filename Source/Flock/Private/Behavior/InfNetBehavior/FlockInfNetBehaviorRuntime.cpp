#include "Behavior/InfNetBehavior/FlockInfNetBehaviorRuntime.h"

#include "Bird/BirdData.h"
#include "Behavior/InfNetBehavior/FlockInfNetBehaviorData.h"
#include "Behavior/FlockBehaviorHelper.h"

void UFlockInfNetBehaviorRuntime::RegisterBird(const TWeakObjectPtr<AActor>& Bird,
	const TWeakObjectPtr<UBirdData>& BirdData)
{
	check(Bird.IsValid());
	InfNetBirds.Add(Bird);
}

void UFlockInfNetBehaviorRuntime::UnregisterBird(const TWeakObjectPtr<AActor>& Bird)
{
	check(Bird.IsValid());
	check(InfNetBirds.Contains(Bird));
	InfNetBirds.Remove(Bird);
}

void UFlockInfNetBehaviorRuntime::UpdateBirds(TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData>& Birds,
	const double WorldTime)
{
	// Clean AokiBirds
	InfNetBirds = InfNetBirds.FilterByPredicate([&Birds](const TWeakObjectPtr<AActor>& elt)
	{
		return elt.IsValid() && Birds.Contains(elt);
	});

	if (!InfNetData.IsValid())
	{
		return;
	}

	for (; LastUpdateTime < WorldTime; LastUpdateTime += InfNetData->UpdateInterval)
	{
		// Update Bird
		for (TWeakObjectPtr<AActor>& bird : InfNetBirds)
		{
			if (Birds[bird].LastUpdateTime < LastUpdateTime)
			{
				UpdateBird(bird, Birds, InfNetData->UpdateInterval);
				Birds[bird].LastUpdateTime = LastUpdateTime;
			}
		}
	}

}

void UFlockInfNetBehaviorRuntime::UpdateBird(const TWeakObjectPtr<AActor>& Bird, TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData>& Birds, float DeltaTime) const
{
	FVector influenceToward = FVector::Zero();
	FVector influenceAlong = FVector::Zero();

	FBirdRuntimeData& birdRuntimeData = Birds[Bird];
	for (const TTuple<TWeakObjectPtr<AActor>, float, float>& elt : FlockBehaviorHelper::GetClosestBirds(InfNetData->NumberOfInfluence, Bird, Birds, InfNetData->VisionAngle))
	{
		FBirdRuntimeData& targetRuntimeData = Birds[elt.Get<0>()];
		const float& distance = elt.Get<1>();
		const float& dot = elt.Get<2>();
		const FVector toward = (targetRuntimeData.BirdTransform.GetLocation() - birdRuntimeData.BirdTransform.GetLocation()).GetSafeNormal();
		const FVector along = targetRuntimeData.BirdTransform.GetRotation().Vector();

		influenceToward += toward * InfNetData->DistanceInfluenceOnToward.GetRichCurve()->Eval(distance) * InfNetData->AngleInfluenceOnToward.GetRichCurve()->Eval(FMath::Acos(dot));
		influenceAlong += along * InfNetData->DistanceInfluenceOnAlong.GetRichCurve()->Eval(distance) * InfNetData->AngleInfluenceOnAlong.GetRichCurve()->Eval(FMath::Acos(dot));
	}
	const FVector influenceTotal = influenceToward + influenceAlong;
#if !UE_BUILD_SHIPPING
	// DrawDebugLine(Bird->GetWorld(), birdRuntimeData.BirdTransform.GetLocation(), birdRuntimeData.BirdTransform.GetLocation() + influenceTotal * 100, FColor::Red);
#endif
	FlockBehaviorHelper::RotateBirdToward(birdRuntimeData, influenceTotal, DeltaTime);
	FlockBehaviorHelper::MoveBirdForward(birdRuntimeData, DeltaTime);
}
