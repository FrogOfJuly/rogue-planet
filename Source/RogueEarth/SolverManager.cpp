// Fill out your copyright notice in the Description page of Project Settings.


#include "SolverManager.h"

// Sets default values
ASolverManager::ASolverManager(): dx(0.001f), dt(0.01f), steps(50000), SolverEngine(dx, dt)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mantle_temerature = 900;
	surface_temperature = 293.0f;
	thermal_conductivity = 3.75f;
	specific_heat_capacity = 1077.0f;
	density = 2700.0f;
	upper_mantle = -40 * pow(10, 3);
	troposphere_height = 0;
	interval_to_mode = 5 * pow(10, 2);
	
	Init();
}

void ASolverManager::Restart()
{
	Init();
}

float ASolverManager::GetT()
{
	auto temps = SolverEngine.simulate_n_steps(draw_each);
	current_it++;
	return temps.back();
}

int ASolverManager::GetIterations()
{
	return iterations;
}

int ASolverManager::GetCurrentIteration()
{
	return current_it;
}

// Called when the game starts or when spawned
void ASolverManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASolverManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (current_it >= iterations)
	{
		EndSimulation();
	}
}

void ASolverManager::Init()
{
	SolverEngine.init_physics(mantle_temerature, surface_temperature, thermal_conductivity,
                              specific_heat_capacity, density, upper_mantle, troposphere_height,
                              interval_to_mode);

	SolverEngine.fill_with(surface_temperature);

	N = SolverEngine.eval_params.N;
	Tl = SolverEngine.phys_params.Tl;

	std::vector<double> border_cond;

	for (size_t i = 0; i < N; ++i)
	{
		border_cond.push_back(Tl + (surface_temperature - Tl) * (static_cast<float>(i)/static_cast<float>(N)));
	}

	SolverEngine.set_border_cond(border_cond);

	ticks_per_day = SolverEngine.ticks_per_day();
	SolverEngine.enable_radiation();

	draw_each = ticks_per_day*10;
	iterations = steps/draw_each;
	current_it = 0;
}

