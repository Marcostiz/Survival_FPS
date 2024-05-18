// Fill out your copyright notice in the Description page of Project Settings.


#include "Medpack.h"

// Sets default values
AMedpack::AMedpack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMedpack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMedpack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

