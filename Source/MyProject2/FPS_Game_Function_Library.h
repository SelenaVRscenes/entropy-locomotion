// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FPS_Game_Function_Library.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UFPS_Game_Function_Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:


	UFUNCTION(BlueprintCallable, Category = "FPS Game CPP Nodes", meta = (Keywords = "Save Text File"))
		static bool SaveTxt(FString SessionID, FString LevelID, FString CoordXYZ, FString Angle, FString Time, bool ClearBuffer);
	UFUNCTION(BlueprintCallable, Category = "Default")
		static void WriteLineToCSV(FString line, FString dir, FString outputFileName, bool ClearBuffer);
	UFUNCTION(BlueprintCallable, Category = "Default")
		static bool CSVExists(FString dir, FString outputFileName);
	UFUNCTION(BlueprintCallable, Category = "Default")
		static void insertAtCSV(FString line, FString dir, FString outputFileName, int32 row, int32 column);
	UFUNCTION(BlueprintCallable, Category = "Default")
		static int32 getLastRow(FString dir, FString outputFileName);
	UFUNCTION(BlueprintCallable, Category = "Default")
		static TArray<FVector> getProximityCoordList(FString dir, FString fileName, FString xColHeader, FString yColHeader);
	UFUNCTION(BlueprintCallable, Category = "Default")
		static FString readFileToString(FString dir, FString outputFileName);

private:
	static FFileHelper::EEncodingOptions DefaultEncoding;
};
