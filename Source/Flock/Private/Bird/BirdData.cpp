#include "Bird/BirdData.h"

FBirdRuntimeData UBirdData::CreateRuntimeData(TWeakObjectPtr<AActor> BirdActor)
{
	check(BirdActor.IsValid());

	FBirdRuntimeData runtimeData;
	runtimeData.BirdActor = BirdActor;
	runtimeData.BirdData = this;
	runtimeData.BirdTransform = BirdActor->GetTransform();
	runtimeData.LastUpdateTime = BirdActor->GetWorld()->GetTimeSeconds();
	return runtimeData;
}
