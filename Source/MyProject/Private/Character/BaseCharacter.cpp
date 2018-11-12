// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "LogMacros.h"
#include "Engine/Engine.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObjectBaseUtility.h"
#include "GameFramework//Pawn.h"
#include "Math/Axis.h"
#include "Math/RotationMatrix.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "CursorDecal.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Public/UserWidget/MainUserWidget.h"
#include "Engine/DataTable.h"
#include "Public/Character/PlayerInfo.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	PrimaryActorTick.bCanEverTick = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	FollowCamera->SetupAttachment(CameraBoom);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->RelativeRotation = FRotator(-20.0f, 0, 0);
	// 移动方式
	bUseControllerRotationYaw = false;
	CameraBoom->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	ReadData();
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	PlayerController->bShowMouseCursor = true;
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *GetName());
	MainUserWidget = CreateWidget<UMainUserWidget>(GetWorld(), LoadClass<UMainUserWidget>(this, TEXT("WidgetBlueprint'/Game/Blueprints/UserWidget/WBP_Main.WBP_Main_C'")));
	MainUserWidget->AddToViewport(); 
}

void ABaseCharacter::MoveForward(float Axis)
{
	// X(Roll) Y(Pitch) Z(Yaw)
	if (Controller != NULL && Axis != 0)
	{
		if (HasCursorMoveCommand)
		{
			CancelMoveToCursor();
		}
		const FRotator CurrentDirection = Controller->GetControlRotation();
		const FRotator YawRotation(0, CurrentDirection.Yaw, 0);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void ABaseCharacter::MoveRight(float Axis)
{
	// X(Roll) Y(Pitch) Z(Yaw)
	if (Controller != NULL && Axis != 0)
	{
		if (HasCursorMoveCommand)
		{
			CancelMoveToCursor();
		}
		const FRotator CurrentDirection = Controller->GetControlRotation();
		const FRotator YawRotation(0, CurrentDirection.Yaw, 0);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void ABaseCharacter::OnDestinationPressed()	
{
	CancelMoveToCursor();
	HasCursorMoveCommand = true;
	FHitResult Hit;
	PlayerController->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit);
	if (Hit.bBlockingHit)
	{
		// UE_LOG(LogTemp, Warning, TEXT("%s"), *GetName());
		FActorSpawnParameters Params;
		Params.Owner = this;
		CurrentCursorDecal = GetWorld()->SpawnActor<ACursorDecal>(CursorDecal, Hit.Location, FRotator::ZeroRotator, Params);
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ABaseCharacter::SetNewMoveDestination(const FVector& DesLocation)
{
	float Distance = FVector::Dist(DesLocation, GetActorLocation());
	if (Distance > 120.0f)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(PlayerController, DesLocation);
	}
}

void ABaseCharacter::CancelMoveToCursor()
{
	if (CurrentCursorDecal != nullptr)
	{
		// 取消鼠标移动
		HasCursorMoveCommand = false;
		GetCharacterMovement()->StopMovementImmediately();
		// 销毁鼠标点击贴花
		CurrentCursorDecal->Destroy();
		CurrentCursorDecal = nullptr;
	}
}

void ABaseCharacter::CameraZoomIn()
{
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength - CameraZoomAngle, MinCameraZoom_V, MaxCameraZoom_V);
}

void ABaseCharacter::CameraZoomOut()
{
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength + CameraZoomAngle, MinCameraZoom_V, MaxCameraZoom_V);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FRotator Rotator = Controller->GetControlRotation();
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Rotator.Yaw);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ABaseCharacter::CameraZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ABaseCharacter::CameraZoomOut);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &ABaseCharacter::OnDestinationPressed);
}

void ABaseCharacter::ReadData()
{
	UDataTable* PlayerInfo = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("DataTable'/Game/Blueprints/Info/PkayerInfo.PkayerInfo'")));
	if (PlayerInfo == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInfo Load Failure"));
	}
	FPlayerInfo* RowData = PlayerInfo->FindRow<FPlayerInfo>(TEXT("1"), NULL, false);
	if (PlayerInfo != NULL)
	{
		SetCurrentPlayerName(RowData->CharacterName);
		SetCurrentHp(RowData->StartHp);
		SetCurrentMp(RowData->StartMp);
		TotalHp = RowData->StartHp;
		TotalMp = RowData->StartMp;
		CurrentLevel = 1;
	}
}

