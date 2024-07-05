#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "BirdSpawnerData.generated.h"

class UBirdData;
struct FBirdSpawnerRuntimeData;

UCLASS()
class FLOCK_API UBirdSpawnerData : public UDataAsset
{
	GENERATED_BODY()

	// Method
public:
	FBirdSpawnerRuntimeData CreateRuntimeData(TWeakObjectPtr<AActor> BirdSpawner);

	// Bird Spawner Data
public:
	UPROPERTY(EditAnywhere, Category = "Flock")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "Flock")
	TObjectPtr<UBirdData> BirdData;

	UPROPERTY(EditAnywhere, Category = "Flock")
	double SpawnInterval = 1.f;

	UPROPERTY(EditAnywhere, Category = "Flock")
	float RandomizeRadius = 1.f;

	UPROPERTY(EditAnywhere, Category = "Flock")
	int32 MaxActorCount = 50.f;

	UPROPERTY(EditAnywhere, Category = "Flock")
	float LeashRadius = 1000.f;
};

USTRUCT()
struct FBirdSpawnerRuntimeData
{
	GENERATED_BODY()

	TWeakObjectPtr<AActor> BirdSpawner;
	TWeakObjectPtr<UBirdSpawnerData> BirdSpawnerData;
	TArray<TWeakObjectPtr<AActor>> SpawnedBirds;
	double LastSpawnTime;
};

