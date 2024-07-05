#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BirdComponent.h"
#include "BirdActor.generated.h"

UCLASS()
class FLOCK_API ABirdActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABirdActor();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> SphereMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBirdComponent> BirdComponent;
};
