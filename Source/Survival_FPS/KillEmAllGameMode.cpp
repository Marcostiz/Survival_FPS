// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	//Se comprueba si nuestro peón muerto es el player
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		//En caso afirmativo se llama a la función que acaba la partida
		PlayerController->GameHasEnded(nullptr, false);
	}
	else
	{
		//En caso contrario significa que ha muerto un enemigo, por lo que se deben añadir puntos
		// al score del player. Para ello se busca el player controller y se comprueba que se haya 
		//encontrado
		PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
		if (PlayerController != nullptr)
		{
			//En caso de haberse encontrado se llama a la clase MyPlayer que debe contener 
			// y se obtienen también una variable de esa clase con el enemigo que se ha muerto
			//posteiormente se settea el score del player como la suma de su anterior con los puntos
			//que da el enemigo al morir
			AMyPlayer* Player = Cast<AMyPlayer>(PlayerController->GetPawn());
			AMyPlayer* enemyKilled = Cast<AMyPlayer>(PawnKilled);
			Player->SetScore(Player->GetScore() + enemyKilled->GetAddToScoreWhenKilled());

			//UE_LOG(LogTemp, Warning, TEXT("Player Score: %i"), Player->GetScore());
		}
		
	}
}

