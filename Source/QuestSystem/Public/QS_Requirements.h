// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QS_Requirements.generated.h"

USTRUCT(Blueprintable)
struct FQS_RequirementsInitializer {
	
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FString> Tags;

	FQS_RequirementsInitializer() {
		Tags = TArray<FString>();
	}

	FQS_RequirementsInitializer(TArray<FString> RequirementTags) {
		Tags = RequirementTags;
	}

};

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQS_Requirements : public UObject
{
	GENERATED_BODY()

public:

	void Init();
	void Init(FQS_RequirementsInitializer RequirementsInitializer);

	bool AreMet(UQS_Requirements* OtherRequirements);

	bool HasRequirement(FString Requirement);

	bool AddRequirement(FString Requirement);

	TArray<FString> GetRequirements();

private:
	UPROPERTY()
	TArray<FString> Tags;
	
};
