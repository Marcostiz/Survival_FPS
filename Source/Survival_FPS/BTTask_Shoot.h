// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_FPS_API UBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()
	
	//Tarea del nodo del Behaviour Tree que le indica que debe disparar
public:
	//Constructor en el que se modifica el nombre de la tarea en el editor
	UBTTask_Shoot();

protected:
	//Override de ExecuteTask para añadir funcionalidades
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
