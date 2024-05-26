// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeActor.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASnakeActor::ASnakeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASnakeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

