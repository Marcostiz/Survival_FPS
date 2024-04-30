// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	//Comprueba que la variable del Behaviour Tree no est� vac�a
	if (AIBehavior != nullptr)
	{
		//En caso de no estar vac�a, activa el BehaviourTree
		RunBehaviorTree(AIBehavior);
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}