//// Fill out your copyright notice in the Description page of Project Settings.
//
//#include "MyDataCollectorComponent.h"
//#include "JsonObject.h"
//#include "JsonPrintPolicy.h"
//#include "JsonWriter.h"
//#include "JsonSerializer.h"
//#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h" 
//#include "Engine.h"
//
//// Sets default values for this component's properties
//UMyDataCollectorComponent::UMyDataCollectorComponent()
//{
//	//PlayerLoc = FVector(0, 0, 0);
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//	//Interval = 1.0f;
//	myDataArray.AddZeroed(arrayRows * arrayColumns);
//
//	// ...
//}
//
//
////// Called when the game starts
////void UMyDataCollectorComponent::BeginPlay()
////{
////	Super::BeginPlay();
////	GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, this, &UMyDataCollectorComponent::onTimerEnd, Interval, false);
////	//...
////
////}
//
//void UMyDataCollectorComponent::UpdateData(FVector playerPos, FVector otherPos)
//{
//	FVector playerDelta = playerPos - otherPos;
//
//	// Gets the player position inside the data array as an index position.
//	int32 i = (int32)(playerDelta.X / gridGran);
//	int32 j = (int32)(playerDelta.Y / gridGran);
//
//	// Sets a value using a conventional array as a bidimentional one.
//	myDataArray[i * arrayRows + j] += 1.0;
//}
// 
////
////void UMyDataCollectorComponent::TrackData()
////{
////	ACharacter* myCharacterLocationPtr = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
////
////	//Deans way
////	PlayerLoc.X = myCharacterLocationPtr->GetActorLocation().X;
////	PlayerLoc.Y = myCharacterLocationPtr->GetActorLocation().Y;
////
////	float IntXVal = PlayerLoc.X;
////	float IntYVal = PlayerLoc.Y;
////
////	int32 XVal = (int32)IntXVal;
////	int32 YVal = (int32)IntYVal;
////
////	FString ThePlayerLocVal = FString::Printf(TEXT("the value of playerLocation is ,X:%d,Y:%d"), XVal, YVal);
////	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Yellow, *ThePlayerLocVal);
////
////	//Interwebs way
////	//GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Red, *myCharacterLocationPtr->GetActorLocation().ToString());
////
////	//set Timer again
////	myDataArray[i*ArrayRow + j] += 1.0;
////	GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, this, &UMyDataCollectorComponent::onTimerEnd, Interval, false);
////}
//
//
//// Creates a temporary data struct variable and sets its parameters.
//// Then, it stores it inside the package array.
//void UMyDataCollectorComponent::CreateDataStruct()
//{
//	FDataStruct tmp = FDataStruct();
//	tmp.name = "Pos";
//	for (int32 i = 0; i < arrayRows; ++i) {
//		for (int32 j = 0; j < arrayColumns; ++j) {
//			// It stores only indices with values greater than 0.
//			if (myDataArray[i * arrayRows + j] > 0.0) {
//				tmp.xArray.Add(i);
//				tmp.yArray.Add(j);
//
//				tmp.values.Add(myDataArray[i * arrayRows + j]);
//				myDataArray[i * arrayRows + j] = 0.0;
//			}
//		}
//	}
//	packageStruct.myDataArray.Add(tmp);
//}
//
//
//// Prints the array values that are not 0.
//FString UMyDataCollectorComponent::GetValues()
//{
//	FString str = "";
//	for (int32 i = 0; i < arrayRows; ++i) {
//		for (int32 j = 0; j < arrayColumns; ++j) {
//			if (myDataArray[i * arrayRows + j] > 0.0)
//				str += FString::FromInt(i) + " , " + FString::FromInt(j) + " = " + FString::SanitizeFloat(myDataArray[i * arrayRows + j]) + " --- ";
//		}
//	}
//
//	return str;
//}
////
////void UMyDataCollectorComponent::onTimerEnd()
////{
////	//Do many things here
////	TrackData();
////
////}
//
//void UMyDataCollectorComponent::MakeJson() {
//	// Create a json object and convert the given stuct into a serializable object.
//	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
//
//	// Set the command package and convert it into a JsonObject to serialize it.
//	packageStruct.cmd = "save";
//	packageStruct.sessionName = "Session1";
//
//	CreateDataStruct();
//
//	//JsonObject = FJsonObjectConverter::UStructToJsonObject<FJsonStruct>(packageStruct);
//	
//
//	// Clear the structs data array for storing new data as a new package.
//	packageStruct.myDataArray.Empty();
//
//	// Create a string will get our formated data.
//	FString OutputString;
//
//	// Serialize the json object with our data into a Json structure.
//	TSharedRef< TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> > JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutputString);
//	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
//
//	// Gets the current date and time to create an unique file name.
//	FDateTime date = FDateTime().Now();
//
//	// Create a file with the given string in the project directory folder. 
//	// It will be as unique as possible to avoid overwriting.
//	FFileHelper::SaveStringToFile(OutputString, *(FPaths::GameDir() + "Json\\session-" + FPlatformMisc::GetLoginId() + date.ToString() + ".json"));
//}