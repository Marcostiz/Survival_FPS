// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SURVIVAL_FPS_API AGun : public AActor
{
	GENERATED_BODY()
	
	//Clase que gestiona el arma y sus parámetros
public:	
	// Sets default values for this actor's properties
	AGun();

	//Función que alplica el disparo del arma
	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//El root del componente
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	//El mesh del componente
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	//La partícula que se emite al disparar
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	//La partícula que se emite en el lugar que se recibe el impacto del disparo
	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	//Rango máximo del arma
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	//Daño que aplica el arma
	UPROPERTY(EditAnywhere)
	float Damage = 10;

	//Munición actual del arma
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CurrentAMMO;

	//Munición máxima del arma
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxAMMO = 10;
};
