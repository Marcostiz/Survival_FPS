// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_FPS_API UBTService_PlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
	//Servicio creado para el nodo de decisión del árbol en el que se aplica la secuencia de seguir
	// y disparar al player, se usa para actualizar la posición del player entre disparos
public:
	//Constructor para cambiar el nomber del servicio en el editor
	UBTService_PlayerLocation();

protected:
	//Override del tick del nodo para añadir funcionalidades
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
