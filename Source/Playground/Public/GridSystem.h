// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridSystem.generated.h"

class UProceduralMeshComponent;
UCLASS()
class PLAYGROUND_API AGridSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool FindTileFromLocation(int32& OutRow, int32& OutColumn, const FVector& Location);
	bool FindLocationFromTile(int32 Row, int32 Column, FVector2D& OutGridLocation, bool Center);

	void SetSelectedTile(int32 Row, int32 Column);

	void CreateLine(FVector Start, FVector End, float Thickness, TArray<FVector>& OutVertices, TArray<int32>& OutTriangles);

	bool IsTileValid(int32 Row, int32 Column);

	void SetHighlightedTiles(const TArray<int32>& HighlightedRow, const TArray<int32>& HighlightedColumn, const TArray<FColor>& HighlightColor);
private:

	void CreateMaterialInstance(UMaterialInstanceDynamic* GridMaterialInstance, const struct FLinearColor& Color, float Opacity);

	float GetGridWidth() const;
	float GetGridHeight() const;

	void CalculateVerticesAndTriangles(TArray<FVector>& OutAllVertices, TArray<int32>& OutAllTriangles);

	void CreateHighlightedTiles();

	UPROPERTY(EditAnywhere)
		class UMaterialInterface* GridMaterial;

	class AChessGameMode* CurrentGameMode;

	UPROPERTY(EditAnywhere)
		int32 GridRowAmount = 8;
	UPROPERTY(EditAnywhere)
		int32 GridColumnAmount = 8;
	UPROPERTY(EditAnywhere)
		// Size of individual tiles
		int32 GridSize = 100;

	UPROPERTY(EditAnywhere)
		float LineThickness = 2.f;

	UPROPERTY(EditAnywhere)
		float LineOpacity = 0.5f;
	UPROPERTY(EditAnywhere)
		float SelectionOpacity = 0.25f;

	UPROPERTY(EditAnywhere)
		FLinearColor LineColor;
	UPROPERTY(EditAnywhere)
		FLinearColor SelectionColor;

	TArray<FVector> HighlightedTileVertices;
	TArray<int32> HighlightedTileTriangles;

	UPROPERTY(EditAnywhere)
		UProceduralMeshComponent* GridProceduralMesh;
	UPROPERTY(EditAnywhere)
		UProceduralMeshComponent* SelectionProceduralMesh;
	UPROPERTY(EditAnywhere)
		TArray<UProceduralMeshComponent*> HighlightProceduralMeshes;
	UPROPERTY(EditAnywhere)
		USceneComponent* DefaultRootComponent;
};
