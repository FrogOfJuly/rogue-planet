// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "engine.h"

#include "SolverManager.generated.h"

UCLASS()
class ROGUEEARTH_API ASolverManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASolverManager();
	
	UFUNCTION(BlueprintCallable)
	void Restart();
	
	UFUNCTION(BlueprintCallable)
	float GetT();

	UFUNCTION(BlueprintCallable)
	int GetIterations();

	UFUNCTION(BlueprintCallable)
	int GetCurrentIteration();

	UFUNCTION(BlueprintImplementableEvent)
	void EndSimulation();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Init();
	
private:
	double dx, dt;
	int steps;
	
	double mantle_temerature;
	double surface_temperature;
	double thermal_conductivity;
	double specific_heat_capacity;
	double density;
	double upper_mantle;
	double troposphere_height;
	double interval_to_mode;

	int N;
	double Tl;

	int ticks_per_day;
	int draw_each;
	int iterations;

	int current_it;
	
	engine SolverEngine;
};
