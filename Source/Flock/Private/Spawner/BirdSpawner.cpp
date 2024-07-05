#include "Spawner/BirdSpawner.h"

#include "Engine/World.h"
#include "TimerManager.h"

#include "FlockSubsystem.h"

ABirdSpawner::ABirdSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABirdSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance()->GetSubsystem<UFlockSubsystem>()->RegisterBirdSpawner(this, SpawnerData);
}

void ABirdSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetGameInstance()->GetSubsystem<UFlockSubsystem>()->UnregisterBirdSpawner(this);
	
	Super::EndPlay(EndPlayReason);
}

void ABirdSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
