// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "MyPlayer.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	//Se modifica el nombre en el editor para más claridad
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	//Primero se comprueba que se obtenga bien el owner de la IA
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		//En caso de no obtener nada, falla la tarea
		return EBTNodeResult::Failed;
	}
	//En caso de no haber fallado, se obtiene al peón propietario de la IA
	AMyPlayer* Character = Cast<AMyPlayer>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr)
	{
		//En caso de no obtener nada, falla la tarea
		return EBTNodeResult::Failed;
	}
	//Y finalmente se llama a su función de disparar
	Character->Shoot();
	//Se retorna que la tarea ha sido un éxito
	return EBTNodeResult::Succeeded;
}
