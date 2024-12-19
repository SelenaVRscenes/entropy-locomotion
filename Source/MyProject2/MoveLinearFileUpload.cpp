

// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveLinearFileUpload.h"

// Sets default values
AMoveLinearFileUpload::AMoveLinearFileUpload()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/MotionExp/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

}

// Called when the game starts or when spawned
void AMoveLinearFileUpload::BeginPlay()
{
	Super::BeginPlay();
	int fileInfo = 0;
	gDirection = 1;
	gCounter = 0;

	FileName = "C:/Users/ypatotsk/Dev/UE5/data/linMotion_N=100.txt";
	//FileName = "/Game/Content/Files/sampleEntropy.txt";

	TArray<FString> take;
	FFileHelper::LoadANSITextFileToStrings(*FileName, NULL, take);

	FVector temp;

	for (int i = 0; i < take.Num(); i++)
	{
		//FString aString = take* ;
		FString aString = take[i];
		//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Blue, "Test:");
		//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Blue, "T:" + aString);

		float xFl = FCString::Atof(*aString);

		CoordX.Add(xFl);


	}
	UE_LOG(LogTemp, Warning, TEXT("Float array"));
	for (int i = 0; i < CoordX.Num(); i++) {
		float x = CoordX[i];
		//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Blue, FString::Printf(TEXT("YawDelta : %f"), x));
	}


	gIterationNum = CoordX.Num();

}

// Called every frame
void AMoveLinearFileUpload::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int lOffset = 10;
	int lPeriod = DeltaTime / lOffset;
	int lYOffset = 10;

	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();

	float DeltaHeight = gDirection * DeltaTime;

	if (gCounter >= gIterationNum - 1) {
		gDirection = -gDirection;
	};

	if ((gCounter <= 0) && (gDirection < 0)) {
		gDirection = 1;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Blue, FString::Printf(TEXT("ind : %i"), gCounter));

	//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Blue, FString::Printf(TEXT("size : %i"), gIterationNum));

	NewLocation.Y = CoordX[gCounter] * cScale + cCenter;
	SetActorLocationAndRotation(NewLocation, NewRotation);


	//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Blue, *TheFloatStr);



	//iteration
	gCounter += gDirection;

}
