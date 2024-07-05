#include "FlockSubsystem.h"

void UFlockSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UFlockSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UFlockSubsystem::Tick(float DeltaTime)
{
	if (GetWorld())
	{
		CleanAllSpawner();
		CleanAllBird();
		CleanAllBehaviors();

		UpdateAllSpawner();
		UpdateLeash();
		UpdateAllBehaviors();
	}
}

TStatId UFlockSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UBirdSubSystem, STATGROUP_Tickables);
}

bool UFlockSubsystem::IsTickable() const
{
	return true;
}

void UFlockSubsystem::RegisterBirdSpawner(const TWeakObjectPtr<AActor>& BirdSpawner, const TWeakObjectPtr<UBirdSpawnerData>& BirdSpawnerData)
{
	check(BirdSpawner.IsValid());
	check(BirdSpawnerData.IsValid());
	check(!BirdSpawners.Contains(BirdSpawner));

	BirdSpawners.Add(BirdSpawner, BirdSpawnerData->CreateRuntimeData(BirdSpawner));
}

void UFlockSubsystem::UnregisterBirdSpawner(const TWeakObjectPtr<AActor>& BirdSpawner)
{
	check(BirdSpawner.IsValid());
	BirdSpawners.Remove(BirdSpawner);
}

void UFlockSubsystem::RegisterBird(const TWeakObjectPtr<AActor>& Bird, const TWeakObjectPtr<UBirdData>& BirdData)
{
	check(Bird.IsValid());
	check(BirdData.IsValid());
	check(BirdData->FlockBehaviorData);
	check(!Birds.Contains(Bird));

	Birds.Add(Bird, BirdData->CreateRuntimeData(Bird));
	if (!Behaviors.Contains(BirdData->FlockBehaviorData))
	{
		Behaviors.Add(BirdData->FlockBehaviorData, BirdData->FlockBehaviorData->CreateRuntime(GetWorld()->GetTimeSeconds()));
	}
	Behaviors[BirdData->FlockBehaviorData]->RegisterBird(Bird, BirdData);
}

void UFlockSubsystem::UnregisterBird(const TWeakObjectPtr<AActor>& Bird)
{
	check(Bird.IsValid());
	if (Birds.Contains(Bird))
	{
		if (Birds[Bird].BirdData.IsValid() && Behaviors.Contains(Birds[Bird].BirdData->FlockBehaviorData))
		{
			Behaviors[Birds[Bird].BirdData->FlockBehaviorData]->UnregisterBird(Bird);
		}
		Birds.Remove(Bird);
	}
}

FTransform UFlockSubsystem::GetDesiredTransform(const TWeakObjectPtr<AActor>& Bird)
{
	if (Birds.Contains(Bird))
	{
		return Birds[Bird].BirdTransform;
	}
	return FTransform::Identity;
}

void UFlockSubsystem::CleanAllSpawner()
{
	BirdSpawners = BirdSpawners.FilterByPredicate([](const TPair<TWeakObjectPtr<AActor>, FBirdSpawnerRuntimeData>& elt)
	{
		return elt.Value.BirdSpawner.IsValid() && elt.Value.BirdSpawnerData.IsValid() && elt.Value.BirdSpawnerData->BirdData != nullptr;
	});
}

void UFlockSubsystem::CleanAllBird()
{
	Birds = Birds.FilterByPredicate([](const TPair<TWeakObjectPtr<AActor>, FBirdRuntimeData>& elt)
	{
		return elt.Value.BirdActor.IsValid() && elt.Value.BirdData.IsValid();
	});
}

void UFlockSubsystem::CleanAllBehaviors()
{
	Behaviors = Behaviors.FilterByPredicate([](const TPair<TWeakObjectPtr<UFlockBehaviorData>, TObjectPtr<UFlockBehaviorRuntime>>& elt)
	{
		return elt.Key.IsValid() && elt.Value;
	});
}

void UFlockSubsystem::UpdateAllSpawner()
{
	for (TTuple<TWeakObjectPtr<AActor>, FBirdSpawnerRuntimeData>& runtimeData : BirdSpawners)
	{
		UpdateSpawner(runtimeData.Key, runtimeData.Value);
	}
}

void UFlockSubsystem::UpdateSpawner(TWeakObjectPtr<AActor>& SpawnerActor, FBirdSpawnerRuntimeData& SpawnerRuntimeData)
{
	const double worldTime = GetWorld()->GetTimeSeconds();
	const TWeakObjectPtr<UBirdSpawnerData>& spawnerData = SpawnerRuntimeData.BirdSpawnerData;
	TArray<TWeakObjectPtr<AActor>>& spawnedBirds = SpawnerRuntimeData.SpawnedBirds;
	TWeakObjectPtr<AActor>& birdSpawner = SpawnerRuntimeData.BirdSpawner;
	double& lastSpawnTime = SpawnerRuntimeData.LastSpawnTime;

	for (; lastSpawnTime < worldTime && spawnedBirds.Num() < spawnerData->MaxActorCount; lastSpawnTime += spawnerData->SpawnInterval)
	{
		// Spawn actor
		FActorSpawnParameters SpawnParams;
		AActor* spawnedBird = GetWorld()->SpawnActor<AActor>(spawnerData->ActorToSpawn, birdSpawner->GetActorLocation() + spawnerData->RandomizeRadius * FMath::VRand(), FMath::VRand().Rotation(), SpawnParams);
		if (spawnedBird != nullptr)
		{
			spawnedBirds.Add(spawnedBird);
		}
		// Create bird runtime data
		RegisterBird(spawnedBird, spawnerData->BirdData);
		Birds[spawnedBird].LeashAnchor = birdSpawner->GetActorLocation();
		Birds[spawnedBird].LeashRadius = spawnerData->LeashRadius;
	}
}

void UFlockSubsystem::UpdateLeash()
{
	const double worldTime = GetWorld()->GetTimeSeconds();
	for (TPair<TWeakObjectPtr<AActor>, FBirdRuntimeData>& bird : Birds)
	{
		FBirdRuntimeData& birdRuntime = bird.Value;
		FVector toLeash = birdRuntime.LeashAnchor - birdRuntime.BirdTransform.GetLocation();
		float leashDistance = toLeash.Length();
		double deltaTime = worldTime - birdRuntime.LastUpdateTime;
		if (deltaTime >= DBL_EPSILON && leashDistance >= birdRuntime.LeashRadius && toLeash.Normalize())
		{
			FQuat targetRotation = FRotationMatrix::MakeFromX(toLeash).ToQuat();
			FQuat newRotation = FMath::QInterpConstantTo(birdRuntime.BirdTransform.GetRotation(), targetRotation, deltaTime, birdRuntime.BirdData->TurnRate);
			birdRuntime.BirdTransform.SetRotation(newRotation);

			FVector targetPosition = birdRuntime.BirdTransform.GetLocation() + (birdRuntime.BirdData->BirdSpeed * deltaTime * birdRuntime.BirdTransform.GetRotation().Vector()); 
			birdRuntime.BirdTransform.SetLocation(targetPosition);

			birdRuntime.LastUpdateTime = worldTime;
		}
	}
}

void UFlockSubsystem::UpdateAllBehaviors()
{
	for (TTuple<TWeakObjectPtr<UFlockBehaviorData>, TObjectPtr<UFlockBehaviorRuntime>>& runtime : Behaviors)
	{
		runtime.Value->UpdateBirds(Birds, GetWorld()->GetTimeSeconds());
	}
}
