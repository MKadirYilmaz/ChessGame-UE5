// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridBasedPlayer.h"
#include "ChessPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PLAYGROUND_API AChessPlayer : public AGridBasedPlayer
{
	GENERATED_BODY()
public:
	AChessPlayer();

	void OnConstruction(const FTransform& Transform) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		AChessManager* GetCurrentChessManager() const { return CurrentChessManager; }

private:
	void SelectChessPiece();
	void MoveSelectedChessPiece();

	void RotateCameraToOtherTeam();

	FHitResult ResultUnderCursor;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* ChessCamera;
	UPROPERTY(EditAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		class AGridSystem* CurrentGrid;

	class AChessGameMode* CurrentGameMode;

	class AChessPieces* SelectedChessPiece;

	FHitResult PieceFinderResult;
	UPROPERTY(EditAnywhere)
		class AChessManager* CurrentChessManager;
	UPROPERTY(EditAnywhere)
		class USplineComponent* CameraRotationPath;
	UPROPERTY(EditAnywhere)
		USceneComponent* CameraFocusPoint;

	UPROPERTY(EditAnywhere)
		float CameraPathRadius = 900.f;
	UPROPERTY(EditAnywhere)
		float CameraPathHeight = 500.f;
	float CameraPathLength;
	UPROPERTY(EditAnywhere)
		float MaxCameraRotationSpeed = 300.f;
	float CurrentRotationSpeed = 0;
	float CameraPathDistance;
	bool FirstHalf = true;

	FVector2D SelectedPieceCoordinate;
	TArray<FVector2D> PieceMovableCoordinates;

	enum ETeamColor TeamTurn;
	int32 TargetOffsetXParam = -1;

	
	float SpringArmYawSpeed = 140.f;
	float OffsetChangeSpeed = 1.5f;
	float TargetOffsetX = -200.f;

	float TargetX;

	float StartSpringArmYaw;
	float TotalYawChange;
	float TotalOffsetChange;
	bool CanCameraRotate;
	bool CanOffsetChange;
};
