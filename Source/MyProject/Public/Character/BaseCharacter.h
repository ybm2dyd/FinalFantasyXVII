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

	/** 用戶主界面 */
	class UMainUserWidget* MainUserWidget;

	class APlayerController* PlayerController;

	/** 是否使用鼠标控制移动 */
	bool HasCursorMoveCommand = false;

	/** 上一个鼠标点击贴花 */
	class ACursorDecal* CurrentCursorDecal;

	/** 鏡頭縮放最小值 */
	UPROPERTY(EditAnywhere, Category = "Camera")
	float MinCameraZoom_V = 75.0f;

	/** 鏡頭縮放最大值 */
	UPROPERTY(EditAnywhere, Category = "Camera")
	float MaxCameraZoom_V = 1000.0f;

	/** 鏡頭縮放角度 */
	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraZoomAngle = 25.0f;

protected:
	/** 角色名字 */
	FString PlayerName;
	/** 当前血量 */
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	float CurrentHp;
	/** 上限血量 */
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	float TotalHp;
	/** 当前蓝量 */
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	float CurrentMp;
	/** 上限蓝量 */
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	float TotalMp;
	/** 当前经验 */
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	uint32 CurrentExp;
	/** 当前等级 */
	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	uint32 CurrentLevel;

	void ReadData();

public:
	FORCEINLINE void SetCurrentHp(float TheHp) { CurrentHp = TheHp; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	FORCEINLINE void SetCurrentMp(float TheMp) { CurrentMp = TheMp; }
	FORCEINLINE float GetCurrentMp() { return CurrentMp; }
	FORCEINLINE void SetCurrentExp(float TheExp) { CurrentHp = TheExp; }
	FORCEINLINE float GetCurrentExp() { return CurrentExp; }
	FORCEINLINE void SetCurrentPlayerName(FString ThePlayerName) { PlayerName = ThePlayerName; }
	FORCEINLINE FString GetCurrentPlayerName() { return PlayerName; }
};
