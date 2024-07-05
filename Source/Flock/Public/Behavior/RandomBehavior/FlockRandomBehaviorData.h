#pragma once

#include "CoreMinimal.h"
#include "Behavior/FlockBehaviorData.h"
#include "FlockRandomBehaviorData.generated.h"

UCLASS()
class FLOCK_API UFlockRandomBehaviorData : public UFlockBehaviorData
{
	GENERATED_BODY()

	// Ctor & Dtor
public:
	UFlockRandomBehaviorData() = default;
	virtual ~UFlockRandomBehaviorData() override = default;

	// UFlockBehaviorData
public:
	virtual TObjectPtr<UFlockBehaviorRuntime> CreateRuntime(const double WorldTime) override;

	// Members
public:
	UPROPERTY(EditAnywhere, Category = "Flock")
	float UpdateInterval = 1.f/60.f;

};
