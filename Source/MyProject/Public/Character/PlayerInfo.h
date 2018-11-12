// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "PlayerInfo.generated.h"

/**
 * 
 */
USTRUCT()
struct FPlayerInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "FPlayerInfo")
	FString CharacterName;
	UPROPERTY(EditAnywhere, Category = "FPlayerInfo")
	float StartHp;
	UPROPERTY(EditAnywhere, Category = "FPlayerInfo")
	float StartMp;
};
