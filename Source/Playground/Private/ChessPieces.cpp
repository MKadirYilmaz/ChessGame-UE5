// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPieces.h"
#include "Components/SplineComponent.h"

// Sets default values
AChessPieces::AChessPieces()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChessPieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chess Piece Mesh"));
	ChessPieceMesh->SetupAttachment(RootComponent);

	DestructionArea = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Destruction Area"));
	DestructionArea->SetupAttachment(ChessPieceMesh);
	DestructionArea->SetCollisionProfileName("OverlapAll");
	DestructionArea->SetVisibility(false);

	PieceMovementSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Piece Movement Spline"));
	PieceMovementSpline->SetupAttachment(RootComponent);

	if (PieceMovementSpline->GetNumberOfSplinePoints() - 1 >= 0)
	{
		PieceMovementSpline->AddSplineLocalPoint(PieceMovementSpline->GetLocationAtSplinePoint(PieceMovementSpline->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::Local)
			+ FVector(-10.f, 0.f, 0.f));
		PieceMovementSpline->AddSplineLocalPoint(PieceMovementSpline->GetLocationAtSplinePoint(PieceMovementSpline->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::Local)
			+ FVector(-10.f, 0.f, 0.f));
		PieceMovementSpline->AddSplineLocalPoint(PieceMovementSpline->GetLocationAtSplinePoint(PieceMovementSpline->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::Local)
			+ FVector(-10.f, 0.f, 0.f));
	}
}

void AChessPieces::OnConstruction(const FTransform& Transform)
{
}

// Called when the game starts or when spawned
void AChessPieces::BeginPlay()
{
	Super::BeginPlay();
	if(PieceType != EChessPieceType::Pawn)
		ChessPieceMesh->SetWorldScale3D(FVector(1.45f, 1.45f, 1.45f));
	else
		ChessPieceMesh->SetWorldScale3D(FVector(1.3f, 1.3f, 1.3f));

	SplinePointCount = PieceMovementSpline->GetNumberOfSplinePoints(); // It should be 5
	DestructionArea->OnComponentBeginOverlap.AddDynamic(this, &AChessPieces::OverlapBegin);

	// Set the piece danger type
	switch (PieceType)
	{
	case Pawn:
		PieceDangerType = EatOrEscape;
		break;
	case Rook:
		PieceDangerType = BlockEatOrEscape;
		break;
	case Knight:
		PieceDangerType = EatOrEscape;
		break;
	case Bishop:
		PieceDangerType = BlockEatOrEscape;
		break;
	case Queen:
		PieceDangerType = BlockEatOrEscape;
		break;
	case King:
		PieceDangerType = JustEscape;
		break;
	}

}

void AChessPieces::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Piece colliding with another piece"));
	AChessPieces* lOtherPiece = Cast<AChessPieces>(OtherActor);
	if (lOtherPiece && HasBeaten)
	{
		UE_LOG(LogTemp, Warning, TEXT("Piece colliding with another piece and it will be destroyed"));
		Destroy();
	}
}

// Called every frame
void AChessPieces::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PieceCanMove)
	{
		DistanceMoved += MovementAnimSpeed * DeltaTime;
		FTransform lPieceTransform = PieceMovementSpline->GetTransformAtDistanceAlongSpline(DistanceMoved, ESplineCoordinateSpace::Local, false);
		SetActorRelativeTransform(FTransform(GetActorRotation(), lPieceTransform.GetLocation(), GetActorScale3D()));
		if (DistanceMoved >= PieceMovementSpline->GetSplineLength() - 1.f)
		{
			DistanceMoved = 0;
			PieceCanMove = false;
		}
	}

}

void AChessPieces::SetPieceMesh(UStaticMesh* PieceMesh)
{
	ChessPieceMesh->SetStaticMesh(PieceMesh);
}

void AChessPieces::SetPieceOverlapArea(UStaticMesh* OverlappingMesh)
{
	DestructionArea->SetStaticMesh(OverlappingMesh);
	DestructionArea->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
}

void AChessPieces::SetSplineForKnightMovement(const FVector& Start, const FVector& End)
{
	PieceMovementSpline->SetWorldLocationAtSplinePoint(0, Start);                                                       
	PieceMovementSpline->SetWorldLocationAtSplinePoint(SplinePointCount - 1, End); // Last point

	FVector lStartToFinish = End - Start;
	FVector lEqualDirection = lStartToFinish / 4;

	FVector lPointLocation = Start;
	for (int32 i = 1; i < 4; i++)
	{
		lPointLocation += lEqualDirection;
		PieceMovementSpline->SetWorldLocationAtSplinePoint(i, lPointLocation);
	}

	PieceCanMove = true;
}

void AChessPieces::SetSplineForDefaultMovements(const FVector& Start, const FVector& End)
{
	PieceMovementSpline->SetWorldLocationAtSplinePoint(0, Start);
	PieceMovementSpline->SetWorldLocationAtSplinePoint(SplinePointCount - 1, End); // Last point

	FVector lStartToFinish = End - Start;
	FVector lEqualDirection = lStartToFinish / 4;
	FVector lPointLocation = Start;
	lPointLocation.Z += 30.f;

	MovementAnimSpeed = FVector::Distance(Start, End);

	lPointLocation += lEqualDirection;
	PieceMovementSpline->SetWorldLocationAtSplinePoint(1, lPointLocation);
	lPointLocation.Z += 10.f;
	lPointLocation += lEqualDirection;
	PieceMovementSpline->SetWorldLocationAtSplinePoint(2, lPointLocation);
	lPointLocation.Z -= 10.f;
	lPointLocation += lEqualDirection;
	PieceMovementSpline->SetWorldLocationAtSplinePoint(3, lPointLocation);

	PieceCanMove = true;
	
}

