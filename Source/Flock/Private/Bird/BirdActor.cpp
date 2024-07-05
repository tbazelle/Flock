#include "Bird/BirdActor.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstance.h"

ABirdActor::ABirdActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	RootComponent = SphereMesh;

	// Load a sphere mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	}

	// Create and set a green material
	static ConstructorHelpers::FObjectFinder<UMaterial> GreenMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial"));
	if (GreenMaterial.Succeeded())
	{
		UMaterialInstanceDynamic* GreenMaterialInstance = UMaterialInstanceDynamic::Create(GreenMaterial.Object, SphereMesh);
		GreenMaterialInstance->SetVectorParameterValue("BaseColor", FLinearColor::Green);
		SphereMesh->SetMaterial(0, GreenMaterialInstance);
	}

	BirdComponent = CreateDefaultSubobject<UBirdComponent>(TEXT("BirdComponent"));
}
