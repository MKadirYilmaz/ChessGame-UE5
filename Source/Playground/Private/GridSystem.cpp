// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSystem.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Math/Color.h"
#include "Materials/MaterialInterface.h"
#include "ProceduralMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ChessGameMode.h"


// Sets default values
AGridSystem::AGridSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Root Component"));
	RootComponent = DefaultRootComponent;

	GridProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Grid Procedural Mesh"));
	GridProceduralMesh->SetupAttachment(RootComponent);

	SelectionProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Selection Procedural Mesh"));
	SelectionProceduralMesh->SetupAttachment(RootComponent);

	TArray<FVector> lVertices;
	TArray<int32> lTriangles;
	CalculateVerticesAndTriangles(lVertices, lTriangles);

	
	TArray<FVector> EmptyNormalsArray;
	TArray<FVector2D> EmptyUV0Array;
	TArray<FColor> EmptyVertexColorArray;
	TArray<FProcMeshTangent> EmptyTangentArray;

	GridProceduralMesh->CreateMeshSection(0, lVertices, lTriangles, EmptyNormalsArray, EmptyUV0Array, EmptyVertexColorArray, EmptyTangentArray, false);
	
	

	TArray<FVector> lSelectionVertices;
	TArray<int32> lSelectionTriangles;
	CreateLine(FVector(0, GridSize / 2, 0), FVector(GridSize, GridSize / 2, 0), GridSize, lSelectionVertices, lSelectionTriangles);

	SelectionProceduralMesh->SetVisibility(false);
	
	EmptyNormalsArray.Empty();
	EmptyUV0Array.Empty();
	EmptyVertexColorArray.Empty();
	EmptyTangentArray.Empty();

	SelectionProceduralMesh->CreateMeshSection(0, lSelectionVertices, lSelectionTriangles, EmptyNormalsArray, EmptyUV0Array, 
		EmptyVertexColorArray, EmptyTangentArray, false);
	

}

// Called when the game starts or when spawned
void AGridSystem::BeginPlay()
{
	Super::BeginPlay();
	CurrentGameMode = Cast<AChessGameMode>(UGameplayStatics::GetGameMode(this));
	if (CurrentGameMode)
	{
		CurrentGameMode->SetCurrentChessGrid(this);
	}
	if (GridMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grid Material is not nullptr"))
		UMaterialInstanceDynamic* LinesMaterialInstance = UMaterialInstanceDynamic::Create(GridMaterial, this);
		CreateMaterialInstance(LinesMaterialInstance, LineColor, LineOpacity);

		UMaterialInterface* GridMaterialInterface = Cast<UMaterialInterface>(LinesMaterialInstance);

		if (GridMaterialInterface)
		{
			GridProceduralMesh->SetMaterial(0, GridMaterialInterface);
			UE_LOG(LogTemp, Warning, TEXT("Grid Material Interface is not nullptr and material setted"));
		}

		UMaterialInstanceDynamic* SelectionMaterialInstance = UMaterialInstanceDynamic::Create(GridMaterial, this);
		CreateMaterialInstance(SelectionMaterialInstance, SelectionColor, SelectionOpacity);

		UMaterialInterface* SelectionMaterialInterface = Cast<UMaterialInterface>(SelectionMaterialInstance);
		if (SelectionMaterialInterface)
		{
			SelectionProceduralMesh->SetMaterial(0, SelectionMaterialInterface);

		}
	}
	CreateHighlightedTiles();
}

// Called every frame
void AGridSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGridSystem::FindTileFromLocation(int32& OutRow, int32& OutColumn, const FVector& Location)
{
	OutRow = FMath::Floor(((Location.X - GetActorLocation().X) / GetGridHeight()) * GridRowAmount);
	OutColumn = FMath::Floor(((Location.Y - GetActorLocation().Y) / GetGridWidth()) * GridColumnAmount);
	return IsTileValid(OutRow, OutColumn);
}

bool AGridSystem::FindLocationFromTile(int32 Row, int32 Column, FVector2D& OutGridLocation, bool Center)
{
	OutGridLocation = FVector2D::ZeroVector;
	OutGridLocation.X = Row * GridSize + GetActorLocation().X;
	if (Center)
		OutGridLocation.X += (GridSize / 2);

	OutGridLocation.Y = Column * GridSize + GetActorLocation().Y;
	if (Center)
		OutGridLocation.Y += (GridSize / 2);

	return IsTileValid(Row, Column);
}

void AGridSystem::SetSelectedTile(int32 Row, int32 Column)
{
	FVector2D lGridLocation;
	if (FindLocationFromTile(Row, Column, lGridLocation, false))
	{
		SelectionProceduralMesh->SetVisibility(true);
		SelectionProceduralMesh->SetWorldLocation(FVector(lGridLocation.X, lGridLocation.Y, GetActorLocation().Z));
	}
	else
	{
		SelectionProceduralMesh->SetVisibility(false);
	}
		
}

void AGridSystem::CreateMaterialInstance(UMaterialInstanceDynamic* GridMaterialInstance,const FLinearColor& Color, float Opacity)
{
	FVector4 lBaseColorVector = FVector4(Color.R, Color.G, Color.B, 1);
	GridMaterialInstance->SetVectorParameterValue(TEXT("Base Color"), lBaseColorVector);
	GridMaterialInstance->SetScalarParameterValue(TEXT("Opacity"), Opacity);
}

float AGridSystem::GetGridHeight() const
{
	return GridSize * GridRowAmount;
}

float AGridSystem::GetGridWidth() const
{
	return GridSize * GridColumnAmount;
}

void AGridSystem::CalculateVerticesAndTriangles(TArray<FVector>& OutAllVertices, TArray<int32>& OutAllTriangles)
{
	for (int i = 0; i <= GridRowAmount; i++)
	{
		float lStart = i * GridSize;
		float lEnd = GetGridWidth();
		CreateLine(FVector(lStart, 0, 0), FVector(lStart, lEnd, 0), LineThickness, OutAllVertices, OutAllTriangles);
	}
	for (int i = 0; i <= GridColumnAmount; i++)
	{
		float lStart = i * GridSize;
		float lEnd = GetGridHeight();
		CreateLine(FVector(0, lStart, 0), FVector(lEnd, lStart, 0), LineThickness, OutAllVertices, OutAllTriangles);
	}

}

void AGridSystem::CreateHighlightedTiles()
{
	/*
	CreateLine(FVector(0, GridSize / 2, 0), FVector(GridSize, GridSize / 2, 0), GridSize, HighlightedTileVertices, HighlightedTileTriangles);
	for (int32 Amount = 0; Amount < 27; Amount++)
	{
		HighlightProceduralMeshes.Add(Cast<UProceduralMeshComponent>(AddComponentByClass(UProceduralMeshComponent::StaticClass(), true, FTransform(FRotator::ZeroRotator,
			FVector::Zero(), FVector(1, 1, 1)), false)));
		if (HighlightProceduralMeshes[Amount])
		{
			HighlightProceduralMeshes[Amount]->RegisterComponent();
			TArray<FVector> EmptyNormalsArray;
			TArray<FVector2D> EmptyUV0Array;
			TArray<FColor> EmptyVertexColorArray;
			TArray<FProcMeshTangent> EmptyTangentArray;
			HighlightProceduralMeshes[Amount]->CreateMeshSection(0, HighlightedTileVertices, HighlightedTileTriangles, EmptyNormalsArray, EmptyUV0Array,
				EmptyVertexColorArray, EmptyTangentArray, false);
			UE_LOG(LogTemp, Display, TEXT("Hightlight Procedural Meshe Successfully Created X:%f"), 
				HighlightProceduralMeshes[Amount]->GetComponentLocation().X);
		}
	}
	*/
	
}

bool AGridSystem::IsTileValid(int32 Row, int32 Column)
{
	if (Row >= 0 && Row < GridRowAmount && Column >= 0 && Column < GridColumnAmount)
		return true;
	else
		return false;
}

void AGridSystem::SetHighlightedTiles(const TArray<int32>& HighlightedRow, const TArray<int32>& HighlightedColumn, const TArray<FColor>& HighlightColor)
{


}

void AGridSystem::CreateLine(FVector Start, FVector End, float Thickness, TArray<FVector>& OutVertices, TArray<int32>& OutTriangles)
{
	float lHalfThickness = Thickness / 2;
	FVector lThicknessDirection = FVector::CrossProduct((End - Start).GetSafeNormal(), FVector(0, 0, 1)/*Up Vector*/);

	TArray<int32> lVertexOrderForTriangle = { 2,1,0 /*End Of The First Triangle For A Sqaure*/, 2,3,1 /*End Of The Second Triangle For A Sqaure*/};

	TArray<int32> lNewTriangles;
	for (int32 i = 0; i < 6; i++)
	{
		lNewTriangles.Add(OutVertices.Num() + lVertexOrderForTriangle[i]);
	}
	OutTriangles.Append(lNewTriangles);
	lNewTriangles.Empty();

	FVector lVertexZero = Start + (lThicknessDirection * lHalfThickness); // Top Left Corner
	FVector lVertexOne = End + (lThicknessDirection * lHalfThickness); // Top Right Corner
	FVector lVertexTwo = Start - (lThicknessDirection * lHalfThickness); // Bottom Left Corner
	FVector lVertexThree = End - (lThicknessDirection * lHalfThickness); // Bottom Right Corner

	TArray<FVector> lNewVertices = { lVertexZero, lVertexOne, lVertexTwo, lVertexThree };
	OutVertices.Append(lNewVertices);
	lNewVertices.Empty();

}
