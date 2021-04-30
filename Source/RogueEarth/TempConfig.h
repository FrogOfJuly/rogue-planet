// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TempConfig.generated.h"

USTRUCT(BlueprintType)
struct FHeatCapacity
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TempCoef;
};


UCLASS(BlueprintType)
class ROGUEEARTH_API UHeatConfig : public UDataAsset
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FHeatCapacity Leaves;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FHeatCapacity Trunk;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FHeatCapacity Ground;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FHeatCapacity Water;
}; 
