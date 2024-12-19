// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "MoveRandomFileUpload.generated.h"

UCLASS()
class MYPROJECT2_API AMoveRandomFileUpload : public AActor
{
	GENERATED_BODY()
		UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

public:
	// Sets default values for this actor's properties
	AMoveRandomFileUpload();
	float cScale = 100.0f;
	float cCenter = -50.0f;
	int gDirection;
	TArray<uint8> RawFileData;
	//TArray<int> RawFileData;
	//FString FileName = "C:/Users/ypatotsk/Dev/UE5/data/zeroOne.txt"; // old
	FString FileName = "C:/Users/ypatotsk/Dev/UE5/data/sampleEntropy.txt";
	//FString FileName = "";
	TArray<float> posArr = { 0.1896760846376218, 0.095695595342932738, -0.053336587320889761,
	-0.090108181507233853,-0.089255153659802255, -0.027871651481178417,  -04.3256481152822068
	};
	int gCounter;
	int gIterationNum;
	TArray<float> CoordX;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
