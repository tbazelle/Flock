#include "Behavior/InfNetBehavior/FlockInfNetBehaviorData.h"

#include "Behavior/InfNetBehavior/FlockInfNetBehaviorRuntime.h"

UFlockInfNetBehaviorData::UFlockInfNetBehaviorData()
{
	AngleInfluenceOnAlong.GetRichCurve()->AddKey(0, 1);
	AngleInfluenceOnToward.GetRichCurve()->AddKey(0, 1);
	DistanceInfluenceOnAlong.GetRichCurve()->AddKey(0, 1);
	DistanceInfluenceOnToward.GetRichCurve()->AddKey(0, 1);
}

TObjectPtr<UFlockBehaviorRuntime> UFlockInfNetBehaviorData::CreateRuntime(const double WorldTime)
{
	TObjectPtr<UFlockInfNetBehaviorRuntime> runtime = NewObject<UFlockInfNetBehaviorRuntime>();
	runtime->InfNetData = this;
	runtime->LastUpdateTime = WorldTime;
	return runtime;
}
