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

	//Se settean los valores iniciales de las variables y se esconde el hueso del arma que ven�a en el 
	//modelo
	Health = MaxHealth;
	ActiveIndex = 0;
	Score = 0;
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	
	//Finalmente se spawnean las armas en el personaje
	SpawnWeapons();
	
}

//Funci�n que comprueba si el personaje est� muerto
bool AMyPlayer::IsDead() const
{
	return Health <= 0;
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Funci�n que aplica el da�o al jugador, hace override a la funci�n ya integrada en la clase de la que 
//hereda en MyPlayer, Character
float AMyPlayer::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//Primero obtenemos el valor del da�o a recibir
	//luego se transforma con la funci�n min para que nunca llegue a pasarse de la vida que le puede
	//restar al personaje
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	//UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	//Comprobaci�n de si se ha matado al personaje que est� recibiendo da�o
	if (IsDead())
	{
		//En caso afirmativo se accede al modo de juego y se llama a la funci�n que gestiona la
		//muerte de un pe�n en el juego
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		//Se hace que no se pueda mover m�s ni colisionar con �l
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	}

	//Se devuelve el da�o que se ha realizado, ya que seguimos heredando de la funci�n TakeDamage que
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

//Mueve la c�mara del personaje rotando hacia arriba o abajo dependiendo del valor del eje, que se obtiene del
//input del player
void AMyPlayer::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

//Adaptaci�n de la anterior funci�n para el uso de mando
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

//Mueve la c�mara del personaje rotando hacia derecha o izquierda dependiendo del valor del eje, que 
// se obtiene del input del player
void AMyPlayer::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

//Adaptaci�n de la anterior funci�n para el uso de mando
void AMyPlayer::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

//Llamada a la funci�n de disparar del arma que llevemos equipada
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

//Setter y getter de la puntuaci�n que da el personaje al morir
void AMyPlayer::SetAddToScoreWhenKilled(int score)
{
	this->AddToScoreWhenKilled = score;
}

int AMyPlayer::GetAddToScoreWhenKilled()
{
	return AddToScoreWhenKilled;
}

//Funci�n que alterna entre las armas del personaje
void AMyPlayer::SwitchWeapons()
{
	//Se realiza esta comprobaci�n para no salir del �ndice, del que sabemos que su m�ximo ser� 2,
	//ya que tenemos 3 armas y se modifica el valor del �ndice
	if (ActiveIndex == 2)
	{
		ActiveIndex = 0;
	}
	else
	{
		ActiveIndex++;
	}

	//Se comprueba que el �ndice aportado al array est� en los l�mites comprendidos
	if (GunArray.IsValidIndex(ActiveIndex))
	{
		//Se esconde el arma actual, se cambia el arma equipada por la indicada del �ndice,
		//se revela el arma equipada y se settea el owner de nuevo a nuestro personaje
		//por asegurarnos de que sea el correcto
		Gun->SetActorHiddenInGame(true);
		Gun = GunArray[ActiveIndex];
		Gun->SetActorHiddenInGame(false);
		Gun->SetOwner(this);
	}	
}

//Funci�n que equipa el arma y a�ade todas a nuestro "inventario"
void AMyPlayer::SpawnWeapons()
{
	//Se itera en el array de blueprints de armas que heredan de nuestra clase Gun
	for (int32 i = 0; i < GunClassArray.Num(); i++)
	{
		//Se spawnea el arma en cuesti�n y se a�ade al socket que hay en el hueso donde debe ir el arma
		//Se a�ade el arma al array de armas y se comprueba si es la que se quiere tener equipada
		//En caso contrario se esconde
		Gun = GetWorld()->SpawnActor<AGun>(GunClassArray[i]);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		GunArray.Add(Gun);
		if (i != ActiveIndex)
		{
			Gun->SetActorHiddenInGame(true);
		}
	}
	//Finalmente se settea como arma equipada la indicada por el �ndice y se settea su ownea a nuestro
	//personaje
	Gun = GunArray[ActiveIndex];
	Gun->SetOwner(this);
}