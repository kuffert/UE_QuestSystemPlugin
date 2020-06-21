// Fill out your copyright notice in the Description page of Project Settings.


#include "QS_Quest.h"
#include "QS_Objective.h"
#include "QS_QuestSystemComponent.h"

bool UQS_Quest::Init(UQS_QuestSystemComponent* QuestSystem)
{
	if (!QuestSystem) return false;
	OwningQuestSystem = QuestSystem;
	for (TSubclassOf<UQS_Objective> ObjectiveSpec : GetObjectiveSpecs())
	{
		UQS_Objective* NewObjective = NewObject<UQS_Objective>(QuestSystem, ObjectiveSpec);
		if (NewObjective) {
			NewObjective->Init(QuestSystem, this, EQS_ObjectiveType::PRIMARY);
			Objectives.AddUnique(NewObjective);
		}
	}
	UpdateCurrentObjective(0);
	return true;
}

FString UQS_Quest::GetQuestDetails()
{
	FString result = FString();
	result += QuestDescription;
	for (UQS_Objective* Objective : Objectives) {
		result += Objective->GetObjectiveDetails();
	}
	return result;
}

bool UQS_Quest::AttemptProgressQuest(FString QuestTag)
{
	return AttemptProgressCurrentObjective(QuestTag);
}

void UQS_Quest::ObjectiveCompleted(UQS_Objective * CompletedObjective)
{
	// Coooooool beans
}

TArray<TSubclassOf<UQS_Objective>> UQS_Quest::GetObjectiveSpecs()
{
	return ObjectiveSpecs;
}

bool UQS_Quest::AttemptProgressCurrentObjective(FString QuestTag)
{
	if (!CurrentObjective) return false;
	return CurrentObjective->AttemptProgressObjective(QuestTag);
}

void UQS_Quest::UpdateCurrentObjective(int ObjectiveIndex)
{
	if (Objectives.Num() > 0 && ObjectiveIndex >= 0 && ObjectiveIndex < Objectives.Num()) {
		CurrentObjective = Objectives[ObjectiveIndex];
	}
}
