// Fill out your copyright notice in the Description page of Project Settings.


#include "QS_QuestSystemComponent.h"
#include "QS_Quest.h"

// Sets default values for this component's properties
UQS_QuestSystemComponent::UQS_QuestSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQS_QuestSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQS_QuestSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Quest System Interface overrides
bool UQS_QuestSystemComponent::AcceptQuest(TSubclassOf<UQS_Quest> QuestSpec)
{
	if (HasQuest(QuestSpec)) return false;

	UQS_Quest* newQuest = NewObject<UQS_Quest>(this, QuestSpec);
	if (!newQuest) return false;

	bool InitializeResult = newQuest->Init(this);
	if (!InitializeResult) return false;

	bool AddQuestResult = AddNewQuest(newQuest);
	if (!AddQuestResult) return false;
	
	bool UpdateActiveQuestResult = UpdateActiveQuest(newQuest);
	return InitializeResult && AddQuestResult && UpdateActiveQuestResult;
}

bool UQS_QuestSystemComponent::ProgressQuest(TSubclassOf<UQS_Quest> QuestSpec, FString QuestTag)
{
	return AttemptProgressQuestBySpec(QuestSpec, QuestTag);
}

bool UQS_QuestSystemComponent::AttemptProgressAllQuests(FString QuestTag)
{
	bool result = false;
	for (UQS_Quest* Quest : Quests) {
		result = Quest->AttemptProgressQuest(QuestTag) || result;
	}
	return result;
}

UQS_Quest* UQS_QuestSystemComponent::GetQuestBySpec(TSubclassOf<UQS_Quest> QuestSpec)
{
	for (UQS_Quest* Quest : Quests) {
		if (Quest->IsA(QuestSpec)) {
			return Quest;
		}
	}
	return nullptr;
}

// Public accessors/validators

bool UQS_QuestSystemComponent::HasQuest(TSubclassOf<UQS_Quest> QuestSpec)
{
	return GetQuestBySpec(QuestSpec);
}

FString UQS_QuestSystemComponent::GetActiveQuestDetails()
{
	return ActiveQuest? ActiveQuest->GetQuestDetails() : FString(TEXT("No active quest."));
}

bool UQS_QuestSystemComponent::HasActiveQuest()
{
	return ActiveQuest;
}

int UQS_QuestSystemComponent::GetQuestCount()
{
	return Quests.Num();
}



// private quest management functionality
bool UQS_QuestSystemComponent::AddNewQuest(UQS_Quest * NewQuest)
{
	return Quests.AddUnique(NewQuest) >= 0;
}

bool UQS_QuestSystemComponent::UpdateActiveQuest(UQS_Quest * NewActiveQuest)
{
	ActiveQuest = NewActiveQuest;
	return true;
}

bool UQS_QuestSystemComponent::AttemptProgressQuestBySpec(TSubclassOf<UQS_Quest> QuestSpec, FString QuestTag)
{
	UQS_Quest* Quest = GetQuestBySpec(QuestSpec);
	if (Quest) {
		return Quest->AttemptProgressQuest(QuestTag);
	}
	return false;
}

