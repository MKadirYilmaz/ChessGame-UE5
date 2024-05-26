// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GridSystem.h"
#include "ChessGameMode.h"
#include "ChessManager.h"
#include "ChessPieces.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SplineComponent.h"
#include "Components/CapsuleComponent.h"


AChessPlayer::AChessPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	ChessCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Chess Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	CameraRotationPath = CreateDefaultSubobject<USplineComponent>(TEXT("Camera Rotation Path"));
	CameraFocusPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Focus Point"));

	SpringArm->SetupAttachment(RootComponent);
	ChessCamera->SetupAttachment(SpringArm);
	CameraRotationPath->SetupAttachment(RootComponent);
	CameraFocusPoint->SetupAttachment(RootComponent);

	SpringArm->TargetOffset = FVector(-150.f, 0.f, -400.f);
	SpringArm->SetRelativeRotation(FRotator(-58.25f, -178.5f, 0.f));
	SpringArm->TargetArmLength = 1000.f;

	for (int32 PointCount = 2; PointCount <= 8; PointCount++)
	{
		CameraRotationPath->AddSplinePoint(FVector(0, 0, 0), ESplineCoordinateSpace::Local);
	}
	
}

void AChessPlayer::OnConstruction(const FTransform& Transform)
{
	int32 lPointDegree = 0;
	FVector lPointLocation;
	lPointLocation = FVector(0, 0, CameraPathHeight);
	for (int32 Index = 0; Index < CameraRotationPath->GetNumberOfSplinePoints(); Index++)
	{
		FVector lRotatedVector = FRotator(0, lPointDegree, 0).RotateVector(GetActorForwardVector());
		lPointDegree += 45;

		CameraRotationPath->SetLocationAtSplinePoint(Index, lPointLocation + lRotatedVector * CameraPathRadius, ESplineCoordinateSpace::Local);
	}
	CameraRotationPath->SetClosedLoop(false);
}

void AChessPlayer::BeginPlay()
{
	Super::BeginPlay();
	TeamTurn = White;
	CurrentChessManager->FillForbiddenCoordinates(TeamTurn);
	CurrentGameMode = Cast<AChessGameMode>(UGameplayStatics::GetGameMode(this));
	if (CurrentGameMode)
	{
		CurrentGrid = CurrentGameMode->GetCurrentChessGrid();
	}
	CameraPathLength = CameraRotationPath->GetSplineLength();
	ChessCamera->SetWorldRotation((CameraFocusPoint->GetComponentLocation() - ChessCamera->GetComponentLocation()).Rotation());
}

void AChessPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bool lHasHit = UGameplayStatics::GetPlayerController(this, 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, ResultUnderCursor);
	if (lHasHit && CurrentGrid)
	{
		int32 lRow, lColumn;
		bool IsValidTile = CurrentGrid->FindTileFromLocation(lRow, lColumn, ResultUnderCursor.Location);
		//UE_LOG(LogTemp, Display, TEXT("Row: %d, Column: %d"), lRow, lColumn);
		CurrentGrid->SetSelectedTile(lRow, lColumn);
	}
	if (CanCameraRotate)
	{
		CurrentRotationSpeed = FMath::FInterpTo(CurrentRotationSpeed, MaxCameraRotationSpeed, DeltaTime, 2.5f);
		//UE_LOG(LogTemp, Display, TEXT("RotationSpeed: %f"), CurrentRotationSpeed);
		CameraPathDistance += CurrentRotationSpeed * DeltaTime;
		FTransform lPointTransform = CameraRotationPath->GetTransformAtDistanceAlongSpline(CameraPathDistance, ESplineCoordinateSpace::World);

		ChessCamera->SetWorldLocation(lPointTransform.GetLocation());
		ChessCamera->SetWorldRotation((CameraFocusPoint->GetComponentLocation() - ChessCamera->GetComponentLocation()).Rotation());

		if (FirstHalf)
		{
			if (CameraPathDistance >= CameraPathLength / 2)
			{
				CanCameraRotate = false;
				FirstHalf = false;
				CurrentRotationSpeed = 0;
			}
		}
		else
		{
			if (CameraPathDistance >= CameraPathLength)
			{
				CameraPathDistance = 0;
				CanCameraRotate = false;
				FirstHalf = true;
				CurrentRotationSpeed = 0;
			}
		}
		
	}
	/*
	if (CanCameraRotate)
	{
		
		SpringArm->AddRelativeRotation(FRotator(0, SpringArmYawSpeed * DeltaTime, 0));
		
		TotalYawChange += SpringArmYawSpeed * DeltaTime;
		if (TotalYawChange >= 180)
		{
			SpringArm->SetRelativeRotation(FRotator(-57.5f, StartSpringArmYaw + 180, 0));
			TotalYawChange = 0;
			CanCameraRotate = false;
		}
	}
	if (CanOffsetChange)
	{
		SpringArm->TargetOffset.X += TargetOffsetX * DeltaTime * OffsetChangeSpeed;
		TotalOffsetChange += TargetOffsetX * DeltaTime * OffsetChangeSpeed;
		if (FMath::Abs(TotalOffsetChange) >= 300)
		{
			SpringArm->TargetOffset.X = TargetX;
			TotalOffsetChange = 0;
			CanOffsetChange = false;
		}
	}
	*/
	
}

void AChessPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Select"), IE_Pressed, this, &AChessPlayer::SelectChessPiece);
	PlayerInputComponent->BindAction(TEXT("Right Click"), IE_Pressed, this, &AChessPlayer::MoveSelectedChessPiece);
}

void AChessPlayer::SelectChessPiece()
{
	bool lHasHit = UGameplayStatics::GetPlayerController(this, 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, ResultUnderCursor);
	if (lHasHit && CurrentGrid)
	{
		int32 lRow, lColumn;
		bool IsValidTile = CurrentGrid->FindTileFromLocation(lRow, lColumn, ResultUnderCursor.Location);
		
		if (CurrentChessManager && IsValidTile)
		{
			bool IsTileEmpty;
			AChessPieces* lChessPiece = CurrentChessManager->GetChessPieceFromTile(lRow, lColumn, IsTileEmpty);
			if (!IsTileEmpty && lChessPiece)
			{
				if (lChessPiece->GetPieceTeam() != TeamTurn)
				{
					UE_LOG(LogTemp, Error, TEXT("Wrong team selection. Select your own team pieces."));
					return;
				}
				int32 TeamIndex;
				switch (lChessPiece->GetPieceTeam())
				{
				case White:
					TeamIndex = 0;
					break;
				case Black:
					TeamIndex = 1;
					break;
				}
				
				SelectedChessPiece = lChessPiece;
				SelectedPieceCoordinate = FVector2D(lRow, lColumn);
				UE_LOG(LogTemp, Display, TEXT("PieceName: %s, TeamIndex: %d, CRow:%f, CColumn:%f"), *SelectedChessPiece->GetActorNameOrLabel(), 
					TeamIndex, SelectedPieceCoordinate.X, SelectedPieceCoordinate.Y);
				PieceMovableCoordinates = CurrentChessManager->GetPieceMovableCoordinates(SelectedChessPiece, lRow, lColumn);

				for (int32 i = 0; i < PieceMovableCoordinates.Num(); i++)
				{
					UE_LOG(LogTemp, Warning, TEXT("MoveRow: %d, MoveColumn: %d"), (int32)PieceMovableCoordinates[i].X, (int32)PieceMovableCoordinates[i].Y);
				}
				if (PieceMovableCoordinates.Num() == 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("There is nowhere to move"));
				}
			}
		}

	}
}

void AChessPlayer::MoveSelectedChessPiece()
{
	bool lHasHit = UGameplayStatics::GetPlayerController(this, 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, ResultUnderCursor);
	if (lHasHit && CurrentGrid)
	{
		int32 lRow, lColumn;
		bool IsValidTile = CurrentGrid->FindTileFromLocation(lRow, lColumn, ResultUnderCursor.Location);
		if (CurrentChessManager && IsValidTile && SelectedChessPiece)
		{
			for (int32 i = 0; i < PieceMovableCoordinates.Num(); i++)
			{
				if (PieceMovableCoordinates[i].X == lRow && PieceMovableCoordinates[i].Y == lColumn) // If new row and column request is available to move by selected piece
				{
					bool lPieceMoved = CurrentChessManager->UpdatePieceLocation(SelectedChessPiece, SelectedPieceCoordinate.X, SelectedPieceCoordinate.Y, lRow, lColumn);
					if (!lPieceMoved) // If piece didn't move then return before turn switched to other team. Player needs to retrigger this function.
						return;
					UE_LOG(LogTemp, Display, TEXT("Update Piece Location function executed"));
					if (SelectedChessPiece->GetPieceType() == Pawn && SelectedChessPiece->GetPawnFirstMovement())
					{
						SelectedChessPiece->SetPawnFirstMovement(false);
					}
					SelectedChessPiece = nullptr;
					if (TeamTurn == White)
					{
						TeamTurn = Black;
					}
					else
					{
						TeamTurn = White;
					}
					CurrentChessManager->ExecuteNextTurn();
					CurrentChessManager->FillForbiddenCoordinates(TeamTurn);
					RotateCameraToOtherTeam();
					return;
				}
			}
			UE_LOG(LogTemp, Error, TEXT("This piece can't move to this location"));
		}
	}
}

void AChessPlayer::RotateCameraToOtherTeam()
{
	StartSpringArmYaw = SpringArm->GetRelativeRotation().Yaw;
	TargetOffsetX *= TargetOffsetXParam;
	TargetX = SpringArm->TargetOffset.X * TargetOffsetXParam;
	CanCameraRotate = true;
	CanOffsetChange = true;

}
