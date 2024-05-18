// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SURVIVAL_FPS_API AGun : public AActor
{
	GENERATED_BODY()
	
	//Clase que gestiona el arma y sus par�metros
public:	
	// Sets default values for this actor's properties
	AGun();

	//Funci�n que alplica el disparo del arma
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

	//La part�cula que se emite al disparar
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	//La part�cula que se emite en el lugar que se recibe el impacto del disparo
	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	//Rango m�ximo del arma
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	//Da�o que aplica el arma
	UPROPERTY(EditAnywhere)
	float Damage = 10;

	//Munici�n actual del arma
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CurrentAMMO;

	//Munici�n m�xima del arma
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxAMMO = 10;
};
