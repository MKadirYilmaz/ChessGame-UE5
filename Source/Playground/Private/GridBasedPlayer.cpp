// Fill out your copyright notice in the Description page of Project Settings.


#include "GridBasedPlayer.h"

// Sets default values
AGridBasedPlayer::AGridBasedPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridBasedPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridBasedPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGridBasedPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

