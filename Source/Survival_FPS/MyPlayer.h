// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"


class AGun;

UCLASS()
class SURVIVAL_FPS_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Shoot();

	void SetScore(int score);
	int GetScore();
	void SetAddToScoreWhenKilled(int score);
	int GetAddToScoreWhenKilled();

private:
	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void MoveRight(float AxisValue);
	void LookRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void SwitchWeapons();
	void SpawnWeapons();
	

	UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AGun>> GunClassArray;

	UPROPERTY(EditAnywhere)
	TArray<AGun*> GunArray;

	UPROPERTY(EditAnywhere)
	int ActiveIndex;

	UPROPERTY(EditAnywhere)
	bool isEnemy;

	UPROPERTY(EditAnywhere)
	int Score;

	UPROPERTY(EditAnywhere)
	int AddToScoreWhenKilled;
};
