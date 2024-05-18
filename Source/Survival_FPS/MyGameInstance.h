// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_FPS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	//Base que hereda de GameModeBase para los diferentes modos de juego que se puedan llegar a implementar
public:
	//Constructor de clase
	UMyGameInstance(const FObjectInitializer& ObjectInitialiaer);

	virtual void Init();

	//Funcion para que activar el viewport de muerte
	UFUNCTION(BlueprintCallable)
	void ShowDeathViewport();

private:
	TSubclassOf<class UUserWidget> DeathMenuClass;
	
};
