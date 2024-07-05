#include "Behavior/RandomBehavior/FlockRandomBehaviorData.h"

#include "Behavior/RandomBehavior/FlockRandomBehaviorRuntime.h"

TObjectPtr<UFlockBehaviorRuntime> UFlockRandomBehaviorData::CreateRuntime(const double WorldTime)
{
	TObjectPtr<UFlockRandomBehaviorRuntime> runtime = NewObject<UFlockRandomBehaviorRuntime>();
	runtime->RandomData = this;
	runtime->LastUpdateTime = WorldTime;
	return runtime;
}
