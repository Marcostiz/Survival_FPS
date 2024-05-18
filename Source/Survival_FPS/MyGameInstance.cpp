// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitialiaer) : Super(FObjectInitializer())
{
	
	static ConstructorHelpers::FClassFinder<UUserWidget> DeathMenu(TEXT("/Game/Menus/WB_DeathScreen.WB_DeathScreen"));
	if (!ensure(DeathMenu.Class != nullptr)) return;

	DeathMenuClass = DeathMenu.Class;
}

void UMyGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Hemos fundado la clase %s"), *DeathMenuClass->GetName())
}

void UMyGameInstance::ShowDeathViewport() {
	//cogemos la instancia del juego
	UGameInstance gameInstance = UGameInstance();

	//Creamos y añadimos el widget al viewport
	UUserWidget* DeathScreen = CreateWidget<UUserWidget>(this, DeathMenuClass);
	DeathScreen->AddToViewport();

	//Cogemos la refencia del Player Controller
	APlayerController* PlayerController = gameInstance.GetFirstLocalPlayerController();

	//Setteamos los parametros del input a los de SetInputUIMode
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(DeathScreen->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	//Set input mode
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}