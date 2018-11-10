// Fill out your copyright notice in the Description page of Project Settings.
// –°µÿàDåç¨F

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "MiniCamera.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMiniCamera : public ASceneCapture2D
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMiniCamera();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ABaseCharacter* PlayerCharacter;

	
};
