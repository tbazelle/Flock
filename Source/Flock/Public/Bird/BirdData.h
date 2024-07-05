#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "BirdData.generated.h"

class UFlockBehaviorData;
struct FBirdRuntimeData;

UCLASS()
class FLOCK_API UBirdData : public UDataAsset
{
	GENERATED_BODY()

	// Method
public:
	FBirdRuntimeData CreateRuntimeData(TWeakObjectPtr<AActor> BirdActor);

	// Properties
public:
	UPROPERTY(EditAnywhere, Category = "Flock")
	float BirdSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Flock")
	float TurnRate = UE_PI;

	UPROPERTY(EditAnywhere, Category = "Flock")
	TObjectPtr<UFlockBehaviorData> FlockBehaviorData;

};

USTRUCT()
struct FBirdRuntimeData
{
	GENERATED_BODY()

	TWeakObjectPtr<AActor> BirdActor;
	TWeakObjectPtr<UBirdData> BirdData;
	FTransform BirdTransform;
	FVector LeashAnchor;
	float LeashRadius;
	double LastUpdateTime;
};
