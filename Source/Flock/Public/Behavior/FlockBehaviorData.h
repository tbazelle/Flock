#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "FlockBehaviorData.generated.h"

class UFlockBehaviorRuntime;

UCLASS()
class FLOCK_API UFlockBehaviorData : public UDataAsset
{
	GENERATED_BODY()

	// Method
public:
	virtual TObjectPtr<UFlockBehaviorRuntime> CreateRuntime(const double WorldTime);
};
