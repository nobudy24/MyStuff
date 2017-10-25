// Fill out your copyright notice in the Description page of Project Settings.

#include "DataGatherer.h"

// Json needed includes
#include "JsonObject.h"
#include "JsonPrintPolicy.h"
#include "JsonWriter.h"
#include "JsonSerializer.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h" 

// Sets default values for this component's properties
UDataGatherer::UDataGatherer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initializes the data array with 0 values.
	dataArray.AddZeroed(gridRows * gridColumns);
}

// Called every 0.1 seconds
void UDataGatherer::UpdateData(FVector playerPos, FVector otherPos)
{
	FVector playerDelta = playerPos - otherPos;

	// Gets the player position inside the data array as an index position.
	int32 i = (int32)(playerDelta.X / gridGran);
	int32 j = (int32)(playerDelta.Y / gridGran);

	// Sets a value using a conventional array as a bidimentional one.
	dataArray[i * gridRows + j] += 1.0;
}

// Creates a temporary data struct variable and sets its parameters.
// Then, it stores it inside the package array.
void UDataGatherer::CreateDataStruct()
{
	FDataStruct tmp = FDataStruct();
	tmp.name = "Pos";
	for (int32 i = 0; i < gridRows; ++i) {
		for (int32 j = 0; j < gridColumns; ++j) {
			// It stores only indices with values greater than 0.
			if (dataArray[i * gridRows + j] > 0.0) {
				tmp.xArray.Add(i);
				tmp.yArray.Add(j);

				tmp.values.Add(dataArray[i * gridRows + j]);
				dataArray[i * gridRows + j] = 0.0;
			}
		}
	}
	packageStruct.dataArray.Add(tmp);
}


// Prints the array values that are not 0.
FString UDataGatherer::GetValues()
{
	FString str = "";
	for (int32 i = 0; i < gridRows; ++i) {
		for (int32 j = 0; j < gridColumns; ++j) {
			if (dataArray[i * gridRows + j] > 0.0)
				str += FString::FromInt(i) + " , " + FString::FromInt(j) + " = " + FString::SanitizeFloat(dataArray[i * gridRows + j]) + " --- ";
		}
	}

	return str;
}

// Gets a struct and serializes it. After, makes a Json file in the project directory.
void UDataGatherer::MakeJson() {
	// Create a json object and convert the given stuct into a serializable object.
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	// Set the command package and convert it into a JsonObject to serialize it.
	packageStruct.cmd = "save";
	packageStruct.sessionName = "Session1";

	CreateDataStruct();

	JsonObject = FJsonObjectConverter::UStructToJsonObject<FJsonStruct>(packageStruct);

	// Clear the structs data array for storing new data as a new package.
	packageStruct.dataArray.Empty();

	// Create a string will get our formated data.
	FString OutputString;

	// Serialize the json object with our data into a Json structure.
	TSharedRef< TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> > JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	// Gets the current date and time to create an unique file name.
	FDateTime date = FDateTime().Now();

	// Create a file with the given string in the project directory folder. 
	// It will be as unique as possible to avoid overwriting.
	FFileHelper::SaveStringToFile(OutputString, *(FPaths::GameDir() + "Json\\session-" + FPlatformMisc::GetLoginId() + date.ToString() + ".json"));
}