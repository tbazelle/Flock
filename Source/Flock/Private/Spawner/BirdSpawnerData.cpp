#include "Spawner/BirdSpawnerData.h"

FBirdSpawnerRuntimeData UBirdSpawnerData::CreateRuntimeData(TWeakObjectPtr<AActor> BirdSpawner)
{
	check(BirdSpawner.IsValid());
	
	FBirdSpawnerRuntimeData runtimeData;

	runtimeData.BirdSpawner = BirdSpawner;
	runtimeData.SpawnedBirds.Reset();
	runtimeData.BirdSpawnerData = this;
	runtimeData.LastSpawnTime= BirdSpawner->GetWorld()->GetTimeSeconds();

	return runtimeData;
}
