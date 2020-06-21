#pragma once

#include "QS_Quest.h"
#include "QS_ObjectiveMocks.h"
#include "QS_QuestMocks.generated.h"

UCLASS()
class UQS_QuestMockBase : public UQS_Quest {

	GENERATED_BODY()

};

UCLASS()
class UQS_BasicQuestMock : public UQS_QuestMockBase {
	
	GENERATED_BODY()

public:

	int CompletedObjectives = 0;

	FString QuestDescription = "Basic Quest Description.";

	virtual TArray <TSubclassOf<UQS_Objective>> GetObjectiveSpecs() override
	{
		TArray<TSubclassOf<UQS_Objective>> MockObjectives = TArray<TSubclassOf<UQS_Objective>>();
		MockObjectives.AddUnique(UQS_BasicObjectiveMock::StaticClass());
		return MockObjectives;
	}

	virtual void ObjectiveCompleted(UQS_Objective* CompletedObjective) override {
		CompletedObjectives++;
		Super::ObjectiveCompleted(CompletedObjective);
	}

};