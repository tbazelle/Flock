#pragma once

#include "CoreMinimal.h"
#include "Behavior/FlockBehaviorData.h"
#include "FlockInfNetBehaviorData.generated.h"

UCLASS()
class FLOCK_API UFlockInfNetBehaviorData : public UFlockBehaviorData
{
	GENERATED_BODY()

	// Ctor & Dtor
public:
	UFlockInfNetBehaviorData();
	virtual ~UFlockInfNetBehaviorData() override = default;

	// UFlockBehaviorData
public:
	virtual TObjectPtr<UFlockBehaviorRuntime> CreateRuntime(const double WorldTime) override;

	// Members
public:
	UPROPERTY(EditAnywhere, Category = "Flock")
	int NumberOfInfluence = 5;

	UPROPERTY(EditAnywhere, Category = "Flock")
	FRuntimeFloatCurve AngleInfluenceOnToward;

	UPROPERTY(EditAnywhere, Category = "Flock")
	FRuntimeFloatCurve AngleInfluenceOnAlong;

	UPROPERTY(EditAnywhere, Category = "Flock")
	FRuntimeFloatCurve DistanceInfluenceOnToward;

	UPROPERTY(EditAnywhere, Category = "Flock")
	FRuntimeFloatCurve DistanceInfluenceOnAlong;

	UPROPERTY(EditAnywhere, Category = "Flock")
	float VisionAngle = 90.f;

	UPROPERTY(EditAnywhere, Category = "Flock")
	float UpdateInterval = 1.f/60.f;
};
