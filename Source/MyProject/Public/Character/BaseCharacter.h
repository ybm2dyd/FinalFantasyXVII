// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ObjectMacros.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MYPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Axis);

	void MoveRight(float Axis);

	void OnDestinationPressed();

	void SetNewMoveDestination(const FVector& DesLocation);

	void CancelMoveToCursor();

	void CameraZoomIn();

	void CameraZoomOut();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	UPROPERTY(VisibleAnywhere,Category = "Camera")
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent*  CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Mouse")
	TSubclassOf<class ACursorDecal> CursorDecal;

	/** �Ñ������� */
	class UMainUserWidget* MainUserWidget;

	class APlayerController* PlayerController;

	/** �Ƿ�ʹ���������ƶ� */
	bool HasCursorMoveCommand = false;

	/** ��һ����������� */
	class ACursorDecal* CurrentCursorDecal;

	/** �R�^�s����Сֵ */
	UPROPERTY(EditAnywhere, Category = "Camera")
	float MinCameraZoom_V = 75.0f;

	/** �R�^�s�����ֵ */
	UPROPERTY(EditAnywhere, Category = "Camera")
	float MaxCameraZoom_V = 1000.0f;

	/** �R�^�s�ŽǶ� */
	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraZoomAngle = 25.0f;
};
