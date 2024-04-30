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
	//Cuenta con las estadísticas de los personajes y las diferentes acciones que pueden realizar
	//así como la configuración de los bindeos de dichas acciones
public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//Función que comprueba si el personaje está muerto
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Función que aplica el daño al personaje al recibir un disparo
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Función que llama al método de disparar del arma que se lleve equipada
	void Shoot();

	//Setters y getters de la puntuación que lleva el personaje
	void SetScore(int score);
	int GetScore();

	//Getters y setters de la puntuación que da el personaje al morir
	void SetAddToScoreWhenKilled(int score);
	int GetAddToScoreWhenKilled();

private:
	//Función que se encarga de mover al personaje en el eje de su vector forward, tanto hacia 
	//delante como hacia atrás
	void MoveForward(float AxisValue);

	//Función que se encarga de mover la cámara personaje para mirar arriba o abajo
	void LookUp(float AxisValue);

	//Función que se encarga de mover al personaje en el eje de su vector right, tanto hacia la
	//derecha como hacia la izquierda
	void MoveRight(float AxisValue);

	//Función que se encarga de mover la cámara personaje para mirar a la derecha o a la izquierda
	void LookRight(float AxisValue);

	//Las siguientes dos funciones son optimizaciones de las funciones de mirar pero para su uso con
	//el mando, ya que nencesita adaptación para ajustarse mejor a la sensibilidad
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	//Función que se encarga de cambiar el arma equipada del personaje entre las 3 disponibles
	void SwitchWeapons();

	//Función que se encarga de spawnear las armas del personaje
	void SpawnWeapons();
	
	//Parámetro que se usa en las funciones de adaptación del movimiento de la cámara con el mando
	//EditAnywhere para poder modificarlo desde el editor facilitando el ajuste del parámetro
	UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	//Parámetro que indica la vida máxima del personaje
	//EditAnywhere para poder modificarlo desde el editor facilitando el ajuste del parámetro
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	//Parámetro que indica la vida actual del personaje
	//Solo visible para que no se pueda modificar en ningún momento desde el editor
	UPROPERTY(VisibleAnywhere)
	float Health;

	//Parámetro que de la clase de nuestras armas, se le pasa luego en el editor
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;

	//Parámetro que almacena el arma en uso del personaje
	UPROPERTY()
	AGun* Gun;

	//Array de los distintos blueprints que heredan de AGun, la clase usada para las armas del personaje
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AGun>> GunClassArray;

	//Array de las armas del personaje
	UPROPERTY(EditAnywhere)
	TArray<AGun*> GunArray;

	//Parámetro que indica cuál de las armas del array es la activa
	UPROPERTY(EditAnywhere)
	int ActiveIndex;

	//Parámetro para ayudar a diferenciar si es enemigo o no
	UPROPERTY(EditAnywhere)
	bool isEnemy;

	//Parámetro que indica el Score actual del personaje
	UPROPERTY(EditAnywhere)
	int Score;

	//Parámetro que indica los puntos que suben al score del personaje que lo mate
	UPROPERTY(EditAnywhere)
	int AddToScoreWhenKilled;
};
