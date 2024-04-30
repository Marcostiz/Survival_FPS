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

	//Clase creada para usar en los blueprints del player y los enemigos
	//Cuenta con las estad�sticas de los personajes y las diferentes acciones que pueden realizar
	//as� como la configuraci�n de los bindeos de dichas acciones
public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//Funci�n que comprueba si el personaje est� muerto
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Funci�n que aplica el da�o al personaje al recibir un disparo
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Funci�n que llama al m�todo de disparar del arma que se lleve equipada
	void Shoot();

	//Setters y getters de la puntuaci�n que lleva el personaje
	void SetScore(int score);
	int GetScore();

	//Getters y setters de la puntuaci�n que da el personaje al morir
	void SetAddToScoreWhenKilled(int score);
	int GetAddToScoreWhenKilled();

private:
	//Funci�n que se encarga de mover al personaje en el eje de su vector forward, tanto hacia 
	//delante como hacia atr�s
	void MoveForward(float AxisValue);

	//Funci�n que se encarga de mover la c�mara personaje para mirar arriba o abajo
	void LookUp(float AxisValue);

	//Funci�n que se encarga de mover al personaje en el eje de su vector right, tanto hacia la
	//derecha como hacia la izquierda
	void MoveRight(float AxisValue);

	//Funci�n que se encarga de mover la c�mara personaje para mirar a la derecha o a la izquierda
	void LookRight(float AxisValue);

	//Las siguientes dos funciones son optimizaciones de las funciones de mirar pero para su uso con
	//el mando, ya que nencesita adaptaci�n para ajustarse mejor a la sensibilidad
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	//Funci�n que se encarga de cambiar el arma equipada del personaje entre las 3 disponibles
	void SwitchWeapons();

	//Funci�n que se encarga de spawnear las armas del personaje
	void SpawnWeapons();
	
	//Par�metro que se usa en las funciones de adaptaci�n del movimiento de la c�mara con el mando
	//EditAnywhere para poder modificarlo desde el editor facilitando el ajuste del par�metro
	UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	//Par�metro que indica la vida m�xima del personaje
	//EditAnywhere para poder modificarlo desde el editor facilitando el ajuste del par�metro
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	//Par�metro que indica la vida actual del personaje
	//Solo visible para que no se pueda modificar en ning�n momento desde el editor
	UPROPERTY(VisibleAnywhere)
	float Health;

	//Par�metro que de la clase de nuestras armas, se le pasa luego en el editor
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;

	//Par�metro que almacena el arma en uso del personaje
	UPROPERTY()
	AGun* Gun;

	//Array de los distintos blueprints que heredan de AGun, la clase usada para las armas del personaje
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AGun>> GunClassArray;

	//Array de las armas del personaje
	UPROPERTY(EditAnywhere)
	TArray<AGun*> GunArray;

	//Par�metro que indica cu�l de las armas del array es la activa
	UPROPERTY(EditAnywhere)
	int ActiveIndex;

	//Par�metro para ayudar a diferenciar si es enemigo o no
	UPROPERTY(EditAnywhere)
	bool isEnemy;

	//Par�metro que indica el Score actual del personaje
	UPROPERTY(EditAnywhere)
	int Score;

	//Par�metro que indica los puntos que suben al score del personaje que lo mate
	UPROPERTY(EditAnywhere)
	int AddToScoreWhenKilled;
};
