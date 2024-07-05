#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BirdSpawner.generated.h"

class UBirdSpawnerData;

UCLASS()
class FLOCK_API ABirdSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABirdSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Flock")
	TObjectPtr<UBirdSpawnerData> SpawnerData;

// private:
// 	void SpawnBird();
//
// 	TArray<TObjectPtr<AActor>> SpawnedBirds;
// 	FTimerHandle SpawnTimerHandle;
};
