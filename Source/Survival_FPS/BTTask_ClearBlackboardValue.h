// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearBlackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_FPS_API UBTTask_ClearBlackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	//Tarea del nodo del Behaviour Tree que limpia el valor del blackboard
public:
	//Constructor en el que se modifica el nombre de la tarea en el editor
	UBTTask_ClearBlackboardValue();

protected:
	//Override de ExecuteTask para añadir funcionalidades
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
