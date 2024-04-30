// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
	//Se modifica el nombre en el editor para m�s claridad
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	//Se hace clear al valor de la blackboard key
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	//Se retorna que la tarea ha sido un �xito
	return EBTNodeResult::Succeeded;
}