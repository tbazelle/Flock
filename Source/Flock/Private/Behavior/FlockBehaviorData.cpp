#include "Behavior/FlockBehaviorData.h"

#include "Behavior/FlockBehaviorRuntime.h"

TObjectPtr<UFlockBehaviorRuntime> UFlockBehaviorData::CreateRuntime(const double WorldTime)
{
	return NewObject<UFlockBehaviorRuntime>();
}
