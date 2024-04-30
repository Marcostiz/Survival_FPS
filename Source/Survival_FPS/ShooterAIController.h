// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_FPS_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

private:
	//Parámetro que indica el BehaviourTree a seguir por la IA
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
};


