#pragma once

#include "CoreMinimal.h"
#include "Behavior/FlockBehaviorData.h"
#include "FlockAokiBehaviorData.generated.h"

UCLASS()
class FLOCK_API UFlockAokiBehaviorData : public UFlockBehaviorData
{
	GENERATED_BODY()

	// Ctor & Dtor
public:
	UFlockAokiBehaviorData() = default;
	virtual ~UFlockAokiBehaviorData() override = default;

	// UFlockBehaviorData
public:
	virtual TObjectPtr<UFlockBehaviorRuntime> CreateRuntime(const double WorldTime) override;

	// Members
public:
	UPROPERTY(EditAnywhere, Category = "Flock")
	float RepulsionRadius = 10.f;

	UPROPERTY(EditAnywhere, Category = "Flock")
	float AlignmentRadius = 100.f;

	UPROPERTY(EditAnywhere, Category = "Flock")
	float AttractionRadius = 300.f;

	UPROPERTY(EditAnywhere, Category = "Flock")
	float VisionAngle = 90.f;

	UPROPERTY(EditAnywhere, Category = "Flock")
	int MaxNumberOfInfluence = 5;

	UPROPERTY(EditAnywhere, Category = "Flock")
	double UpdateInterval = 1.f/60.f;
};
