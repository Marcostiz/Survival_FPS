// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

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

	Health = MaxHealth;
	ActiveIndex = 0;
	Score = 0;
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	//UE_LOG(LogTemp, Warning, TEXT("ClassArraySize %i"), GunClassArray.Num());

	/*Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);*/
	/*if (isEnemy)
	{
		Gun = GetWorld()->SpawnActor<AGun>(GunClass);
		GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		Gun->SetOwner(this);
	}
	else
	{
		SpawnWeapons();
	}*/
	SpawnWeapons();
	
}

bool AMyPlayer::IsDead() const
{
	return Health <= 0;
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < GunArray.Num(); i++)
	{
		if (i != ActiveIndex)
		{
			GunArray[i]->SetHidden(true);
			GunArray[i]->SetActorHiddenInGame(true);
		}
	}
}

float AMyPlayer::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	}

	return DamageToApply;
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyPlayer::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMyPlayer::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AMyPlayer::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AMyPlayer::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AMyPlayer::Shoot);
	PlayerInputComponent->BindAction(TEXT("SwitchWeapon"), EInputEvent::IE_Pressed, this, &AMyPlayer::SwitchWeapons);
	//PlayerInputComponent->BindAction(TEXT("SwitchWeaponUp"), EInputEvent::IE_Pressed, this, &AMyPlayer::SwitchWeaponUp);
	//PlayerInputComponent->BindAction(TEXT("SwitchWeaponDown"), EInputEvent::IE_Pressed, this, &AMyPlayer::SwitchWeaponDown);
}

void AMyPlayer::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AMyPlayer::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AMyPlayer::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AMyPlayer::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AMyPlayer::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AMyPlayer::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AMyPlayer::Shoot()
{
	Gun->PullTrigger();
}

void AMyPlayer::SetScore(int score)
{
	this->Score = score;
}

int AMyPlayer::GetScore()
{
	return Score;
}

void AMyPlayer::SetAddToScoreWhenKilled(int score)
{
	this->AddToScoreWhenKilled = score;
}

int AMyPlayer::GetAddToScoreWhenKilled()
{
	return AddToScoreWhenKilled;
}

void AMyPlayer::SwitchWeapons()
{
	if (ActiveIndex == 2)
	{
		ActiveIndex = 0;
	}
	else
	{
		ActiveIndex++;
	}
	if (GunArray.IsValidIndex(ActiveIndex))
	{
		Gun->SetActorHiddenInGame(true);
		Gun = GunArray[ActiveIndex];
		Gun->SetActorHiddenInGame(false);
		Gun->SetOwner(this);
	}	
}

void AMyPlayer::SpawnWeapons()
{
	for (int32 i = 0; i < GunClassArray.Num(); i++)
	{
		Gun = GetWorld()->SpawnActor<AGun>(GunClassArray[i]);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		GunArray.Add(Gun);
		if (i != ActiveIndex)
		{
			Gun->SetActorHiddenInGame(true);
		}
	}
	Gun = GunArray[ActiveIndex];
	Gun->SetOwner(this);
}