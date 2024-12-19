// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_Game_Function_Library.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Containers/Array.h"
#include "Misc/DateTime.h"
#include "HAL/PlatformFileManager.h"
#include "Kismet/KismetMathLibrary.h"

FFileHelper::EEncodingOptions UFPS_Game_Function_Library::DefaultEncoding = FFileHelper::EEncodingOptions::ForceAnsi;

bool UFPS_Game_Function_Library::SaveTxt(FString SessionID, FString LevelID, FString CoordXYZ, FString Angle, FString Time, bool ClearBuffer)
{
	static int frameCount;
	FString FileNameCoord;
	FString FileNameAngle;
	FString FileNameTS;

	static TArray<FString> CoordXYZArray;
	static TArray<FString> AngleArray;
	static TArray<FString> TimeStamp;

	//static FString LevelIDPrev;
	//auto t = FDateTime.UtcNow();

	//FDateTime time;
	//FDateTime timeUtc = time.UtcNow();
	//FString timeStr = time.UtcNow().ToString();

	if (ClearBuffer)
	{

		CoordXYZArray.Empty();
		AngleArray.Empty();
		TimeStamp.Empty();
	}

	frameCount++;

	CoordXYZArray.Add(CoordXYZ);
	AngleArray.Add(Angle);
	TimeStamp.Add(Time);

	FileNameCoord = "trackingData/" + SessionID + "_" + LevelID + "_Coord.csv";
	FileNameAngle = "trackingData/" + SessionID + "_" + LevelID + "_Angle.csv";
	FileNameTS = "trackingData/" + SessionID + "_" + LevelID + "_TS.csv";

	// Always first check if the file that you want to manipulate exist.
	//FPaths path;
	//path.Combine(FPaths::ProjectDir(), "trackingData", tsStr);

	bool res = FFileHelper::SaveStringArrayToFile(AngleArray, *(FPaths::ProjectDir() + FileNameAngle));
	res = FFileHelper::SaveStringArrayToFile(TimeStamp, *(FPaths::ProjectDir() + FileNameTS));
	return FFileHelper::SaveStringArrayToFile(CoordXYZArray, *(FPaths::ProjectDir() + FileNameCoord));


}

void UFPS_Game_Function_Library::WriteLineToCSV(FString line, FString dir, FString outputFileName, bool ClearBuffer)
{
	//This could suffice for the save location
	//UE_LOG(LogTemp, Log, TEXT("This would be the default save Location, not saving here right now %s"), (*(FPaths::GameDir() + outputFileName)));
	FString SaveDirectory = dir;
	FString FileName = outputFileName;
	//char* lineChar = TCHAR_TO_ANSI(*line);
	//strcat(lineChar, ", \n");
	
	// YPat: this is not working
	//if (ClearBuffer)
	//{
	//	line.Reset();
	//}

	line.Append(", \n");
	//FString TextToSave = FString(lineChar);

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.CreateDirectoryTree(*SaveDirectory))
	{
		if (ClearBuffer) {

			FString AbsoluteFilePath = SaveDirectory + "/" + FileName;
			printf(TCHAR_TO_ANSI(*AbsoluteFilePath));
			//UE_LOG(LogTemp, Log, TEXT("This is the save Location, being used for the write operation %s"), *AbsoluteFilePath);
			FFileHelper::SaveStringToFile(line, *AbsoluteFilePath, DefaultEncoding, &IFileManager::Get(), EFileWrite::FILEWRITE_NoFail);
		}
		else {

			FString AbsoluteFilePath = SaveDirectory + "/" + FileName;
			printf(TCHAR_TO_ANSI(*AbsoluteFilePath));
			//UE_LOG(LogTemp, Log, TEXT("This is the save Location, being used for the write operation %s"), *AbsoluteFilePath);
			FFileHelper::SaveStringToFile(line, *AbsoluteFilePath, DefaultEncoding, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
		}


	}
}

FString UFPS_Game_Function_Library::readFileToString(FString dir, FString outputFileName) {
	FString SaveDirectory = dir;
	FString FileName = outputFileName;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString existing;
	if (PlatformFile.CreateDirectoryTree(*SaveDirectory))
	{
		FString AbsoluteFilePath = SaveDirectory + "/" + FileName;
		printf(TCHAR_TO_ANSI(*AbsoluteFilePath));
		FFileHelper::LoadFileToString(existing, *AbsoluteFilePath, FFileHelper::EHashOptions::None);
	}
	return existing;
}

bool UFPS_Game_Function_Library::CSVExists(FString dir, FString outputFileName)
{
	FString SaveDirectory = dir;
	FString FileName = outputFileName;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString existing;
	if (PlatformFile.CreateDirectoryTree(*SaveDirectory))
	{
		FString AbsoluteFilePath = SaveDirectory + "/" + FileName;
		printf(TCHAR_TO_ANSI(*AbsoluteFilePath));
		FFileHelper::LoadFileToString(existing, *AbsoluteFilePath, FFileHelper::EHashOptions::None);
	}
	if (existing.Compare("") == 0) {
		//file is empty or did not previously exist
		return false;
	}
	return true;
}

void UFPS_Game_Function_Library::insertAtCSV(FString line, FString dir, FString outputFileName, int32 row, int32 column)
{
	FString file = readFileToString(dir, outputFileName);
	int counter = 0;
	int r = row;
	int c = column;
	//Get correct row by stepping through the file and counting \n (\n indicates new row in CSV format)
	while (r > 0 && counter < file.Len()) {

		if (file[counter] == '\n') {
			r--;
			counter++;
		}
		counter++;
	}
	//Insert extra \n if needed
	for (int i = 0; i < r; i++) {
		file.InsertAt(counter++, ", \n");
	}

	//Get correct column by stepping through the file and counting ',' (this indicates a new column in CSV format)
	while (c > 0 && counter < file.Len() && file[counter + 1] != '\n') {
		if (file[counter] == ',') {
			c--;
		}
		counter++;
	}
	for (int i = 0; i < c; i++) {
		file.InsertAt(counter++, ',');
	}
	//UE_LOG(LogTemp, Warning, TEXT("!!!!!!!!_____%d_____!!!!!!!!"), counter);
	//line.Append(",");
	file.InsertAt(counter, line);
	counter += line.Len();
	while (file[counter] == ' ') {
		counter++;
	}
	if (file[counter] != ',') {
		file.InsertAt(counter, ',');
	}
	UE_LOG(LogTemp, Log, TEXT("This was written to file:\n %s"), *file);
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.CreateDirectoryTree(*dir))
	{
		FString AbsoluteFilePath = dir + "/" + outputFileName;
		printf(TCHAR_TO_ANSI(*AbsoluteFilePath));
		FFileHelper::SaveStringToFile(file, *AbsoluteFilePath, DefaultEncoding, &IFileManager::Get(), EFileWrite::FILEWRITE_AllowRead);
	}

}

int32 UFPS_Game_Function_Library::getLastRow(FString dir, FString outputFileName)
{
	FString file = readFileToString(dir, outputFileName);
	int counter = 0;
	for (int i = 0; i < file.Len(); i++) {
		if (file[i] == '\n') {
			counter++;
		}
	}
	return counter;
}

TArray<FVector> SimplifySpline(TArray<FVector> points, float epsilon) {
	//Using the 'Ramer–Douglas–Peucker' algorithm to simplify a list of line segments
	int32 size = points.Num();
	if (points.Num() == 0) {
		return points;
	}
	//Find point with max distance
	float dmax = 0;
	int32 index = 0;
	int32 end = points.Num();
	for (int i = 1; i < end - 1; i++) {
		float d = UKismetMathLibrary::GetPointDistanceToLine(points[i], points[0], UKismetMathLibrary::GetDirectionUnitVector(points[1], points[end - 1]));
		if (d > dmax) {
			index = i;
			dmax = d;
		}
	}
	TArray<FVector> result;
	// If max distance is greater than epsilon, recursively simplify

	if (dmax > epsilon) {
		TArray<FVector> left;
		TArray<FVector> right;
		for (int i = 0; i < end; i++) {
			if (i <= index) {
				left.Add(points[i]);
			}
			if (i >= index) {
				right.Add(points[i]);
			}
		}
		//Recursive call
		TArray<FVector> recResults1 = SimplifySpline(left, epsilon);
		TArray<FVector> recResults2 = SimplifySpline(right, epsilon);
		if (recResults1.Num() == 0) {
			result = recResults2;
		}
		else {
			recResults1.Append(recResults2);
			result = recResults1;
		}
	}
	else if (points.IsValidIndex(0) && points.IsValidIndex(end - 1)) {
		result = { points[0], points[end - 1] };
	}
	else {
		return points;
	}

	return result;
}

TArray<FVector> UFPS_Game_Function_Library::getProximityCoordList(FString dir, FString fileName, FString xColHeader, FString yColHeader)
{
	FString file = readFileToString(dir, fileName);
	int counter = 0;
	int32 xCol = -1;
	int32 yCol = -1;
	TArray<FVector> vectors;
	TArray<FString> rows;
	file.ParseIntoArrayLines(rows);
	TArray<FString> columns;

	rows[0].ParseIntoArray(columns, TEXT(","), true);
	for (int j = 0; j < columns.Num(); j++) {
		FString cmp = columns[j].TrimStartAndEnd();
		if (cmp.Equals(xColHeader)) {
			xCol = j;
		}
		if (cmp.Equals(yColHeader)) {
			yCol = j;
		}
	}
	if (xCol != -1 && yCol != -1) {
		for (int i = 1; i < rows.Num(); i++) {
			int len = rows[i].ParseIntoArray(columns, TEXT(","), true);
			if (xCol < len && yCol < len) {
				vectors.Add(FVector(FCString::Atof(*columns[xCol]), FCString::Atof(*columns[yCol]), 10));
			}
		}
		vectors = SimplifySpline(vectors, 0.5);
	}

	return vectors;
}