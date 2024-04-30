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

	//Se crean y configuran los elementos básicos del actor
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

//Función que aplica el disparo del arma
void AGun::PullTrigger()
{
	//Primero se comprueba si se dispone de munición
	if (CurrentAMMO > 0)
	{
		//En caso afirmativo se resta 1 a la munición actual y se emiten las partículas de disparo
		CurrentAMMO--;
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

		//Se comprueba que el arma esté equipada por un personaje que se pueda mover
		APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if (OwnerPawn == nullptr) return;
		AController* OwnerController = OwnerPawn->GetController();
		if (OwnerController == nullptr) return;

		//Vectores para la localización y rotación
		FVector Location;
		FRotator Rotation;

		//Se settean esos vectores a los que coinciden con los valores de visión del personaje
		//que está disparando
		OwnerController->GetPlayerViewPoint(Location, Rotation);

		//Se calcula hasta dónde debe llegar el rayo a trazar
		FVector End = Location + Rotation.Vector() * MaxRange;

		//Para debuggear, dibuja la cámara del personaje que dispara para poder ver dónde estaba mirando
		//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);
		
		//Se crean el parámetro Hit, que almacenará el choque del rayo trazado y Params, que almacena
		//la configuración para trazar el rayo
		FHitResult Hit;
		FCollisionQueryParams Params;

		//Se configura que el rayo ignore tanto el arma como al propietario para que no se disparen
		//ellos mismos
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());

		//Se traza el rayo indicando dónde guardar con lo que choque, desde dónde empieza, dónde acaba y el canal a usar
		//que se ha comprobado en los archivos de configuración al crearlo. Y finalmente se añaden los parámetros
		//de configuración y se comprueba si ha hitteado
		bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel2, Params);
		if (bSuccess)
		{
			//En caso afirmativo se calcula el vector de la dirección en la que se ha hitteado
			// y se emiten las partículas de impacto en la localización del hit
			FVector ShotDirection = -Rotation.Vector();

			//Esta línea dibuja en la escena el lugar de impacto
			//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());

			//Después se obtiene el actor al que le ha impactado
			AActor* HitActor = Hit.GetActor();

			//Se comprueba que realmente haya impactado con un actor y no con una pared, por ejemplo
			if (HitActor != nullptr)
			{
				//En caso de que realmente impacte con un actor se crea un evento de daño y se llama
				//A la función TakeDamage del actor para aplicárselo
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
	//Settea la munición del arma a su máximo al inicio
	CurrentAMMO = MaxAMMO;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

