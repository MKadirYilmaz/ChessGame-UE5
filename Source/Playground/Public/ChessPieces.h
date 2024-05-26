// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessPieces.generated.h"


enum EChessPieceType
{
	Pawn	UMETA(DisplayName = "Pawn"),
	Rook	UMETA(DisplayName = "Rook"),
	Knight	UMETA(DisplayName = "Knight"),
	Bishop	UMETA(DisplayName = "Bishop"),
	Queen	UMETA(DisplayName = "Queen"),
	King	UMETA(DisplayName = "King")
};


enum ETeamColor
{
	White	UMETA(DisplayName = "White"),
	Black	UMETA(DisplayName = "Black")
};

enum EDangerType
{
	BlockEatOrEscape,
	EatOrEscape,
	JustEscape,
	Safe
};

UCLASS()
class PLAYGROUND_API AChessPieces : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AChessPieces();

	void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPieceType(EChessPieceType NewPieceType) { PieceType = NewPieceType; }
	EChessPieceType GetPieceType() { return PieceType; }

	void SetPieceTeam(ETeamColor NewTeamColor) { TeamColor = NewTeamColor; }
	ETeamColor GetPieceTeam() { return TeamColor; }

	void SetPieceMesh(UStaticMesh* PieceMesh);
	void SetPieceOverlapArea(UStaticMesh* OverlappingMesh);

	bool GetPawnFirstMovement() { return PawnFirstMovement; }
	void SetPawnFirstMovement(bool NewBool) { PawnFirstMovement = NewBool; }

	void SetSplineForKnightMovement(const FVector& Start, const FVector& End);
	void SetSplineForDefaultMovements(const FVector& Start, const FVector& End); // For rooks, bishops, queens, pawns, kings
	
	void SetHasBeaten(bool HasItBeaten) { HasBeaten = HasItBeaten; }
	bool GetHasBeaten() { return HasBeaten; }

	EDangerType GetPieceDangerType() { return PieceDangerType; }
	void SetPieceDangerType(EDangerType NewDangerType) { PieceDangerType = NewDangerType; }
private:

	EChessPieceType PieceType;

	ETeamColor TeamColor;

	EDangerType PieceDangerType;

	bool PawnFirstMovement = true;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DestructionArea;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ChessPieceMesh;
	UPROPERTY(EditAnywhere)
		class USplineComponent* PieceMovementSpline;

	UPROPERTY(EditAnywhere)
		class AChessManager* TiedChessManager;

	int32 SplinePointCount;
	bool PieceCanMove;


	int32 MovementAnimSpeed = 200.f;
	float DistanceMoved;
	bool HasBeaten = false;
};
