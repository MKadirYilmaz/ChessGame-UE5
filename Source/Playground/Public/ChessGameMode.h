// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLAYGROUND_API AChessGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AChessGameMode();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	bool SetCurrentChessGrid(class AGridSystem* ChessGrid);

	AGridSystem* GetCurrentChessGrid() { return TiedChessGrid; }

private:
	AGridSystem* TiedChessGrid;
	
};
