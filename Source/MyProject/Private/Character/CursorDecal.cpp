// Fill out your copyright notice in the Description page of Project Settings.

#include "CursorDecal.h"
#include "Components/SceneComponent.h"
#include "Components/DecalComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Components/BoxComponent.h"

// Sets default values
ACursorDecal::ACursorDecal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	RootComponent = DefaultRootComponent;
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>(TEXT("CursorToWorld"));
	CursorToWorld->SetupAttachment(RootComponent);

	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->RelativeRotation = FRotator(90.0f, 0, 0);

	// ¼ì²âÊó±êµã»÷Ìù»¨µÄÅö×²
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetBoxExtent(FVector(20.0f, 34.0f, 34.0f));
	BoxComponent->SetRelativeRotation(FRotator(90.0f, 0, 0).Quaternion());

	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAssest(TEXT("Material'/Game/Texures/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAssest.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAssest.Object);
	}
}

// Called when the game starts or when spawned
void ACursorDecal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACursorDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACursorDecal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor == GetOwner())
	{
		Destroy();
	}
}

