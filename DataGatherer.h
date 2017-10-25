// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Components/ActorComponent.h"
#include "DataGatherer.generated.h"


// Data structure that will be fetched several times.
USTRUCT(BlueprintType)
struct FDataStruct {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		FString name;

	UPROPERTY(BlueprintReadWrite)
		TArray<int32> xArray = {};
	UPROPERTY(BlueprintReadWrite)
		TArray<int32> yArray = {};

	UPROPERTY(BlueprintReadWrite)
		TArray<float> values;
};

// Struct that will envelope the data package.
USTRUCT(BlueprintType)
struct FJsonStruct {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		FString cmd;

	UPROPERTY(BlueprintReadWrite)
		FString sessionName;

	UPROPERTY(BlueprintReadWrite)
		TArray<FDataStruct> dataArray;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLETREALM_API UDataGatherer : public UActorComponent
{
	GENERATED_BODY()

		FJsonStruct packageStruct = FJsonStruct();

public:
	UPROPERTY(EditAnywhere, BlueprintreadWrite)
		int32 gridColumns = 100;

	UPROPERTY(EditAnywhere, BlueprintreadWrite)
		int32 gridRows = 100;

	UPROPERTY(EditAnywhere, BlueprintreadWrite)
		float gridGran = 100;

	UPROPERTY(EditAnywhere, BlueprintreadWrite)
		TArray<float> dataArray;

	// Sets default values for this component's properties
	UDataGatherer();

public:

	UFUNCTION(BlueprintCallable)
		void UpdateData(FVector playerPos, FVector otherPos);

	UFUNCTION(BlueprintCallable)
		FString GetValues();

	UFUNCTION(BlueprintCallable)
		void MakeJson();

private:

	void CreateDataStruct();
};
