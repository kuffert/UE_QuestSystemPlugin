#pragma once

#include "QS_QuestSystemComponent.h"
#include "QS_QuestMocks.h"
#include "QS_QuestSystemComponentMocks.generated.h"

UCLASS()
class UQS_QuestSystemComponentMockBase : public UQS_QuestSystemComponent
{
	GENERATED_BODY()

public:
	virtual void Setup() {};
};

UCLASS()
class UQS_QuestSystemComponentEmptyMock : public UQS_QuestSystemComponentMockBase
{
	GENERATED_BODY()

private:
		TArray<UQS_Quest*> Quests = TArray<UQS_Quest*>();
		UQS_Quest* ActiveQuest = nullptr;
};

UCLASS()
class UQS_QuestSystemComponentOneQuestMock : public UQS_QuestSystemComponentMockBase
{
	GENERATED_BODY()

public:
	virtual void Setup() override {
		AcceptQuest(UQS_BasicQuestMock::StaticClass());
	}

private:
	TArray<UQS_Quest*> Quests = TArray<UQS_Quest*>();
	UQS_Quest* ActiveQuest = nullptr;

};