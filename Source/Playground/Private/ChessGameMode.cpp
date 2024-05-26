// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameMode.h"

AChessGameMode::AChessGameMode()
{

}

void AChessGameMode::BeginPlay()
{
	Super::BeginPlay();


}

void AChessGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AChessGameMode::SetCurrentChessGrid(AGridSystem* ChessGrid)
{
	if (ChessGrid)
	{
		TiedChessGrid = ChessGrid;
		return true;
	}
	else
		return false;
}
