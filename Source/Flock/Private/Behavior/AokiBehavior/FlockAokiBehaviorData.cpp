#include "Behavior/AokiBehavior/FlockAokiBehaviorData.h"

#include "Behavior/AokiBehavior/FlockAokiBehaviorRuntime.h"

TObjectPtr<UFlockBehaviorRuntime> UFlockAokiBehaviorData::CreateRuntime(const double WorldTime)
{
	TObjectPtr<UFlockAokiBehaviorRuntime> runtime = NewObject<UFlockAokiBehaviorRuntime>();
	runtime->AokiData = this;
	runtime->LastUpdateTime = WorldTime;
	return runtime;
}
