// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	//UE_LOG(LogTemp, Warning, TEXT("A pawn was killed!"));

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->GameHasEnded(nullptr, false);
	}
	else
	{
		//AMyPlayer* player = Cast<AMyPlayer>(PawnKilled->GetController());
		//AMyPlayer* Player = Cast<AMyPlayer>(PlayerController->GetPawn());
		PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
		if (PlayerController != nullptr)
		{
			AMyPlayer* Player = Cast<AMyPlayer>(PlayerController->GetPawn());
			AMyPlayer* enemyKilled = Cast<AMyPlayer>(PawnKilled);
			Player->SetScore(Player->GetScore() + enemyKilled->GetAddToScoreWhenKilled());

			UE_LOG(LogTemp, Warning, TEXT("Player Score: %i"), Player->GetScore());
		}
		
	}
}