// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocationIfSeen.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_FPS_API UBTService_PlayerLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
	//Servicio creado para el nodo raíz del árbol
public:
	//Constructor para cambiar el nomber del servicio en el editor
	UBTService_PlayerLocationIfSeen();

protected:
	//Override del tick del nodo para añadir funcionalidades
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
