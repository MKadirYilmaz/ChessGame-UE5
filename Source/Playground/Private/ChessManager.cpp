// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessManager.h"
#include "ChessPieces.h"
#include "GridSystem.h"

// Sets default values
AChessManager::AChessManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChessManager::BeginPlay()
{
	Super::BeginPlay();

	GridRow.Init(GridColumn, 8);

	SetTheChessBoard();
	
	int32 Number = 1;
	for (int32 i = 0; i < GridRow.Num(); i++)
	{
		for (int32 j = 0; j < GridRow[i].GridColumn.Num(); j++)
		{
			if (GridRow[i].GridColumn[j])
			{
				UE_LOG(LogTemp, Display, TEXT("%d. Row: %d, Column: %d, Name: %s"), Number, i, j, *GridRow[i].GridColumn[j]->GetActorNameOrLabel());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("%d. Row: %d, Column: %d, Nullptr"), i, j);
			}
			Number++;
		}
	}

	if (RegisteredPieces.Num() != 32)
	{
		UE_LOG(LogTemp, Error, TEXT("There is more or less than 32 chess pieces. Check the all chess pieces in the map"));
	}
}

// Called every frame
void AChessManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChessManager::AlignBoardForStartPosition()
{
	int32 BlackPawnIndex = 0;
	int32 WhitePawnIndex = 0;
	
	int32 BlackRookIndex = 0;
	int32 WhiteRookIndex = 0;

	int32 WhiteKnightIndex = 1;
	int32 BlackKnightIndex = 1;

	int32 WhiteBishopIndex = 2;
	int32 BlackBishopIndex = 2;

	FVector2D lPawnLocation(0, 0);
	FVector2D lRookLocation(0, 0);
	FVector2D lKnightLocation(0, 0);
	FVector2D lBishopLocation(0, 0);
	FVector2D lQueenLocation(0, 0);
	FVector2D lKingLocation(0, 0);

	PieceInfo lPieceInfo;
	for (int32 i = 0; i < RegisteredPieces.Num(); i++)
	{
		switch (RegisteredPieces[i]->GetPieceType())
		{
		 
		case EChessPieceType::Pawn:
			switch (RegisteredPieces[i]->GetPieceTeam())
			{
			case ETeamColor::White:
				
				ChessGrid->FindLocationFromTile(1, WhitePawnIndex, lPawnLocation, true);
				RegisteredPieces[i]->SetActorLocation(FVector(lPawnLocation.X, lPawnLocation.Y, ChessGrid->GetActorLocation().Z));

				GridRow[1].GridColumn[WhitePawnIndex] = RegisteredPieces[i];
				
				lPieceInfo.sChessPiece = RegisteredPieces[i];
				lPieceInfo.sChessCoordinate = FVector2D(1, WhitePawnIndex);
				RegisteredWhitePieces.Add(lPieceInfo);

				WhitePawnIndex++;
				break;
			case ETeamColor::Black:
				
				ChessGrid->FindLocationFromTile(6, BlackPawnIndex, lPawnLocation, true);
				RegisteredPieces[i]->SetActorLocation(FVector(lPawnLocation.X, lPawnLocation.Y, ChessGrid->GetActorLocation().Z));

				GridRow[6].GridColumn[BlackPawnIndex] = RegisteredPieces[i];

				lPieceInfo.sChessPiece = RegisteredPieces[i];
				lPieceInfo.sChessCoordinate = FVector2D(6, BlackPawnIndex);
				RegisteredBlackPieces.Add(lPieceInfo);

				BlackPawnIndex++;
				break;
			}
			break;
			
		case EChessPieceType::Rook:
			switch (RegisteredPieces[i]->GetPieceTeam())
			{
			case ETeamColor::White:
				ChessGrid->FindLocationFromTile(0, WhiteRookIndex, lRookLocation, true);
				RegisteredPieces[i]->SetActorLocation(FVector(lRookLocation.X, lRookLocation.Y, ChessGrid->GetActorLocation().Z));

				GridRow[0].GridColumn[WhiteRookIndex] = RegisteredPieces[i];

				lPieceInfo.sChessPiece = RegisteredPieces[i];
				lPieceInfo.sChessCoordinate = FVector2D(0, WhiteRookIndex);
				RegisteredWhitePieces.Add(lPieceInfo);

				WhiteRookIndex += 7;
				break;
			case ETeamColor::Black:
				ChessGrid->FindLocationFromTile(7, BlackRookIndex, lRookLocation, true);
				RegisteredPieces[i]->SetActorLocation(FVector(lRookLocation.X, lRookLocation.Y, ChessGrid->GetActorLocation().Z));

				GridRow[7].GridColumn[BlackRookIndex] = RegisteredPieces[i];

				lPieceInfo.sChessPiece = RegisteredPieces[i];
				lPieceInfo.sChessCoordinate = FVector2D(7, BlackRookIndex);
				RegisteredBlackPieces.Add(lPieceInfo);

				BlackRookIndex += 7;
				break;
			}
			break;
		case EChessPieceType::Knight:
			switch (RegisteredPieces[i]->GetPieceTeam())
			{
			case ETeamColor::White:
				ChessGrid->FindLocationFromTile(0, WhiteKnightIndex, lKnightLocation, true);
				RegisteredPieces[i]->SetActorLocation(FVector(lKnightLocation.X, lKnightLocation.Y, ChessGrid->GetActorLocation().Z));

				GridRow[0].GridColumn[WhiteKnightIndex] = RegisteredPieces[i];

				lPieceInfo.sChessPiece = RegisteredPieces[i];
				lPieceInfo.sChessCoordinate = FVector2D(0, WhiteKnightIndex);
				RegisteredWhitePieces.Add(lPieceInfo);

				WhiteKnightIndex += 5;
				break;
			case ETeamColor::Black:
				ChessGrid->FindLocationFromTile(7, BlackKnightIndex, lKnightLocation, true);
				RegisteredPieces[i]->SetActorLocation(FVector(lKnightLocation.X, lKnightLocation.Y, ChessGrid->GetActorLocation().Z));

				GridRow[7].GridColumn[BlackKnightIndex] = RegisteredPieces[i];

				lPieceInfo.sChessPiece = RegisteredPieces[i];
				lPieceInfo.sChessCoordinate = FVector2D(7, BlackKnightIndex);
				RegisteredBlackPieces.Add(lPieceInfo);

				BlackKnightIndex += 5;
				break;
			}
			break;
		case EChessPieceType::Bishop:
			switch (RegisteredPieces[i]->GetPieceTeam())
			{
			case ETeamColor::White:
				ChessGrid->FindLocationFromTile(0, WhiteBishopIndex, lBishopLocation, true);
				RegisteredPieces[i]->SetActorLocation(FVector(lBishopLocation.X, lBishopLocation.Y, ChessGrid->GetActorLocation().Z));

				GridRow[0].GridColumn[WhiteBishopIndex] = RegisteredPieces[i];

				lPieceInfo.sChessPiece = RegisteredPieces[i];
				lPieceInfo.sChessCoordinate = FVector2D(0, WhiteBishopIndex);
				RegisteredWhitePieces.Add(lPieceInfo);

				WhiteBishopIndex += 3;
				break;
			case ETeamColor::Black:
				ChessGrid->FindLocationFromTile(7, BlackBishopIndex, lBishopLocation, true);
				RegisteredPieces[i]->SetActorLocation(FVector(lBishopLocation.X, lBishopLocation.Y, ChessGrid->GetActorLocation().Z));

				GridRow[7].GridColumn[BlackBishopIndex] = RegisteredPieces[i];

				lPieceInfo.sChessPiece = RegisteredPieces[i];
				lPieceInfo.sChessCoordinate = FVector2D(7, BlackBishopIndex);
				RegisteredBlackPieces.Add(lPieceInfo);

				BlackBishopIndex += 3;
				break;
			}
			break;
		case EChessPieceType::Queen:
			switch (RegisteredPieces[i]->GetPieceTeam())
			{
			case ETeamColor::White:
				ChessGrid->FindLocationFromTile(0, 3, lQueenLocation, true);
				RegisteredPieces[i]->SetActorLocation(FVector(lQueenLocation.X, lQueenLocation.Y, ChessGrid->GetActorLocation().Z));
				GridRow[0].GridColumn[3] = RegisteredPieces[i];

				lPieceInfo.sChessPiece = RegisteredPieces[i];
				lPieceInfo.sChessCoordinate = FVector2D(0, 3);
				RegisteredWhitePieces.Add(lPieceInfo);
				break;
			case ETeamColor::Black:
				ChessGrid->FindLocationFromTile(7, 3, lQueenLocation, true);
				RegisteredPieces[i]->SetActorLocation(FVector(lQueenLocation.X, lQueenLocation.Y, ChessGrid->GetActorLocation().Z));
				GridRow[7].GridColumn[3] = RegisteredPieces[i];

				lPieceInfo.sChessPiece = RegisteredPieces[i];
				lPieceInfo.sChessCoordinate = FVector2D(7, 3);
				RegisteredBlackPieces.Add(lPieceInfo);
				break;
			}
			break;
		case EChessPieceType::King:
			switch (RegisteredPieces[i]->GetPieceTeam())
			{
			case ETeamColor::White:
				ChessGrid->FindLocationFromTile(0, 4, lKingLocation, true);
				RegisteredPieces[i]->SetActorLocation(FVector(lKingLocation.X, lKingLocation.Y, ChessGrid->GetActorLocation().Z));
				GridRow[0].GridColumn[4] = RegisteredPieces[i];

				lPieceInfo.sChessPiece = RegisteredPieces[i];
				lPieceInfo.sChessCoordinate = FVector2D(0, 4);
				RegisteredWhitePieces.Add(lPieceInfo);
				WhiteKingCoordinate = FVector2D(0, 4);
				break;
			case ETeamColor::Black:
				ChessGrid->FindLocationFromTile(7, 4, lKingLocation, true);
				RegisteredPieces[i]->SetActorLocation(FVector(lKingLocation.X, lKingLocation.Y, ChessGrid->GetActorLocation().Z));
				GridRow[7].GridColumn[4] = RegisteredPieces[i];

				lPieceInfo.sChessPiece = RegisteredPieces[i];
				lPieceInfo.sChessCoordinate = FVector2D(7, 4);
				RegisteredBlackPieces.Add(lPieceInfo);
				BlackKingCoordinate = FVector2D(7, 4);
				break;
			}
			break;
		default:
			break;
		}
	}
}

void AChessManager::SpawnPiece(EChessPieceType PieceType, ETeamColor Team)
{
	AChessPieces* lNewChessPiece;
	switch (Team)
	{
	case ETeamColor::White:
		lNewChessPiece = GetWorld()->SpawnActor<AChessPieces>(FVector(0, 0, 0), FRotator(0, 90, 0));
		lNewChessPiece->SetPieceTeam(Team);
		lNewChessPiece->SetPieceType(PieceType);
		switch (PieceType)
		{
		case EChessPieceType::Pawn:
			lNewChessPiece->SetPieceMesh(PieceMeshes.WhitePawnMesh);
			lNewChessPiece->SetPieceOverlapArea(PieceMeshes.WhitePawnMesh);
			break;
		case EChessPieceType::Rook:
			lNewChessPiece->SetPieceMesh(PieceMeshes.WhiteRookMesh);
			lNewChessPiece->SetPieceOverlapArea(PieceMeshes.WhiteRookMesh);
			break;
		case EChessPieceType::Knight:
			lNewChessPiece->SetPieceMesh(PieceMeshes.WhiteKnightMesh);
			lNewChessPiece->SetPieceOverlapArea(PieceMeshes.WhiteKnightMesh);
			break;
		case EChessPieceType::Bishop:
			lNewChessPiece->SetPieceMesh(PieceMeshes.WhiteBishopMesh);
			lNewChessPiece->SetPieceOverlapArea(PieceMeshes.WhiteBishopMesh);
			break;
		case EChessPieceType::Queen:
			lNewChessPiece->SetPieceMesh(PieceMeshes.WhiteQueenMesh);
			lNewChessPiece->SetPieceOverlapArea(PieceMeshes.WhiteQueenMesh);
			break;
		case EChessPieceType::King:
			lNewChessPiece->SetPieceMesh(PieceMeshes.WhiteKingMesh);
			lNewChessPiece->SetPieceOverlapArea(PieceMeshes.WhiteKingMesh);
			WhiteKingActor = lNewChessPiece;
			break;
		}
		
		RegisteredPieces.Add(lNewChessPiece);
		break;
	case ETeamColor::Black:
		lNewChessPiece = GetWorld()->SpawnActor<AChessPieces>(FVector(0, 0, 0), FRotator(0, 90, 0));
		lNewChessPiece->SetPieceTeam(Team);
		lNewChessPiece->SetPieceType(PieceType);
		switch (PieceType)
		{
		case EChessPieceType::Pawn:
			lNewChessPiece->SetPieceMesh(PieceMeshes.BlackPawnMesh);
			lNewChessPiece->SetPieceOverlapArea(PieceMeshes.BlackPawnMesh);
			break;
		case EChessPieceType::Rook:
			lNewChessPiece->SetPieceMesh(PieceMeshes.BlackRookMesh);
			lNewChessPiece->SetPieceOverlapArea(PieceMeshes.BlackRookMesh);
			break;
		case EChessPieceType::Knight:
			lNewChessPiece->SetPieceMesh(PieceMeshes.BlackKnightMesh);
			lNewChessPiece->SetPieceOverlapArea(PieceMeshes.BlackKnightMesh);
			break;
		case EChessPieceType::Bishop:
			lNewChessPiece->SetPieceMesh(PieceMeshes.BlackBishopMesh);
			lNewChessPiece->SetPieceOverlapArea(PieceMeshes.BlackBishopMesh);
			break;
		case EChessPieceType::Queen:
			lNewChessPiece->SetPieceMesh(PieceMeshes.BlackQueenMesh);
			lNewChessPiece->SetPieceOverlapArea(PieceMeshes.BlackQueenMesh);
			break;
		case EChessPieceType::King:
			lNewChessPiece->SetPieceMesh(PieceMeshes.BlackKingMesh);
			lNewChessPiece->SetPieceOverlapArea(PieceMeshes.BlackKingMesh);
			BlackKingActor = lNewChessPiece;
			break;
		}
		RegisteredPieces.Add(lNewChessPiece);
		break;
	}
	
}

void AChessManager::SetTheChessBoard()
{
	EChessPieceType ChessPieceType = EChessPieceType::Pawn;
	ETeamColor TeamWhite = ETeamColor::White;
	ETeamColor TeamBlack = ETeamColor::Black;
	for (int32 i = 0; i < 8; i++) // Spawn all pawns
	{
		SpawnPiece(ChessPieceType, TeamWhite);
		SpawnPiece(ChessPieceType, TeamBlack);
	}
	ChessPieceType = EChessPieceType::Rook;
	for (int32 i = 0; i < 2; i++) // Spawn all rooks
	{
		SpawnPiece(ChessPieceType, TeamWhite);
		SpawnPiece(ChessPieceType, TeamBlack);
	}
	ChessPieceType = EChessPieceType::Knight;
	for (int32 i = 0; i < 2; i++) // Spawn all knights
	{
		SpawnPiece(ChessPieceType, TeamWhite);
		SpawnPiece(ChessPieceType, TeamBlack);
	}
	ChessPieceType = EChessPieceType::Bishop;
	for (int32 i = 0; i < 2; i++) // Spawn all bishops
	{
		SpawnPiece(ChessPieceType, TeamWhite);
		SpawnPiece(ChessPieceType, TeamBlack);
	}
	ChessPieceType = EChessPieceType::Queen;
	for (int32 i = 0; i < 1; i++) // Spawn all queens
	{
		SpawnPiece(ChessPieceType, TeamWhite);
		SpawnPiece(ChessPieceType, TeamBlack);
	}
	ChessPieceType = EChessPieceType::King;
	for (int32 i = 0; i < 1; i++) // Spawn all kings
	{
		SpawnPiece(ChessPieceType, TeamWhite);
		SpawnPiece(ChessPieceType, TeamBlack);
	}

	if(ChessGrid)
		AlignBoardForStartPosition();
}

AChessPieces* AChessManager::GetChessPieceFromTile(int32 Row, int32 Column, bool& OutIsEmpty)
{
	if (Row > GridRow.Num() || Column > GridRow[0].GridColumn.Num() || Row < 0 || Column < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Get chess piece from tile row or column parameters are unvalid"));
		return nullptr;
	}
	if (GridRow[Row].GridColumn[Column])
	{
		OutIsEmpty = false;
		return GridRow[Row].GridColumn[Column];
	}
	else
	{
		OutIsEmpty = true;
		return nullptr;
	}
	
}

TArray<FVector2D> AChessManager::GetPieceMovableCoordinates(AChessPieces* PieceActor, const float Row, const float Column)
{
	TArray<FVector2D> lPieceMovableCoordinates;
	switch (PieceActor->GetPieceType())
	{
	case Pawn:
		GetPawnMovableCoordinates(PieceActor->GetPieceTeam(), Row, Column, lPieceMovableCoordinates, PieceActor->GetPawnFirstMovement());
		break;
	case Rook:
		GetRookMovableCoordinates(PieceActor->GetPieceTeam(), Row, Column, lPieceMovableCoordinates);
		break;
	case Knight:
		GetKnightMovableCoordinates(PieceActor->GetPieceTeam(), Row, Column, lPieceMovableCoordinates);
		break;
	case Bishop:
		GetBishopMovableCoordinates(PieceActor->GetPieceTeam(), Row, Column, lPieceMovableCoordinates);
		break;
	case Queen:
		GetQueenMovableCoordinates(PieceActor->GetPieceTeam(), Row, Column, lPieceMovableCoordinates);
		break;
	case King:
		GetKingMovableCoordinates(PieceActor->GetPieceTeam(), Row, Column, lPieceMovableCoordinates);
		break;
	default:
		break;
	}
	return lPieceMovableCoordinates;
}

void AChessManager::FillForbiddenCoordinates(ETeamColor TeamTurn)
{
	switch (TeamTurn)
	{
	case White:
		for (int32 i = 0; i < RegisteredBlackPieces.Num(); i++)
		{
			GetPieceMovableCoordinates(RegisteredBlackPieces[i].sChessPiece, RegisteredBlackPieces[i].sChessCoordinate.X,
				RegisteredBlackPieces[i].sChessCoordinate.Y);
		}
		break;
	case Black:
		for (int32 i = 0; i < RegisteredWhitePieces.Num(); i++)
		{
			GetPieceMovableCoordinates(RegisteredWhitePieces[i].sChessPiece, RegisteredWhitePieces[i].sChessCoordinate.X,
				RegisteredWhitePieces[i].sChessCoordinate.Y);
		}
		break;
	}
	UE_LOG(LogTemp, Error, TEXT("Path to king coordinates ->"));
	for (const FVector2D& lPathToKing : PathToKingCoordinates)
	{
		UE_LOG(LogTemp, Warning, TEXT("X: %d, Y: %d"), (int32)lPathToKing.X, (int32)lPathToKing.Y);
	}
}

void AChessManager::ExecuteNextTurn()
{
	PathToKingCoordinates.Empty();
	DTilesToWhiteKing.Empty();
	DTilesToBlackKing.Empty();
	UpdateKingsCoordinates();
	//PrintAllRPIs();
}

bool AChessManager::UpdatePieceLocation(AChessPieces* PieceToMove, int32 OldRow, int32 OldColumn, int32 NewRow, int32 NewColumn)
{
	FVector lFirstLocation = PieceToMove->GetActorLocation();
	bool lIsTileEmpty;
	AChessPieces* lPieceInThatTile = GetChessPieceFromTile(NewRow, NewColumn, lIsTileEmpty);
	
	if (!lIsTileEmpty && lPieceInThatTile) // If target tile is not empty
	{
		if (lPieceInThatTile->GetPieceTeam() != PieceToMove->GetPieceTeam()) // Then check whether or not moving piece and target piece is in the same team
		{
			//
			GridRow[OldRow].GridColumn[OldColumn] = nullptr;

			GridRow[NewRow].GridColumn[NewColumn] = PieceToMove;
			UpdatePieceInfoCoordinate(PieceToMove, NewRow, NewColumn);
			int32 CheckPieceIndex;
			SafeDeleteRegisteredPiece(lPieceInThatTile, CheckPieceIndex);
			// Logical movement. At this point pieces are considered to have moved

			if (PieceToMove->GetPieceType() != King && !IsMovementValid(PieceToMove->GetPieceTeam())) // If the player didn't move the king then check if king is safe
			{
				SafeRecoverRegisteredPiece(lPieceInThatTile, FVector2D(NewRow, NewColumn), CheckPieceIndex);
				SafeReverseMovement(lPieceInThatTile, FVector2D(NewRow, NewColumn), PieceToMove, FVector2D(OldRow, OldColumn)); // Back to old positions
				return false;
			}
			DisableThePiece(lPieceInThatTile);

			FVector2D lNewLocation;
			ChessGrid->FindLocationFromTile(NewRow, NewColumn, lNewLocation, true);

			PieceToMove->SetSplineForDefaultMovements(lFirstLocation, FVector(lNewLocation.X, lNewLocation.Y, ChessGrid->GetActorLocation().Z));
			return true;
		}
		else // If moving piece and target piece is in the same team
		{
			return false;
		}
	}
	else // If target tile is empty
	{
		GridRow[OldRow].GridColumn[OldColumn] = nullptr;
		GridRow[NewRow].GridColumn[NewColumn] = PieceToMove;
		UpdatePieceInfoCoordinate(PieceToMove, NewRow, NewColumn);

		if (PieceToMove->GetPieceType() != King && !IsMovementValid(PieceToMove->GetPieceTeam())) // If the player didn't move the king then check if king is safe
		{
			SafeReverseMovement(lPieceInThatTile, FVector2D(NewRow, NewColumn), PieceToMove, FVector2D(OldRow, OldColumn)); // Back to old positions
			return false;
		}

		FVector2D lNewLocation;
		ChessGrid->FindLocationFromTile(NewRow, NewColumn, lNewLocation, true);
		
		PieceToMove->SetSplineForDefaultMovements(lFirstLocation, FVector(lNewLocation.X, lNewLocation.Y, ChessGrid->GetActorLocation().Z));
		return true;
	}
	
}

void AChessManager::UpdatePieceInfoCoordinate(AChessPieces* PieceToMove, int32 NewRow, int32 NewColumn)
{
	if (!PieceToMove)
	{
		return;
	}
		
	switch (PieceToMove->GetPieceTeam())
	{
	case White:
		for (int32 i = 0; i < RegisteredWhitePieces.Num(); i++)
		{
			if (RegisteredWhitePieces[i].sChessPiece == PieceToMove)
			{
				RegisteredWhitePieces[i].sChessCoordinate = FVector2D(NewRow, NewColumn);
				return;
			}
		}
		break;
	case Black:
		for (int32 i = 0; i < RegisteredBlackPieces.Num(); i++)
		{
			if (RegisteredBlackPieces[i].sChessPiece == PieceToMove)
			{
				RegisteredBlackPieces[i].sChessCoordinate = FVector2D(NewRow, NewColumn);
				return;
			}
		}
		break;
	}
	
}

void AChessManager::PrintAllRPIs() // RPI = Registered Piece Info
{
	UE_LOG(LogTemp, Warning, TEXT("Total white piece registered now is %d"), RegisteredWhitePieces.Num());
	for (int32 i = 0; i < RegisteredWhitePieces.Num(); i++)
	{
		UE_LOG(LogTemp, Display, TEXT("%d piece, Row %d, Column %d"), i, (int32)RegisteredWhitePieces[i].sChessCoordinate.X,
			(int32)RegisteredWhitePieces[i].sChessCoordinate.Y);
	}
	UE_LOG(LogTemp, Warning, TEXT("Total black piece registered now is %d"), RegisteredBlackPieces.Num());
	for (int32 i = 0; i < RegisteredBlackPieces.Num(); i++)
	{
		UE_LOG(LogTemp, Display, TEXT("%d th piece, Row %d, Column %d"), i, (int32)RegisteredBlackPieces[i].sChessCoordinate.X,
			(int32)RegisteredBlackPieces[i].sChessCoordinate.Y);
	}
}

void AChessManager::DisableThePiece(AChessPieces* PieceToDisable)
{
	/*
	switch (PieceToDisable->GetPieceTeam())
	{
	case White:
		UE_LOG(LogTemp, Display, TEXT("(Before)White pieces count: %d"), RegisteredWhitePieces.Num());
		for (int32 i = 0; i < RegisteredWhitePieces.Num(); i++)
		{
			if (RegisteredWhitePieces[i].sChessPiece == PieceToDisable)
			{
				RegisteredWhitePieces.RemoveAt(i);
				PieceToDisable->Destroy();
				UE_LOG(LogTemp, Display, TEXT("(Deleted) White pieces count: %d"), RegisteredWhitePieces.Num());
				return;
			}
		}
		UE_LOG(LogTemp, Error, TEXT("Couldn't find white piece to delete"), RegisteredWhitePieces.Num());
		break;
	case Black:
		UE_LOG(LogTemp, Display, TEXT("(Before)Black pieces count: %d"));
		for (int32 i = 0; i < RegisteredBlackPieces.Num(); i++)
		{
			if (RegisteredBlackPieces[i].sChessPiece == PieceToDisable)
			{
				RegisteredBlackPieces.RemoveAt(i);
				PieceToDisable->Destroy();
				UE_LOG(LogTemp, Display, TEXT("(Deleted) Black pieces count: %d"), RegisteredBlackPieces.Num());
				return;
			}
		}
		UE_LOG(LogTemp, Error, TEXT("Couldn't find black piece to delete"));
		break;
	}
	*/
	//PieceToDisable->Destroy();
	PieceToDisable->SetHasBeaten(true);
	
}

void AChessManager::GetPawnMovableCoordinates(ETeamColor TeamOfPawn, const float CurrentRow, const float CurrentColumn, TArray<FVector2D>& OutMovableCoordinates, bool PawnFirstMovement)
{
	AChessPieces* lLeftCornerPiece;
	AChessPieces* lRightCornerPiece;
	bool lRightCornerEmpty = true, lLeftCornerEmpty = true, lFrontEmpty = false;
	TArray<FVector2D> lMovableCoArray;
	switch (TeamOfPawn)
	{
	case White: // Positive direction
		if (CurrentRow >= 7) // Is pawn at the end of the board
		{
			OutMovableCoordinates.Empty();
			return;
		}
		if (CurrentColumn < 7) // Is pawn (from the white team perspective) at the rightest side of the board
		{
			lRightCornerPiece = GetChessPieceFromTile(CurrentRow + 1, CurrentColumn + 1, lRightCornerEmpty);
			if (!lRightCornerEmpty)
			{
				if (TeamOfPawn != lRightCornerPiece->GetPieceTeam())
				{
					SetKingDangerType(EatOrEscape, lRightCornerPiece, FVector2D(CurrentRow + 1, CurrentColumn + 1), FVector2D(CurrentRow, CurrentColumn));
					OutMovableCoordinates.Add(FVector2D(CurrentRow + 1, CurrentColumn + 1));
					UE_LOG(LogTemp, Display, TEXT("You can move to right forward corner to eat enemy"));
				}

			}
			DTilesToBlackKing.Add(FVector2D(CurrentRow + 1, CurrentColumn + 1));
		}
		

		if (CurrentColumn > 0) // Is pawn (from the white team perspective) at the leftest side of the board
		{
			lLeftCornerPiece = GetChessPieceFromTile(CurrentRow + 1, CurrentColumn - 1, lLeftCornerEmpty);
			if (!lLeftCornerEmpty)
			{
				if (TeamOfPawn != lLeftCornerPiece->GetPieceTeam())
				{
					SetKingDangerType(EatOrEscape, lLeftCornerPiece, FVector2D(CurrentRow + 1, CurrentColumn - 1), FVector2D(CurrentRow, CurrentColumn));
					OutMovableCoordinates.Add(FVector2D(CurrentRow + 1, CurrentColumn - 1));
					UE_LOG(LogTemp, Display, TEXT("You can move to left forward corner to eat enemy"));
				}
			}
			DTilesToBlackKing.Add(FVector2D(CurrentRow + 1, CurrentColumn - 1));
		}
		if (PawnFirstMovement) // If pawn is going to move for the first time then it can move 1 more tile
		{
			bool lFirstMovementEmpty = false;
			GetChessPieceFromTile(CurrentRow + 2, CurrentColumn, lFirstMovementEmpty);
			if (lFirstMovementEmpty)
				OutMovableCoordinates.Add(FVector2D(CurrentRow + 2, CurrentColumn));
		}
		
		GetChessPieceFromTile(CurrentRow + 1, CurrentColumn, lFrontEmpty); // Check if front is empty
		if (lFrontEmpty)
			OutMovableCoordinates.Add(FVector2D(CurrentRow + 1, CurrentColumn));
		break;
	case Black: // Negative Direction

		if (CurrentRow <= 0) // Is pawn at the end of the board
		{
			OutMovableCoordinates.Empty();
			return;
		}
		if (CurrentColumn < 7) // Is pawn (from the black team perspective) at the leftest side of the board
		{
			lLeftCornerPiece = GetChessPieceFromTile(CurrentRow - 1, CurrentColumn + 1, lLeftCornerEmpty);
			if (!lLeftCornerEmpty)
			{
				if (TeamOfPawn != lLeftCornerPiece->GetPieceTeam())
				{
					SetKingDangerType(EatOrEscape, lLeftCornerPiece, FVector2D(CurrentRow - 1, CurrentColumn + 1), FVector2D(CurrentRow, CurrentColumn));
					OutMovableCoordinates.Add(FVector2D(CurrentRow - 1, CurrentColumn + 1));
					UE_LOG(LogTemp, Display, TEXT("You can move to left forward corner to eat enemy"));
				}
			}
			DTilesToWhiteKing.Add(FVector2D(CurrentRow - 1, CurrentColumn + 1));
		}
		
		
		if (CurrentColumn > 0) // Is pawn (from the black team perspective) at the rightest side of the board
		{
			lRightCornerPiece = GetChessPieceFromTile(CurrentRow - 1, CurrentColumn - 1, lRightCornerEmpty);
			if (!lRightCornerEmpty)
			{
				if (TeamOfPawn != lRightCornerPiece->GetPieceTeam())
				{
					SetKingDangerType(EatOrEscape, lRightCornerPiece, FVector2D(CurrentRow - 1, CurrentColumn - 1), FVector2D(CurrentRow, CurrentColumn));
					OutMovableCoordinates.Add(FVector2D(CurrentRow - 1, CurrentColumn - 1));
					UE_LOG(LogTemp, Display, TEXT("You can move to right forward corner to eat enemy"));
				}
			}
			DTilesToWhiteKing.Add(FVector2D(CurrentRow - 1, CurrentColumn - 1));
		}
		if (PawnFirstMovement) // If pawn is going to move for the first time then it can move 1 more tile
		{
			bool lFirstMovementEmpty = false;
			GetChessPieceFromTile(CurrentRow - 2, CurrentColumn, lFirstMovementEmpty);
			if (lFirstMovementEmpty)
				OutMovableCoordinates.Add(FVector2D(CurrentRow - 2, CurrentColumn));
		}

		GetChessPieceFromTile(CurrentRow - 1, CurrentColumn, lFrontEmpty); // Check if front is empty
		if (lFrontEmpty)
			OutMovableCoordinates.Add(FVector2D(CurrentRow - 1, CurrentColumn));
		break;
	}
}


void AChessManager::GetRookMovableCoordinates(ETeamColor TeamOfRook, const float CurrentRow, const float CurrentColumn, TArray<FVector2D>& OutMovableCoordinates)
{
	AChessPieces* FoundPiece;
	bool IsTileEmpty = true;
	int32 LoopRunTime = 0;
	for (float i = CurrentRow + 1; i < GridRow.Num(); i++) // Check All Rows To Positive Direction Until Finding A Piece
	{
		if (LoopRunTime > 8)
		{
			UE_LOG(LogTemp, Error, TEXT("1. Rook loop has took way too long"));
			break;
		}
		//UE_LOG(LogTemp, Warning, TEXT("%f. Now checking %f. row, %f. column"), i - CurrentRow, i, CurrentColumn);
		FoundPiece = GetChessPieceFromTile(i, CurrentColumn, IsTileEmpty);

		
		LoopRunTime++;
		if (!IsTileEmpty)
		{
			if (FoundPiece)
			{
				if (FoundPiece->GetPieceTeam() != TeamOfRook)
				{
					SetKingDangerType(BlockEatOrEscape, FoundPiece, FVector2D(i, CurrentColumn), FVector2D(CurrentRow, CurrentColumn));
					OutMovableCoordinates.Add(FVector2D(i, CurrentColumn));
				}
				
				switch (TeamOfRook)
				{
				case White:
					DTilesToBlackKing.Add(FVector2D(i, CurrentColumn));
					break;
				case Black:
					DTilesToWhiteKing.Add(FVector2D(i, CurrentColumn));
					break;
				}
			}
			break;
		}
		switch (TeamOfRook)
		{
		case White:
			DTilesToBlackKing.Add(FVector2D(i, CurrentColumn));
			break;
		case Black:
			DTilesToWhiteKing.Add(FVector2D(i, CurrentColumn));
			break;
		}
		OutMovableCoordinates.Add(FVector2D(i, CurrentColumn));
			
	}
	LoopRunTime = 0;
	IsTileEmpty = true;
	for (float i = CurrentRow - 1; i >= 0; i--) // Check All Rows To Negative Direction Until Finding A Piece
	{
		if (LoopRunTime > 8)
		{
			UE_LOG(LogTemp, Error, TEXT("2. Rook loop has took way too long"));
			break;
		}
		//UE_LOG(LogTemp, Warning, TEXT("%f. Now checking %f. row, %f. column"), i - CurrentRow, i, CurrentColumn);
		FoundPiece = GetChessPieceFromTile(i, CurrentColumn, IsTileEmpty);

		
		LoopRunTime++;
		if (!IsTileEmpty)
		{
			if (FoundPiece)
			{
				if (FoundPiece->GetPieceTeam() != TeamOfRook)
				{
					SetKingDangerType(BlockEatOrEscape, FoundPiece, FVector2D(i, CurrentColumn), FVector2D(CurrentRow, CurrentColumn));
					OutMovableCoordinates.Add(FVector2D(i, CurrentColumn));
				}

				switch (TeamOfRook)
				{
				case White:
					DTilesToBlackKing.Add(FVector2D(i, CurrentColumn));
					break;
				case Black:
					DTilesToWhiteKing.Add(FVector2D(i, CurrentColumn));
					break;
				}
			}
			break;
		}
		switch (TeamOfRook)
		{
		case White:
			DTilesToBlackKing.Add(FVector2D(i, CurrentColumn));
			break;
		case Black:
			DTilesToWhiteKing.Add(FVector2D(i, CurrentColumn));
			break;
		}
		OutMovableCoordinates.Add(FVector2D(i, CurrentColumn));
	}
	LoopRunTime = 0;
	IsTileEmpty = true;
	for (float i = CurrentColumn + 1; i < GridRow[CurrentRow].GridColumn.Num(); i++) // Check All Columns To Positive Direction Until Finding A Piece
	{
		if (LoopRunTime > 8)
		{
			UE_LOG(LogTemp, Error, TEXT("3. Rook loop has took way too long"));
			break;
		}
		//UE_LOG(LogTemp, Warning, TEXT("%f. Now checking %f. row, %f. column"), i - CurrentColumn, CurrentRow, i);
		FoundPiece = GetChessPieceFromTile(CurrentRow, i, IsTileEmpty);
		
		
		LoopRunTime++;
		if (!IsTileEmpty)
		{
			if (FoundPiece)
			{
				if (FoundPiece->GetPieceTeam() != TeamOfRook)
				{
					SetKingDangerType(BlockEatOrEscape, FoundPiece, FVector2D(CurrentRow, i), FVector2D(CurrentRow, CurrentColumn));
					OutMovableCoordinates.Add(FVector2D(CurrentRow, i));
				}
				
				switch (TeamOfRook)
				{
				case White:
					DTilesToBlackKing.Add(FVector2D(CurrentRow, i));
					break;
				case Black:
					DTilesToWhiteKing.Add(FVector2D(CurrentRow, i));
					break;
				}
			}
			break;
		}
		switch (TeamOfRook)
		{
		case White:
			DTilesToBlackKing.Add(FVector2D(CurrentRow, i));
			break;
		case Black:
			DTilesToWhiteKing.Add(FVector2D(CurrentRow, i));
			break;
		}
		OutMovableCoordinates.Add(FVector2D(CurrentRow, i));
			
	}
	LoopRunTime = 0;
	IsTileEmpty = true;
	for (float i = CurrentColumn - 1; i >= 0; i--) // Check All Columns To Negative Direction Until Finding A Piece
	{
		if (LoopRunTime > 8)
		{
			UE_LOG(LogTemp, Error, TEXT("4. Rook loop has took way too long"));
			break;
		}
		//UE_LOG(LogTemp, Warning, TEXT("%f. Now checking %f. row, %f. column"), i - CurrentColumn, CurrentRow, i);
		FoundPiece = GetChessPieceFromTile(CurrentRow, i, IsTileEmpty);

		
		LoopRunTime++;
		if (!IsTileEmpty)
		{
			if (FoundPiece)
			{
				if (FoundPiece->GetPieceTeam() != TeamOfRook)
				{
					SetKingDangerType(BlockEatOrEscape, FoundPiece, FVector2D(CurrentRow, i), FVector2D(CurrentRow, CurrentColumn));
					OutMovableCoordinates.Add(FVector2D(CurrentRow, i));
				}
				switch (TeamOfRook)
				{
				case White:
					DTilesToBlackKing.Add(FVector2D(CurrentRow, i));
					break;
				case Black:
					DTilesToWhiteKing.Add(FVector2D(CurrentRow, i));
					break;
				}
			}
			break;
		}
		switch (TeamOfRook)
		{
		case White:
			DTilesToBlackKing.Add(FVector2D(CurrentRow, i));
			break;
		case Black:
			DTilesToWhiteKing.Add(FVector2D(CurrentRow, i));
			break;
		}
		OutMovableCoordinates.Add(FVector2D(CurrentRow, i));
	}
}

void AChessManager::GetKnightMovableCoordinates(ETeamColor TeamOfKnight, const float CurrentRow, const float CurrentColumn, TArray<FVector2D>& OutMovableCoordinates)
{
	TArray<float> KnightColumnMoves = { 1, 1, -1, -1, 2, -2, 2, -2 };
	TArray<float> KnightRowMoves = { 2, -2, 2, -2, 1, 1, -1, -1 };
	bool lValid;
	for (int32 i = 0; i < 8; i++)
	{
		FVector2D KnightMovableTile = FVector2D(CurrentRow + KnightRowMoves[i], CurrentColumn + KnightColumnMoves[i]);
		lValid = ChessGrid->IsTileValid(KnightMovableTile.X, KnightMovableTile.Y);
		if (lValid)
		{
			bool lIsTileEmpty;
			AChessPieces* lChessPiece = GetChessPieceFromTile(KnightMovableTile.X, KnightMovableTile.Y, lIsTileEmpty);
			if (!lIsTileEmpty)
			{
				if (lChessPiece)
				{
					if (lChessPiece->GetPieceTeam() != TeamOfKnight)
					{
						SetKingDangerType(EatOrEscape, lChessPiece, FVector2D(KnightMovableTile.X, KnightMovableTile.Y), FVector2D(CurrentRow, CurrentColumn));
						OutMovableCoordinates.Add(KnightMovableTile);
					}
					switch (TeamOfKnight)
					{
					case White:
						DTilesToBlackKing.Add(KnightMovableTile);
						UE_LOG(LogTemp, Warning, TEXT("WhiteKnight is protecting row: %d, column: %d"), (int32)KnightMovableTile.X,
							(int32)KnightMovableTile.Y);
						break;
					case Black:
						DTilesToWhiteKing.Add(KnightMovableTile);
						UE_LOG(LogTemp, Warning, TEXT("BlackKnight is protecting row: %d, column: %d"), (int32)KnightMovableTile.X,
							(int32)KnightMovableTile.Y);
						break;
					}
					continue;
				}
			}
			switch (TeamOfKnight)
			{
			case White:
				DTilesToBlackKing.Add(KnightMovableTile);
				UE_LOG(LogTemp, Warning, TEXT("WhiteKnight is protecting row: %d, column: %d"), (int32)KnightMovableTile.X,
					(int32)KnightMovableTile.Y);
				break;
			case Black:
				DTilesToWhiteKing.Add(KnightMovableTile);
				UE_LOG(LogTemp, Warning, TEXT("BlackKnight is protecting row: %d, column: %d"), (int32)KnightMovableTile.X,
					(int32)KnightMovableTile.Y);
				break;
			}
			OutMovableCoordinates.Add(KnightMovableTile);
		}
	}
}

void AChessManager::GetBishopMovableCoordinates(ETeamColor TeamOfBishop, const float CurrentRow, const float CurrentColumn, TArray<FVector2D>& OutMovableCoordinates)
{
	bool lTileEmpty = true;
	int32 LoopRunTime = 0;
	int32 lColumnAddition = 1;
	for (int32 i = CurrentRow + 1; ChessGrid->IsTileValid(i, CurrentColumn + lColumnAddition); i++) // Row Positive Direction, Column Positive Direction
	{
		if (LoopRunTime > 8)
		{
			UE_LOG(LogTemp, Error, TEXT("1. Bishop loop has took way too long"));
			break;
		}
		AChessPieces* lChessPiece = GetChessPieceFromTile(i, CurrentColumn + lColumnAddition, lTileEmpty);
		
		
		if (!lTileEmpty) // Check if tile is full
		{
			if (lChessPiece) // Nullptr checker
			{
				if (lChessPiece->GetPieceTeam() != TeamOfBishop) // Check if the other piece is in same team with selected piece
				{
					SetKingDangerType(BlockEatOrEscape, lChessPiece, FVector2D(i, CurrentColumn + lColumnAddition), FVector2D(CurrentRow, CurrentColumn));
					OutMovableCoordinates.Add(FVector2D(i, CurrentColumn + lColumnAddition));
				}
				switch (TeamOfBishop)
				{
				case White:
					DTilesToBlackKing.Add(FVector2D(i, CurrentColumn + lColumnAddition));
					break;
				case Black:
					DTilesToWhiteKing.Add(FVector2D(i, CurrentColumn + lColumnAddition));
					break;
				}
			}
			break;
		}
		switch (TeamOfBishop)
		{
		case White:
			DTilesToBlackKing.Add(FVector2D(i, CurrentColumn + lColumnAddition));
			break;
		case Black:
			DTilesToWhiteKing.Add(FVector2D(i, CurrentColumn + lColumnAddition));
			break;
		}
		OutMovableCoordinates.Add(FVector2D(i, CurrentColumn + lColumnAddition));
		lColumnAddition++;
		LoopRunTime++;
		
	}
	lColumnAddition = 1;
	lTileEmpty = true;
	LoopRunTime = 0;
	for (int32 i = CurrentRow + 1; ChessGrid->IsTileValid(i, CurrentColumn - lColumnAddition); i++) // Row Positive Direction, Column Negative Direction
	{
		if (LoopRunTime > 8)
		{
			UE_LOG(LogTemp, Error, TEXT("2. Bishop loop has took way too long"));
			break;
		}
		AChessPieces* lChessPiece = GetChessPieceFromTile(i, CurrentColumn - lColumnAddition, lTileEmpty);
		
		
		if (!lTileEmpty)
		{
			if (lChessPiece) // Nullptr checker
			{
				if (lChessPiece->GetPieceTeam() != TeamOfBishop) // Check if the other piece is in same team with selected piece
				{
					SetKingDangerType(BlockEatOrEscape, lChessPiece, FVector2D(i, CurrentColumn - lColumnAddition), FVector2D(CurrentRow, CurrentColumn));
					OutMovableCoordinates.Add(FVector2D(i, CurrentColumn - lColumnAddition));
				}
				switch (TeamOfBishop)
				{
				case White:
					DTilesToBlackKing.Add(FVector2D(i, CurrentColumn - lColumnAddition));
					break;
				case Black:
					DTilesToWhiteKing.Add(FVector2D(i, CurrentColumn - lColumnAddition));
					break;
				}
			}
			break;
		}
		switch (TeamOfBishop)
		{
		case White:
			DTilesToBlackKing.Add(FVector2D(i, CurrentColumn - lColumnAddition));
			break;
		case Black:
			DTilesToWhiteKing.Add(FVector2D(i, CurrentColumn - lColumnAddition));
			break;
		}
		OutMovableCoordinates.Add(FVector2D(i, CurrentColumn - lColumnAddition));
		lColumnAddition++;
		LoopRunTime++;
	}
	lColumnAddition = 1;
	lTileEmpty = true;
	LoopRunTime = 0;
	for (int32 i = CurrentRow - 1; ChessGrid->IsTileValid(i, CurrentColumn + lColumnAddition); i--) // Row Negative Direction, Column Positive Direction
	{
		if (LoopRunTime > 8)
		{
			UE_LOG(LogTemp, Error, TEXT("3. Bishop loop has took way too long"));
			break;
		}
		AChessPieces* lChessPiece = GetChessPieceFromTile(i, CurrentColumn + lColumnAddition, lTileEmpty);
		
		
		if (!lTileEmpty)
		{
			if (lChessPiece) // Nullptr checker
			{
				if (lChessPiece->GetPieceTeam() != TeamOfBishop) // Check if the other piece is in same team with selected piece
				{
					SetKingDangerType(BlockEatOrEscape, lChessPiece, FVector2D(i, CurrentColumn + lColumnAddition), FVector2D(CurrentRow, CurrentColumn));
					OutMovableCoordinates.Add(FVector2D(i, CurrentColumn + lColumnAddition));
				}
				switch (TeamOfBishop)
				{
				case White:
					DTilesToBlackKing.Add(FVector2D(i, CurrentColumn + lColumnAddition));
					break;
				case Black:
					DTilesToWhiteKing.Add(FVector2D(i, CurrentColumn + lColumnAddition));
					break;
				}
			}
			
			break;
		}
		switch (TeamOfBishop)
		{
		case White:
			DTilesToBlackKing.Add(FVector2D(i, CurrentColumn + lColumnAddition));
			break;
		case Black:
			DTilesToWhiteKing.Add(FVector2D(i, CurrentColumn + lColumnAddition));
			break;
		}
		OutMovableCoordinates.Add(FVector2D(i, CurrentColumn + lColumnAddition));
		lColumnAddition++;
		LoopRunTime++;
	}
	lColumnAddition = 1;
	lTileEmpty = true;
	LoopRunTime = 0;
	for (int32 i = CurrentRow - 1; ChessGrid->IsTileValid(i, CurrentColumn - lColumnAddition); i--) // Row Negative Direction, Column Negative Direction
	{
		if (LoopRunTime > 8)
		{
			UE_LOG(LogTemp, Error, TEXT("4. Bishop loop has took way too long"));
			break;
		}
		AChessPieces* lChessPiece = GetChessPieceFromTile(i, CurrentColumn - lColumnAddition, lTileEmpty);
		
		if (!lTileEmpty)
		{
			if (lChessPiece) // Nullptr checker
			{
				if (lChessPiece->GetPieceTeam() != TeamOfBishop) // Check if the other piece is in same team with selected piece
				{
					SetKingDangerType(BlockEatOrEscape, lChessPiece, FVector2D(i, CurrentColumn - lColumnAddition), FVector2D(CurrentRow, CurrentColumn));
					OutMovableCoordinates.Add(FVector2D(i, CurrentColumn - lColumnAddition));
				}
				switch (TeamOfBishop)
				{
				case White:
					DTilesToBlackKing.Add(FVector2D(i, CurrentColumn - lColumnAddition));
					break;
				case Black:
					DTilesToWhiteKing.Add(FVector2D(i, CurrentColumn - lColumnAddition));
					break;
				}
			}
			break;
		}
		switch (TeamOfBishop)
		{
		case White:
			DTilesToBlackKing.Add(FVector2D(i, CurrentColumn - lColumnAddition));
			break;
		case Black:
			DTilesToWhiteKing.Add(FVector2D(i, CurrentColumn - lColumnAddition));
			break;
		}
		OutMovableCoordinates.Add(FVector2D(i, CurrentColumn - lColumnAddition));
		lColumnAddition++;
		LoopRunTime++;
	}
}

void AChessManager::GetQueenMovableCoordinates(ETeamColor TeamOfQueen, const float CurrentRow, const float CurrentColumn, TArray<FVector2D>& OutMovableCoordinates)
{
	GetRookMovableCoordinates(TeamOfQueen, CurrentRow, CurrentColumn, OutMovableCoordinates);
	GetBishopMovableCoordinates(TeamOfQueen, CurrentRow, CurrentColumn, OutMovableCoordinates);
	//GetKnightMovableCoordinates(TeamOfQueen, CurrentRow, CurrentColumn, OutMovableCoordinates);
}

void AChessManager::GetKingMovableCoordinates(ETeamColor TeamOfKing, const float CurrentRow, const float CurrentColumn, TArray<FVector2D>& OutMovableCoordinates)
{
	TArray<FVector2D> lDefaultMovableCoordinates;
	TArray<int32> KingRowMovement = { 1, 1, 1, 0, 0, -1, -1, -1 };
	TArray<int32> KingColumnMovement = { 1, -1, 0, 1, -1, 1, -1, 0 };
	for (int32 i = 0; i < 7; i++)
	{
		bool lIsTileEmpty;
		if (ChessGrid->IsTileValid(CurrentRow + KingRowMovement[i], CurrentColumn + KingColumnMovement[i]))
		{
			AChessPieces* lChessPiece = GetChessPieceFromTile(CurrentRow + KingRowMovement[i], CurrentColumn + KingColumnMovement[i], lIsTileEmpty);
			if (!lIsTileEmpty) // If tile full
			{
				if (lChessPiece)
				{
					if (lChessPiece->GetPieceTeam() != TeamOfKing)
					{
						lDefaultMovableCoordinates.Add(FVector2D(CurrentRow + KingRowMovement[i], CurrentColumn + KingColumnMovement[i]));
						UE_LOG(LogTemp, Warning, TEXT("You can eat enemy piece at row: %f, column: %f"), CurrentRow + KingRowMovement[i], CurrentColumn + KingColumnMovement[i]);
						continue;
					}
					continue;
				}
			}
			else // If tile empty
			{
				lDefaultMovableCoordinates.Add(FVector2D(CurrentRow + KingRowMovement[i], CurrentColumn + KingColumnMovement[i]));
				UE_LOG(LogTemp, Display, TEXT("You can move to row: %d, column: %d"), (int32)(CurrentRow + KingRowMovement[i]), 
					(int32)(CurrentColumn + KingColumnMovement[i]));
				continue;
			}
		}
	}
	DelForbidTilesFromDefault(TeamOfKing, lDefaultMovableCoordinates);
	OutMovableCoordinates = lDefaultMovableCoordinates;
}


void AChessManager::DelForbidTilesFromDefault(ETeamColor KingTeam, TArray<FVector2D>& OutKingDefaultMovement)
{
	int32 CheckIndex = 0;
	switch (KingTeam)
	{
	case White:
		for (int32 j = 0; j < OutKingDefaultMovement.Num(); j++)
		{
			UE_LOG(LogTemp, Warning, TEXT("All movable areas: Row: %f, Column: %f"), OutKingDefaultMovement[j].X,
				OutKingDefaultMovement[j].Y);
		}
		for (int32 i = 0; i < DTilesToWhiteKing.Num(); i++) // Check if some of the movable coordinates are forbidden (Protected by another piece)
		{
			if (CheckIndex >= OutKingDefaultMovement.Num())
				break;
			UE_LOG(LogTemp, Display, TEXT("King movable area row: %f, column:%f. Current Checking Forbidden Row: %f, Column: %f, CheckIndex: %d"),
				OutKingDefaultMovement[CheckIndex].X, OutKingDefaultMovement[CheckIndex].Y, DTilesToWhiteKing[i].X, DTilesToWhiteKing[i].Y, CheckIndex);
			if (DTilesToWhiteKing[i].X == OutKingDefaultMovement[CheckIndex].X && DTilesToWhiteKing[i].Y == OutKingDefaultMovement[CheckIndex].Y)
			{
				UE_LOG(LogTemp, Error, TEXT("King cannot go to row: %f, column:%f. It's forbidden! CheckIndex: %d"), DTilesToWhiteKing[i].X, DTilesToWhiteKing[i].Y,
				CheckIndex);
				OutKingDefaultMovement.RemoveAt(CheckIndex); // We are not increasing CheckIndex because when a member of an array deleted array shrinks. 
				i = 0;
				continue;
			}
			if (i == DTilesToWhiteKing.Num() - 1) // If for loop couldn't find until end of the array to find a forbidden tile which matches with the movable tile. Then move on to the next movable tile in the array. End reset the for loop.
			{
				CheckIndex++;
				i = 0;
			}
		}
		break;
	case Black:
		CheckIndex = 0;
		for (int32 j = 0; j < OutKingDefaultMovement.Num(); j++)
		{
			UE_LOG(LogTemp, Warning, TEXT("All movable areas: Row: %f, Column: %f"), OutKingDefaultMovement[j].X,
				OutKingDefaultMovement[j].Y);
		}
		for (int32 i = 0; i < DTilesToBlackKing.Num(); i++) // Check if some of the movable coordinates are forbidden (Protected by another piece)
		{
			if (CheckIndex >= OutKingDefaultMovement.Num())
				break;
			UE_LOG(LogTemp, Display, TEXT("King movable area row: %f, column:%f. Current Checking Forbidden Row: %f, Column: %f, CheckIndex: %d"),
				OutKingDefaultMovement[CheckIndex].X, OutKingDefaultMovement[CheckIndex].Y, DTilesToBlackKing[i].X, DTilesToBlackKing[i].Y, CheckIndex);
			if (DTilesToBlackKing[i].X == OutKingDefaultMovement[CheckIndex].X && DTilesToBlackKing[i].Y == OutKingDefaultMovement[CheckIndex].Y)
			{
				UE_LOG(LogTemp, Error, TEXT("King cannot go to row: %f, column:%f. It's forbidden! CheckIndex: %d"), DTilesToBlackKing[i].X, DTilesToBlackKing[i].Y,
				CheckIndex);
				OutKingDefaultMovement.RemoveAt(CheckIndex); // We are not increasing CheckIndex because when a member of an array deleted array shrinks.
				i = 0;
				continue;
			}
			if (i == DTilesToBlackKing.Num() - 1) // If for loop couldn't find until end of the array to find a forbidden tile which matches with the movable tile. Then move on to the next movable tile in the array. End reset the for loop.
			{
				CheckIndex++;
				i = 0;
			}
		}
		break;
	}
}

void AChessManager::CheckKingsCondition(ETeamColor TeamColor)
{
	DTilesToWhiteKing.Empty();
	DTilesToBlackKing.Empty();
	UpdateKingsCoordinates(); // Refresh kings' location
	FillForbiddenCoordinates(TeamColor); // Refresh dangerous tiles
	
	for (int32 i = 0; i < DTilesToWhiteKing.Num(); i++)
	{
		if (DTilesToWhiteKing[i].X == WhiteKingCoordinate.X && DTilesToWhiteKing[i].Y == WhiteKingCoordinate.Y) // If one of the dangerous tiles is same as the kings location
		{
			WhiteKingBeingThreatened = true;
			UE_LOG(LogTemp, Error, TEXT("White king being threatened"));
			TArray<FVector2D> lKingMovables;
			GetKingMovableCoordinates(White, WhiteKingCoordinate.X, WhiteKingCoordinate.Y, lKingMovables);
			if (lKingMovables.Num() == 0)
			{
				UE_LOG(LogTemp, Error, TEXT("White king being threatened and it can't move anywhere. Black Team Won!"));
				GameOver(Black);
			}
			break;
		}
		WhiteKingBeingThreatened = false;
		UE_LOG(LogTemp, Display, TEXT("White king released"));
	}
	for (int32 i = 0; i < DTilesToBlackKing.Num(); i++)
	{
		if (DTilesToBlackKing[i].X == BlackKingCoordinate.X && DTilesToBlackKing[i].Y == BlackKingCoordinate.Y) // If one of the dangerous tiles is same as the kings location
		{
			BlackKingBeingThreatened = true;
			UE_LOG(LogTemp, Error, TEXT("Black king being threatened"));
			TArray<FVector2D> lKingMovables;
			GetKingMovableCoordinates(Black, BlackKingCoordinate.X, BlackKingCoordinate.Y, lKingMovables);
			if (lKingMovables.Num() == 0)
			{
				UE_LOG(LogTemp, Error, TEXT("Black king being threatened and it can't move anywhere. White Team Won!"));
				GameOver(White);
			}
			break;
		}
		BlackKingBeingThreatened = false;
		UE_LOG(LogTemp, Display, TEXT("Black king released"));
	}
	if (TeamColor == White)
	{
		if (!WhiteKingBeingThreatened)
		{
			PathToKingCoordinates.Empty();
		}
	}
	else
	{
		if (!BlackKingBeingThreatened)
		{
			PathToKingCoordinates.Empty();
		}
	}
}

void AChessManager::UpdateKingsCoordinates()
{
	if (LastWKingIndex < RegisteredWhitePieces.Num())
	{
		if (RegisteredWhitePieces[LastWKingIndex].sChessPiece->GetPieceType() != King) // Check whether or not white king is still at the same index since last execution
		{
			for (int32 i = 0; i < RegisteredWhitePieces.Num(); i++)
			{
				if (RegisteredWhitePieces[i].sChessPiece->GetPieceType() == King)
				{
					WhiteKingCoordinate = RegisteredWhitePieces[i].sChessCoordinate;
					UE_LOG(LogTemp, Warning, TEXT("White king new location: x: %d, y: %d"), (int32)WhiteKingCoordinate.X, (int32)WhiteKingCoordinate.Y);
					LastWKingIndex = i;
					break;
				}
			}
		}
		else
			WhiteKingCoordinate = RegisteredWhitePieces[LastWKingIndex].sChessCoordinate;
	}
	else
	{
		for (int32 i = 0; i < RegisteredWhitePieces.Num(); i++)
		{
			if (RegisteredWhitePieces[i].sChessPiece->GetPieceType() == King)
			{
				WhiteKingCoordinate = RegisteredWhitePieces[i].sChessCoordinate;
				UE_LOG(LogTemp, Warning, TEXT("White king new location: x: %d, y: %d"), (int32)WhiteKingCoordinate.X, (int32)WhiteKingCoordinate.Y);
				LastWKingIndex = i;
				break;
			}
		}
	}

	if (LastBKingIndex < RegisteredBlackPieces.Num())
	{
		if (RegisteredBlackPieces[LastBKingIndex].sChessPiece->GetPieceType() != King) // Check whether or not black king is still at the same index since last execution
		{
			for (int32 i = 0; i < RegisteredBlackPieces.Num(); i++)
			{
				if (RegisteredBlackPieces[i].sChessPiece->GetPieceType() == King)
				{
					BlackKingCoordinate = RegisteredBlackPieces[i].sChessCoordinate;
					UE_LOG(LogTemp, Warning, TEXT("Black king new location: x: %d, y: %d"), (int32)BlackKingCoordinate.X, (int32)BlackKingCoordinate.Y);
					LastWKingIndex = i;
					break;
				}
			}
		}
		else
			BlackKingCoordinate = RegisteredBlackPieces[LastBKingIndex].sChessCoordinate;
	}
	else
	{
		for (int32 i = 0; i < RegisteredBlackPieces.Num(); i++)
		{
			if (RegisteredBlackPieces[i].sChessPiece->GetPieceType() == King)
			{
				BlackKingCoordinate = RegisteredBlackPieces[i].sChessCoordinate;
				UE_LOG(LogTemp, Warning, TEXT("Black king new location: x: %d, y: %d"), (int32)BlackKingCoordinate.X, (int32)BlackKingCoordinate.Y);
				LastWKingIndex = i;
				break;
			}
		}
	}
	
}

void AChessManager::GameOver(ETeamColor WinnerTeam)
{

}

void AChessManager::SetKingDangerType(EDangerType PieceDangerType, AChessPieces* King, const FVector2D& KingCoordinates, const FVector2D& EnemyCoordinates)
{
	if (!King)
	{
		PathToKingCoordinates.Empty();
		return;
	}
	if (King->GetPieceType() == EChessPieceType::King)
	{
		King->SetPieceDangerType(PieceDangerType);
		switch (PieceDangerType)
		{
		case BlockEatOrEscape:
			if (KingCoordinates.X == EnemyCoordinates.X) // If king's row and enemy's row are the same
			{
				int32 lScanDirection;
				if (KingCoordinates.X - EnemyCoordinates.X < 0) // If king is at the lower side of the board
					lScanDirection = 1;
				else
					lScanDirection = -1;
				for (int32 i = KingCoordinates.X; i != EnemyCoordinates.X; i += lScanDirection)
				{
					UE_LOG(LogTemp, Display, TEXT("X Direction. Path to king has been added, X:%d Y:%d"), i, (int32)KingCoordinates.Y);
					PathToKingCoordinates.Add(FVector2D(i, KingCoordinates.Y));
				}
			}
			else if (KingCoordinates.Y == EnemyCoordinates.Y) // If king's column and enemy's column are the same
			{
				int32 lScanDirection;
				if (KingCoordinates.Y - EnemyCoordinates.Y < 0) // If king is at the righter side of the board
					lScanDirection = 1;
				else
					lScanDirection = -1;
				for (int32 i = KingCoordinates.Y; i != EnemyCoordinates.Y; i += lScanDirection)
				{
					UE_LOG(LogTemp, Display, TEXT("Y Direction. Path to king has been added, X:%d Y:%d"), (int32)KingCoordinates.X, i);
					PathToKingCoordinates.Add(FVector2D(KingCoordinates.X, i));
				}
			}
			else // If the enemy has the bishop movement set
			{
				UE_LOG(LogTemp, Warning, TEXT("Bishop movement. Path to king being calculated"));
				if (FMath::Abs(KingCoordinates.X - EnemyCoordinates.X) != FMath::Abs(KingCoordinates.Y - EnemyCoordinates.Y))
				{
					UE_LOG(LogTemp, Error, TEXT("Something wrong with bishop movement calculation. Path to the king is not linear"));
				}
				else
				{
					int32 lStepAmount = FMath::Abs(KingCoordinates.X - EnemyCoordinates.X);

					int32 lXDirection = (KingCoordinates.X - EnemyCoordinates.X) / lStepAmount;
					int32 lYDirection = (KingCoordinates.Y - EnemyCoordinates.Y) / lStepAmount;

					int32 lCurrentX = EnemyCoordinates.X;
					int32 lCurrentY = EnemyCoordinates.Y;
					//UE_LOG(LogTemp, Warning, TEXT("KingX:%f, KingY: %f, EnemyX: %f, EnemyY: %f"), KingCoordinates.X, KingCoordinates.Y, EnemyCoordinates.X, EnemyCoordinates.Y);
					for (int32 i = 1; i < lStepAmount; i++)
					{
						lCurrentX += lXDirection;
						lCurrentY += lYDirection;
						UE_LOG(LogTemp, Display, TEXT("Bishop or Queen is danger to the king. X:%d Y:%d"), lCurrentX, lCurrentY);
						PathToKingCoordinates.Add(FVector2D(lCurrentX, lCurrentY));
					}
					
				}
			}
			break;
		case EatOrEscape:
			//PathToKingCoordinates.Empty();
			break;
		case JustEscape:
			//PathToKingCoordinates.Empty();
			break;
		case Safe:
			//PathToKingCoordinates.Empty();
			break;
		default:
			//PathToKingCoordinates.Empty();
			break;
		}
	}
	else
	{
		//PathToKingCoordinates.Empty(); // If the enemy is not a danger to the king. Then empty this array
	}
}

bool AChessManager::IsMovementValid(ETeamColor TeamColor)
{
	TArray<FVector2D> lKingMovables;
	CheckKingsCondition(TeamColor);
	switch (TeamColor)
	{
	case White:
		if (WhiteKingBeingThreatened)
		{
			GetKingMovableCoordinates(TeamColor, WhiteKingCoordinate.X, WhiteKingCoordinate.Y, lKingMovables);
			if (lKingMovables.Num() == 0) // If king can't move then allow other pieces to move (no other option)
			{
				UE_LOG(LogTemp, Display, TEXT("WKing is in danger but has no place to move. So other pieces free to move"));
				return true;
			}
			else // If king can move and break other piece's movement
			{
				UE_LOG(LogTemp, Error, TEXT("WKing is in danger but it can move. So other pieces cannot move"));
				return false;
			}
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("WKing is free so every other pieces free"));
			return true;
		}	
		break;
	case Black:
		if (BlackKingBeingThreatened)
		{
			GetKingMovableCoordinates(TeamColor, BlackKingCoordinate.X, BlackKingCoordinate.Y, lKingMovables);
			if (lKingMovables.Num() == 0) // If king can't move then allow other pieces to move (no other option)
			{
				UE_LOG(LogTemp, Display, TEXT("BKing is in danger but has no place to move. So other pieces free to move"));
				return true;
			}
			else // If king can move and break other piece's movement
			{
				UE_LOG(LogTemp, Error, TEXT("BKing is in danger but it can move. So other pieces cannot move"));
				return false;
			}	
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("BKing is free so every other pieces free"));
			return true;
		}	
		break;
	default:
		return false;
		break;
	}
}

void AChessManager::SafeReverseMovement(AChessPieces* OldPiece, const FVector2D& OldPieceCoordinate, AChessPieces* NewPiece, const FVector2D& NewPieceCoordinate)
{
	GridRow[OldPieceCoordinate.X].GridColumn[OldPieceCoordinate.Y] = OldPiece;
	if (OldPiece)
	{
		UE_LOG(LogTemp, Display, TEXT("%s returned the old location ox: %d, oy: %d"), *OldPiece->GetActorNameOrLabel(), 
			(int32)OldPieceCoordinate.X, (int32)OldPieceCoordinate.Y);
	}
	UpdatePieceInfoCoordinate(OldPiece, OldPieceCoordinate.X, OldPieceCoordinate.Y);

	GridRow[NewPieceCoordinate.X].GridColumn[NewPieceCoordinate.Y] = NewPiece;
	if (NewPiece)
	{
		UE_LOG(LogTemp, Display, TEXT("%s (moving piece) returned the old location ox: %d, oy: %d"), *NewPiece->GetActorNameOrLabel(),
			(int32)NewPieceCoordinate.X, (int32)NewPieceCoordinate.Y);
	}

	UpdatePieceInfoCoordinate(NewPiece, NewPieceCoordinate.X, NewPieceCoordinate.Y);

	DTilesToWhiteKing.Empty();
	DTilesToBlackKing.Empty();
	FillForbiddenCoordinates(NewPiece->GetPieceTeam());
}

void AChessManager::SafeDeleteRegisteredPiece(AChessPieces* PieceToDelete, int32& OutIndex)
{
	switch (PieceToDelete->GetPieceTeam())
	{
	case White:
		for (int32 i = 0; i < RegisteredWhitePieces.Num(); i++)
		{
			if (RegisteredWhitePieces[i].sChessPiece == PieceToDelete)
			{
				OutIndex = i;
				RegisteredWhitePieces.RemoveAt(i);
			}
		}
		break;
	case Black:
		for (int32 i = 0; i < RegisteredBlackPieces.Num(); i++)
		{
			if (RegisteredBlackPieces[i].sChessPiece == PieceToDelete)
			{
				OutIndex = i;
				RegisteredBlackPieces.RemoveAt(i);
			}
		}
		break;
	}
}

void AChessManager::SafeRecoverRegisteredPiece(AChessPieces* PieceToRecover, FVector2D PieceLocation, const int32 IndexOfPiece)
{
	PieceInfo lOldPiece;
	lOldPiece.sChessPiece = PieceToRecover;
	lOldPiece.sChessCoordinate = PieceLocation;
	switch (PieceToRecover->GetPieceTeam())
	{
	case White:
		RegisteredWhitePieces.Add(lOldPiece);
		break;
	case Black:
		RegisteredBlackPieces.Add(lOldPiece);
		break;
	default:
		break;
	}
}

EChessPieceType AChessManager::ConvertIndexToPieceType(int32 Index)
{
	switch (Index)
	{
	case 0:
		return EChessPieceType::Pawn;
		break;
	case 1:
		return EChessPieceType::Rook;
		break;
	case 2:
		return EChessPieceType::Knight;
		break;
	case 3:
		return EChessPieceType::Bishop;
		break;
	case 4:
		return EChessPieceType::Queen;
		break;
	case 5:
		return EChessPieceType::King;
		break;
	default:
		return EChessPieceType::Pawn;
		break;
	}
}

void AChessManager::SetPawnConvertedPiece(int32 PieceTypeIndex)
{
	ConvertPieceType = ConvertIndexToPieceType(PieceTypeIndex);
}

bool AChessManager::ConvertPawn(const EChessPieceType& NewPieceType, AChessPieces* PawnActor, const FVector2D& PawnCoordinate)
{
	// Sets piece's static mesh
	switch (NewPieceType)
	{
	case Pawn:
		return false;
		break;
	case Rook:
		
		if (PawnActor->GetPieceTeam() == White)
		{
			PawnActor->SetPieceMesh(PieceMeshes.WhiteRookMesh);
		}
		else
		{
			PawnActor->SetPieceMesh(PieceMeshes.BlackRookMesh);
		}
		PawnActor->SetPieceType(Rook);
		break;
	case Knight:
		
		if (PawnActor->GetPieceTeam() == White)
		{
			PawnActor->SetPieceMesh(PieceMeshes.WhiteKnightMesh);
		}
		else
		{
			PawnActor->SetPieceMesh(PieceMeshes.BlackKnightMesh);
		}
		PawnActor->SetPieceType(Knight);
		break;
	case Bishop:
		
		if (PawnActor->GetPieceTeam() == White)
		{
			PawnActor->SetPieceMesh(PieceMeshes.WhiteBishopMesh);
		}
		else
		{
			PawnActor->SetPieceMesh(PieceMeshes.BlackBishopMesh);
		}
		PawnActor->SetPieceType(Bishop);
		break;
	case Queen:
		
		if (PawnActor->GetPieceTeam() == White)
		{
			PawnActor->SetPieceMesh(PieceMeshes.WhiteQueenMesh);
		}
		else
		{
			PawnActor->SetPieceMesh(PieceMeshes.BlackQueenMesh);
		}
		PawnActor->SetPieceType(Queen);
		break;
	case King:
		return false;
		break;
	default:
		return false;
		break;
	}
	PawnActor->SetPieceType(NewPieceType); // When the main pointer's piece type changes the type in piece info and gridrow-gridcolumn arrays changes

	return true;
}

bool AChessManager::CheckMateControl(ETeamColor TeamToCheck)
{
	bool lCurrentCheckMate = true;
	switch (TeamToCheck)
	{
	case White:
		switch (WhiteKingActor->GetPieceDangerType())
		{
		case BlockEatOrEscape:
			for (int32 i = 0; i < RegisteredWhitePieces.Num(); i++)
			{
				TArray<FVector2D> lPieceMovables = GetPieceMovableCoordinates(RegisteredWhitePieces[i].sChessPiece, RegisteredWhitePieces[i].sChessCoordinate.X, 
					RegisteredWhitePieces[i].sChessCoordinate.Y);

				for (const FVector2D& lPathToKing : PathToKingCoordinates)
				{
					for (const FVector2D& lCheckCoordinates : lPieceMovables)
					{
						if (lPathToKing.X == lCheckCoordinates.X && lPathToKing.Y == lCheckCoordinates.Y)
						{
							CheckMateBlockers.Add(RegisteredWhitePieces[i].sChessPiece);
							lCurrentCheckMate = false;
						}
					}
				}
			}
			return lCurrentCheckMate;
			break;
		case EatOrEscape:
			break;
		case JustEscape:
			break;
		case Safe:
			break;
		}
		break;
	case Black:
		switch (WhiteKingActor->GetPieceDangerType())
		{
		case BlockEatOrEscape:
			for (int32 i = 0; i < RegisteredBlackPieces.Num(); i++)
			{
				TArray<FVector2D> lPieceMovables = GetPieceMovableCoordinates(RegisteredBlackPieces[i].sChessPiece, RegisteredBlackPieces[i].sChessCoordinate.X,
					RegisteredBlackPieces[i].sChessCoordinate.Y);

				for (const FVector2D& lPathToKing : PathToKingCoordinates)
				{
					for (const FVector2D& lCheckCoordinates : lPieceMovables)
					{
						if (lPathToKing.X == lCheckCoordinates.X && lPathToKing.Y == lCheckCoordinates.Y)
						{
							CheckMateBlockers.Add(RegisteredBlackPieces[i].sChessPiece);
							lCurrentCheckMate = false;
						}
					}
				}
			}
			return lCurrentCheckMate;
			break;
		case EatOrEscape:
			break;
		case JustEscape:
			break;
		case Safe:
			break;
		}
		break;
	}
	return false;
}