// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_FPS_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	//Clase que hereda de PlayerController, usada para el GameMode
public:
	//Función que gestiona lo que pasa al acabar la partida
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	//Delay del respawn
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5;

	//Handler de tiempo
	FTimerHandle RestartTimer;
};
