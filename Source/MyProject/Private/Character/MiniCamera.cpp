// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniCamera.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "Public/Character/BaseCharacter.h"

AMiniCamera::AMiniCamera()
{
	GetCaptureComponent2D()->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f)); 
}

void AMiniCamera::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	// •º•rŸo·¨Ó|°lÔ“tick£¬¸ÄÔÚË{ˆDŒ¬F
	//UE_LOG(LogTemp, Warning, TEXT("Tick"));
	//FVector TargetLocation(PlayerCharacter->GetActorLocation().X, PlayerCharacter->GetActorLocation().Y, GetActorLocation().Z);
	//SetActorLocation(TargetLocation);
}

void AMiniCamera::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
}
