// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Se crean y configuran los elementos b�sicos del actor
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

//Funci�n que aplica el disparo del arma
void AGun::PullTrigger()
{
	//Primero se comprueba si se dispone de munici�n
	if (CurrentAMMO > 0)
	{
		//En caso afirmativo se resta 1 a la munici�n actual y se emiten las part�culas de disparo
		CurrentAMMO--;
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

		//Se comprueba que el arma est� equipada por un personaje que se pueda mover
		APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if (OwnerPawn == nullptr) return;
		AController* OwnerController = OwnerPawn->GetController();
		if (OwnerController == nullptr) return;

		//Vectores para la localizaci�n y rotaci�n
		FVector Location;
		FRotator Rotation;

		//Se settean esos vectores a los que coinciden con los valores de visi�n del personaje
		//que est� disparando
		OwnerController->GetPlayerViewPoint(Location, Rotation);

		//Se calcula hasta d�nde debe llegar el rayo a trazar
		FVector End = Location + Rotation.Vector() * MaxRange;

		//Para debuggear, dibuja la c�mara del personaje que dispara para poder ver d�nde estaba mirando
		//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);
		
		//Se crean el par�metro Hit, que almacenar� el choque del rayo trazado y Params, que almacena
		//la configuraci�n para trazar el rayo
		FHitResult Hit;
		FCollisionQueryParams Params;

		//Se configura que el rayo ignore tanto el arma como al propietario para que no se disparen
		//ellos mismos
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());

		//Se traza el rayo indicando d�nde guardar con lo que choque, desde d�nde empieza, d�nde acaba y el canal a usar
		//que se ha comprobado en los archivos de configuraci�n al crearlo. Y finalmente se a�aden los par�metros
		//de configuraci�n y se comprueba si ha hitteado
		bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel2, Params);
		if (bSuccess)
		{
			//En caso afirmativo se calcula el vector de la direcci�n en la que se ha hitteado
			// y se emiten las part�culas de impacto en la localizaci�n del hit
			FVector ShotDirection = -Rotation.Vector();

			//Esta l�nea dibuja en la escena el lugar de impacto
			//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());

			//Despu�s se obtiene el actor al que le ha impactado
			AActor* HitActor = Hit.GetActor();

			//Se comprueba que realmente haya impactado con un actor y no con una pared, por ejemplo
			if (HitActor != nullptr)
			{
				//En caso de que realmente impacte con un actor se crea un evento de da�o y se llama
				//A la funci�n TakeDamage del actor para aplic�rselo
				FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
				HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}
		}
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("NO AMMO"));
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	//Settea la munici�n del arma a su m�ximo al inicio
	CurrentAMMO = MaxAMMO;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

