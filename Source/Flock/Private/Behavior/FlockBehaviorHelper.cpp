#include "FlockBehaviorHelper.h"

TArray<TTuple<TWeakObjectPtr<AActor>, float, float>> FlockBehaviorHelper::GetClosestBirds(int NumBirds, const TWeakObjectPtr<AActor>& Bird, TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData>& Birds, float VisionAngle)
{
	TArray<TTuple<TWeakObjectPtr<AActor>, float, float>> heap;
	heap.Reserve(NumBirds);

	check(Birds.Contains(Bird));
	const FTransform& birdTransform = Birds[Bird].BirdTransform;
	const float minDot = FMath::Cos(FMath::DegreesToRadians(VisionAngle));

	auto HeapLessOperator = [](const TTuple<TWeakObjectPtr<AActor>, float, float>& a, const TTuple<TWeakObjectPtr<AActor>, float, float>& b)
	{
		return a.Get<1>() < b.Get<1>();	
	};
	
	for(TPair<TWeakObjectPtr<AActor>, FBirdRuntimeData>& elt : Birds)
	{
		if (Bird == elt.Key)
		{
			continue;
		}

		const FTransform& targetTransform = elt.Value.BirdTransform;
		const FVector direction = targetTransform.GetLocation() - birdTransform.GetLocation();
		const float birdDistance = direction.Length();
		const float dotToForward = birdDistance < UE_SMALL_NUMBER ? -1 : (direction / birdDistance).Dot(birdTransform.GetRotation().Vector());

		if (dotToForward < minDot)
		{
			continue;
		}
		
		if (heap.Num() < NumBirds)
		{
			heap.Add(TTuple<TWeakObjectPtr<AActor>, float, float>(elt.Key, birdDistance, dotToForward));
			// Maintain the heap property
			if (heap.Num() == NumBirds)
			{
				heap.Heapify(HeapLessOperator);
			}
		}
		else if (birdDistance < heap[0].Get<1>())
		{
			// Replace the farthest transform if the current one is closer
			heap[0] = TTuple<TWeakObjectPtr<AActor>, float, float>(elt.Key, birdDistance,  dotToForward);
			// Maintain the heap property
			heap.Heapify(HeapLessOperator);
		}
	}

	return MoveTemp(heap);
}

void FlockBehaviorHelper::MoveBirdForward(FBirdRuntimeData& BirdRuntimeData, double DeltaTime)
{
	const float birdSpeed = BirdRuntimeData.BirdData->BirdSpeed;
	FVector targetPosition = BirdRuntimeData.BirdTransform.GetLocation() + (birdSpeed * DeltaTime * BirdRuntimeData.BirdTransform.GetRotation().Vector()); 
	BirdRuntimeData.BirdTransform.SetLocation(targetPosition);
}

void FlockBehaviorHelper::RotateBirdToward(FBirdRuntimeData& BirdRuntimeData, const FVector& Direction, double DeltaTime)
{
	if (Direction.SquaredLength() > UE_SMALL_NUMBER)
	{
		FQuat targetRotation = FRotationMatrix::MakeFromX(Direction).ToQuat();
		FQuat newRotation = FMath::QInterpConstantTo(BirdRuntimeData.BirdTransform.GetRotation(), targetRotation, DeltaTime, BirdRuntimeData.BirdData->TurnRate);
		BirdRuntimeData.BirdTransform.SetRotation(newRotation);
	}
}
