// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_FPS_API ASimpleShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	//Base que hereda de GameModeBase para los diferentes modos de juego que se puedan llegar a implementar
public:
	//Función de la que heredarán los diferentes modos de juego, haciendo una cosa u otra dependiendo
	//de lo que se quiera hacer al matar a un personaje en esa modalidad
	virtual void PawnKilled(APawn* PawnKilled);
};
