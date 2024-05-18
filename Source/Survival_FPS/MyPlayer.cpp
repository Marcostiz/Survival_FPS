// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Se settean los valores iniciales de las variables y se esconde el hueso del arma que venía en el 
	//modelo
	Health = MaxHealth;
	ActiveIndex = 0;
	Score = 0;
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	
	//Finalmente se spawnean las armas en el personaje
	SpawnWeapons();
	
}

//Función que comprueba si el personaje está muerto
bool AMyPlayer::IsDead() const
{
	return Health <= 0;
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Función que aplica el daño al jugador, hace override a la función ya integrada en la clase de la que 
//hereda en MyPlayer, Character
float AMyPlayer::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//Primero obtenemos el valor del daño a recibir
	//luego se transforma con la función min para que nunca llegue a pasarse de la vida que le puede
	//restar al personaje
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	//UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	//Comprobación de si se ha matado al personaje que está recibiendo daño
	if (IsDead())
	{
		//En caso afirmativo se accede al modo de juego y se llama a la función que gestiona la
		//muerte de un peón en el juego
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		//Se hace que no se pueda mover más ni colisionar con él
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	}

	//Se devuelve el daño que se ha realizado, ya que seguimos heredando de la función TakeDamage que
	//retorna un float
	return DamageToApply;
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bindeos de las diferentes acciones o movimientos en los ejes del personaje
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyPlayer::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMyPlayer::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AMyPlayer::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AMyPlayer::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AMyPlayer::Shoot);
	PlayerInputComponent->BindAction(TEXT("SwitchWeapon"), EInputEvent::IE_Pressed, this, &AMyPlayer::SwitchWeapons);
	//PlayerInputComponent->BindAction(TEXT("PauseMenu"), EInputEvent::IE_Pressed, this, &AMyPlayer::Pause);
	//PlayerInputComponent->BindAction(TEXT("SwitchWeaponUp"), EInputEvent::IE_Pressed, this, &AMyPlayer::SwitchWeaponUp);
	//PlayerInputComponent->BindAction(TEXT("SwitchWeaponDown"), EInputEvent::IE_Pressed, this, &AMyPlayer::SwitchWeaponDown);
}

//Mueve al personaje en su vector forward dependiendo del valor dado por el eje, que se obtiene del
//input del player
void AMyPlayer::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

//Mueve la cámara del personaje rotando hacia arriba o abajo dependiendo del valor del eje, que se obtiene del
//input del player
void AMyPlayer::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

//Adaptación de la anterior función para el uso de mando
void AMyPlayer::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

//Mueve al personaje en su vector right dependiendo del valor dado por el eje, que se obtiene del
//input del player
void AMyPlayer::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

//Mueve la cámara del personaje rotando hacia derecha o izquierda dependiendo del valor del eje, que 
// se obtiene del input del player
void AMyPlayer::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

//Adaptación de la anterior función para el uso de mando
void AMyPlayer::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

//Llamada a la función de disparar del arma que llevemos equipada
void AMyPlayer::Shoot()
{
	Gun->PullTrigger();
}

//LLamada para activar el menu de pausa
//void AMyPlayer::Pause() 
//{
//	MyController = GetWorld()->GetFirstPlayerController();
//	UUserWidget* PauseScreen = CreateWidget(MyController, PauseMenuClass);
//	
//	if (!UGameplayStatics::IsGamePaused(GetWorld()))
//	{
//		if (PauseScreen != nullptr) {
//			PauseScreen->AddToViewport();
//			MyController->bShowMouseCursor = true;
//			MyController->bEnableClickEvents = true;
//			MyController->bEnableMouseOverEvents = true;
//			UGameplayStatics::SetGamePaused(GetWorld(), true);
//		}
//	}
//	else 
//	{
//		PauseScreen->RemoveFromParent();
//		PauseScreen->RemoveFromRoot();
//		MyController->bShowMouseCursor = false;
//		MyController->bEnableClickEvents = false;
//		MyController->bEnableMouseOverEvents = false;
//		UGameplayStatics::SetGamePaused(GetWorld(), false);
//	}
//}

//Setter y getter del score actual
void AMyPlayer::SetScore(int score)
{
	this->Score = score;
}

int AMyPlayer::GetScore()
{
	return Score;
}

//Setter y getter de la puntuación que da el personaje al morir
void AMyPlayer::SetAddToScoreWhenKilled(int score)
{
	this->AddToScoreWhenKilled = score;
}

int AMyPlayer::GetAddToScoreWhenKilled()
{
	return AddToScoreWhenKilled;
}

//Función que alterna entre las armas del personaje
void AMyPlayer::SwitchWeapons()
{
	//Se realiza esta comprobación para no salir del índice, del que sabemos que su máximo será 2,
	//ya que tenemos 3 armas y se modifica el valor del índice
	if (ActiveIndex == 2)
	{
		ActiveIndex = 0;
	}
	else
	{
		ActiveIndex++;
	}

	//Se comprueba que el índice aportado al array esté en los límites comprendidos
	if (GunArray.IsValidIndex(ActiveIndex))
	{
		//Se esconde el arma actual, se cambia el arma equipada por la indicada del índice,
		//se revela el arma equipada y se settea el owner de nuevo a nuestro personaje
		//por asegurarnos de que sea el correcto
		Gun->SetActorHiddenInGame(true);
		Gun = GunArray[ActiveIndex];
		Gun->SetActorHiddenInGame(false);
		Gun->SetOwner(this);
	}	
}

//Función que equipa el arma y añade todas a nuestro "inventario"
void AMyPlayer::SpawnWeapons()
{
	//Se itera en el array de blueprints de armas que heredan de nuestra clase Gun
	for (int32 i = 0; i < GunClassArray.Num(); i++)
	{
		//Se spawnea el arma en cuestión y se añade al socket que hay en el hueso donde debe ir el arma
		//Se añade el arma al array de armas y se comprueba si es la que se quiere tener equipada
		//En caso contrario se esconde
		Gun = GetWorld()->SpawnActor<AGun>(GunClassArray[i]);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		GunArray.Add(Gun);
		if (i != ActiveIndex)
		{
			Gun->SetActorHiddenInGame(true);
		}
	}
	//Finalmente se settea como arma equipada la indicada por el índice y se settea su ownea a nuestro
	//personaje
	Gun = GunArray[ActiveIndex];
	Gun->SetOwner(this);
}