#include "Bird/BirdComponent.h"

#include "FlockSubsystem.h"

UBirdComponent::UBirdComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBirdComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetGameInstance()->GetSubsystem<UFlockSubsystem>()->UnregisterBird(GetOwner());
	Super::EndPlay(EndPlayReason);
}

void UBirdComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FTransform desiredTransform = GetWorld()->GetGameInstance()->GetSubsystem<UFlockSubsystem>()->GetDesiredTransform(GetOwner()); 
	if (AActor* Owner = GetOwner())
	{
		Owner->SetActorTransform(desiredTransform);
	}
}
