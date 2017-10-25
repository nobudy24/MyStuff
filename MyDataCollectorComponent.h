//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
//#include "MyDataCollectorComponent.generated.h"
//
//// Data structure that will be fetched several times.
//USTRUCT(BlueprintType)
//struct FDataStruct {
//	GENERATED_BODY()
//
//	UPROPERTY(BlueprintReadWrite)
//		FString name;
//	UPROPERTY(BlueprintReadWrite)
//		TArray<int32> xArray = {};
//	UPROPERTY(BlueprintReadWrite)
//		TArray<int32> yArray = {};
//	UPROPERTY(BlueprintReadWrite)
//		TArray<float> values;
//};
//
//// Struct that will envelope the data package.
//USTRUCT(BlueprintType)
//struct FJsonStruct {
//	GENERATED_BODY()
//
//	UPROPERTY(BlueprintReadWrite)
//		FString cmd;
//
//	UPROPERTY(BlueprintReadWrite)
//		FString sessionName;
//
//	UPROPERTY(BlueprintReadWrite)
//		TArray<FDataStruct> myDataArray;
//};
//
//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
//class BULLETREALM_API UMyDataCollectorComponent : public UActorComponent
//{
//	GENERATED_BODY()
//
//	FJsonStruct packageStruct = FJsonStruct();
//
//
//public:
//	//the location of the player 
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Analytics)
//		FVector PlayerLoc;
//	//the Time it takes to Track Data
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Analytics)
//		float Interval;
//	
//
//	//the number of columns
//	UPROPERTY(EditAnywhere, BlueprintreadWrite, Category = Analytics)
//		int32 arrayColumns = 100;
//	//the number of rows
//	UPROPERTY(EditAnywhere, BlueprintreadWrite, Category = Analytics)
//		int32 arrayRows = 100;
//	//the grid granularity
//	UPROPERTY(EditAnywhere, BlueprintreadWrite, Category = Analytics)
//		float gridGran = 100;
//	//the array we use to store data
//	UPROPERTY(BlueprintReadWrite)
//		TArray<float> myDataArray;
//	// Sets default values for this component's properties
//	UMyDataCollectorComponent();
//
//
//public:
//	//Create a timer handle to handle timing related functions
//	void onTimerEnd();
//	// will track the location of the character eact frame
//	void TrackData();
//
//	UFUNCTION(BlueprintCallable)
//		void UpdateData(FVector playerPos, FVector otherPos);
//
//	UFUNCTION(BlueprintCallable)
//		FString GetValues();
//
//	UFUNCTION(BlueprintCallable)
//		void MakeJson();
//
//private:
//	
//	FTimerHandle _loopTimerHandle;
//	void CreateDataStruct();
//};