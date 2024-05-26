// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessManager.generated.h"

USTRUCT(BlueprintType)
struct FChessPieceMeshes
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
		UStaticMesh* WhitePawnMesh;
	UPROPERTY(EditAnywhere)
		UStaticMesh* BlackPawnMesh;

	UPROPERTY(EditAnywhere)
		UStaticMesh* WhiteRookMesh;
	UPROPERTY(EditAnywhere)
		UStaticMesh* BlackRookMesh;

	UPROPERTY(EditAnywhere)
		UStaticMesh* WhiteKnightMesh;
	UPROPERTY(EditAnywhere)
		UStaticMesh* BlackKnightMesh;

	UPROPERTY(EditAnywhere)
		UStaticMesh* WhiteBishopMesh;
	UPROPERTY(EditAnywhere)
		UStaticMesh* BlackBishopMesh;

	UPROPERTY(EditAnywhere)
		UStaticMesh* WhiteQueenMesh;
	UPROPERTY(EditAnywhere)
		UStaticMesh* BlackQueenMesh;

	UPROPERTY(EditAnywhere)
		UStaticMesh* WhiteKingMesh;
	UPROPERTY(EditAnywhere)
		UStaticMesh* BlackKingMesh;
};
struct PieceInfo
{
	class AChessPieces* sChessPiece;
	FVector2D sChessCoordinate;
};

struct ActivePiecesOnGrid
{
public:
	TArray<class AChessPieces*> GridColumn = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
};

enum ESpecialCases
{
	KingInDanger, // Warn player when their king is in danger
	KingSafetyIsPriority, // Warn player when their king is in danger but they moved a piece that doesn't protect king
	Checkmate, // Game over. King has no place to go. (Triggered When The Player Surrenders)
	PawnTransformation // When pawn reaches to the end of the board. Player will be able to change it with any other piece.
};

UCLASS()
class PLAYGROUND_API AChessManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AlignBoardForStartPosition();

	void SpawnPiece(enum EChessPieceType PieceType, enum ETeamColor Team);

	AChessPieces* GetChessPieceFromTile(int32 Row, int32 Column, bool& OutIsEmpty);

	TArray<FVector2D> GetPieceMovableCoordinates(AChessPieces* PieceActor, const float Row, const float  Column);

	void FillForbiddenCoordinates(ETeamColor TeamTurn);
	void ExecuteNextTurn();

	bool UpdatePieceLocation(AChessPieces* PieceToMove, int32 OldRow, int32 OldColumn, int32 NewRow, int32 NewColumn);

	UFUNCTION(BlueprintCallable)
		void SetPawnConvertedPiece(int32 PieceTypeIndex);
	UFUNCTION(BlueprintImplementableEvent)
		void PawnConvertUI(bool ShowUI);
private:

	void DisableThePiece(AChessPieces* PieceToDisable);

	void GetPawnMovableCoordinates(ETeamColor TeamOfPawn, const float CurrentRow, const float CurrentColumn, TArray<FVector2D>& OutMovableCoordinates, bool PawnFirstMovement);
	void GetRookMovableCoordinates(ETeamColor TeamOfRook, const float CurrentRow, const float CurrentColumn, TArray<FVector2D>& OutMovableCoordinates);
	void GetKnightMovableCoordinates(ETeamColor TeamOfKnight, const float CurrentRow, const float CurrentColumn, TArray<FVector2D>& OutMovableCoordinates);
	void GetBishopMovableCoordinates(ETeamColor TeamOfBishop, const float CurrentRow, const float CurrentColumn, TArray<FVector2D>& OutMovableCoordinates);
	void GetQueenMovableCoordinates(ETeamColor TeamOfQueen, const float CurrentRow, const float CurrentColumn, TArray<FVector2D>& OutMovableCoordinates);
	void GetKingMovableCoordinates(ETeamColor TeamOfKing, const float CurrentRow, const float CurrentColumn, TArray<FVector2D>& OutMovableCoordinates);

	void DelForbidTilesFromDefault(ETeamColor KingTeam, TArray<FVector2D>& OutKingDefaultMovement); // Remove enemy defended tiles from king's default movement tiles.

	void UpdatePieceInfoCoordinate(AChessPieces* PieceToMove, int32 NewRow, int32 NewColumn);

	void PrintAllRPIs(); // Registered Pieces Info

	void SetTheChessBoard();

	void CheckKingsCondition(ETeamColor TeamColor); // Run this function every movement.
	void UpdateKingsCoordinates(); // Run this function every turn.
	// Checks if team's king is safe. If not and king has space to move then break movement. King's safety is priority. (Execute after the piece moved)
	bool IsMovementValid(ETeamColor TeamColor);
	void SafeReverseMovement(AChessPieces* OldPiece, const FVector2D& OldPieceCoordinate, AChessPieces* NewPiece, const FVector2D& NewPieceCoordinate);

	void SafeDeleteRegisteredPiece(AChessPieces* PieceToDelete, int32& OutIndex);
	void SafeRecoverRegisteredPiece(AChessPieces* PieceToRecover, FVector2D PieceLocation, const int32 IndexOfPiece);

	bool ConvertPawn(const EChessPieceType& NewPieceType, AChessPieces* PawnActor, const FVector2D& PawnCoordinate);

	void GameOver(ETeamColor WinnerTeam);

	void SetKingDangerType(enum EDangerType PieceDangerType, AChessPieces* King = nullptr, const FVector2D& KingCoordinates = FVector2D(0,0), const FVector2D& EnemyCoordinates = FVector2D(0, 0));

	EChessPieceType ConvertIndexToPieceType(int32 Index);
	
	UPROPERTY(EditAnywhere)
		class AGridSystem* ChessGrid;

	TArray<class AChessPieces*> RegisteredPieces;

	TArray<PieceInfo> RegisteredWhitePieces;
	TArray<PieceInfo> RegisteredBlackPieces;
	UPROPERTY(EditAnywhere)
		FChessPieceMeshes PieceMeshes; // Static meshes struct for chess pieces 

	ActivePiecesOnGrid GridColumn;
	TArray<ActivePiecesOnGrid> GridRow;

	TArray<FVector2D> DTilesToWhiteKing;
	TArray<FVector2D> DTilesToBlackKing;

	bool WhiteKingBeingThreatened, BlackKingBeingThreatened;
	FVector2D WhiteKingCoordinate, BlackKingCoordinate;
	
	int32 LastWKingIndex, LastBKingIndex;

	EChessPieceType ConvertPieceType;
	enum EDangerType KingDangerType;

	AChessPieces* WhiteKingActor;
	AChessPieces* BlackKingActor;

	TArray<FVector2D> PathToKingCoordinates;
	TArray<AChessPieces*> CheckMateBlockers;

	// Experimental
	bool CheckMateControl(ETeamColor TeamToCheck);
};
