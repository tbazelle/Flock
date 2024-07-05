#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "Behavior/FlockBehaviorData.h"
#include "Behavior/FlockBehaviorRuntime.h"
#include "Bird/BirdData.h"
#include "Spawner/BirdSpawnerData.h"

#include "FlockSubsystem.generated.h"

UCLASS()
class FLOCK_API UFlockSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

	// Ctor & Dtor
public:
	UFlockSubsystem() = default;
	virtual ~UFlockSubsystem() override = default;

	// USubsystem
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// FTickableGameObject
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
	
	// Methods
public:
	void RegisterBirdSpawner(const TWeakObjectPtr<AActor>& BirdSpawner, const TWeakObjectPtr<UBirdSpawnerData>& BirdSpawnerData);
	void UnregisterBirdSpawner(const TWeakObjectPtr<AActor>& BirdSpawner);

	void RegisterBird(const TWeakObjectPtr<AActor>& Bird, const TWeakObjectPtr<UBirdData>& BirdData);
	void UnregisterBird(const TWeakObjectPtr<AActor>& Bird);

	FTransform GetDesiredTransform(const TWeakObjectPtr<AActor>& Bird);
	
private:
	void CleanAllSpawner();
	void CleanAllBird();
	void CleanAllBehaviors();

	void UpdateAllSpawner();
	void UpdateSpawner(TWeakObjectPtr<AActor>& SpawnerActor, FBirdSpawnerRuntimeData& SpawnerRuntimeData);
	void UpdateLeash();
	void UpdateAllBehaviors();

	// Member
private:
	TMap<TWeakObjectPtr<AActor>, FBirdSpawnerRuntimeData> BirdSpawners;
	TMap<TWeakObjectPtr<AActor>, FBirdRuntimeData> Birds;
	UPROPERTY(Transient)
	TMap<TWeakObjectPtr<UFlockBehaviorData>, TObjectPtr<UFlockBehaviorRuntime>> Behaviors;
};
