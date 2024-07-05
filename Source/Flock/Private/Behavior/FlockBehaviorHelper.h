#pragma once

#include "Bird/BirdData.h"

namespace FlockBehaviorHelper
{
	// TTuple<Bird, distance, dot>
	TArray<TTuple<TWeakObjectPtr<AActor>, float, float>> GetClosestBirds(int NumBirds, const TWeakObjectPtr<AActor>& Bird, TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData>& Birds, float VisionAngle = 180);
	void MoveBirdForward(FBirdRuntimeData& BirdRuntimeData, double DeltaTime);
	void RotateBirdToward(FBirdRuntimeData& BirdRuntimeData, const FVector& Direction, double DeltaTime);
};
