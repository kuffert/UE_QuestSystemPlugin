#pragma once

#include "QS_Objective.h"
#include "QS_Requirements.h"
#include "QS_ObjectiveMocks.generated.h"

UCLASS()
class UQS_ObjectiveMockBase : public UQS_Objective
{
	GENERATED_BODY()

public:

	FQS_RequirementsInitializer GetObjectiveRequirements() override {
		TArray<FString> ReqTags = TArray<FString>();
		ReqTags.Add(FString(TEXT("TestRequirement_Primary")));
		return FQS_RequirementsInitializer(ReqTags);
	}

};

UCLASS()
class UQS_BasicObjectiveMock : public UQS_ObjectiveMockBase
{
	GENERATED_BODY()

public:
	FString ObjectiveDescription = "Basic Objective Description.";
};

UCLASS()
class UQS_BasicSubObjectiveMock : public UQS_ObjectiveMockBase
{
	GENERATED_BODY()

public:
	FString ObjectiveDescription = "Basic SubObjective Description.";

	FQS_RequirementsInitializer GetObjectiveRequirements() override {
		TArray<FString> ReqTags = TArray<FString>();
		ReqTags.Add(FString(TEXT("TestRequirement_Sub")));
		return FQS_RequirementsInitializer(ReqTags);
	}
};

UCLASS()
class UQS_ComplexObjectiveWithSubObjectiveMock : public UQS_ObjectiveMockBase
{
	GENERATED_BODY()

public:
	FString ObjectiveDescription = "Complex Objective With SubObjectives Description.";
	virtual TArray <TSubclassOf<UQS_Objective>> GetSubObjectiveSpecs() override 
	{
		TArray<TSubclassOf<UQS_Objective>> MockSubObjectives = TArray<TSubclassOf<UQS_Objective>>();
		MockSubObjectives.AddUnique(UQS_BasicSubObjectiveMock::StaticClass());
		return MockSubObjectives;
	}
};
