// Fill out your copyright notice in the Description page of Project Settings.


#include "QS_Objective.h"
#include "QS_Requirements.h"
#include "QS_Quest.h"
#include "QS_QuestSystemComponent.h"

bool UQS_Objective::Init(UQS_QuestSystemComponent* QuestSystem, UQS_Quest * Quest, EQS_ObjectiveType Type)
{
	if (!QuestSystem || !Quest) return false;
	ObjectiveType = Type;
	OwningQuestSystem = QuestSystem;
	OwningQuest = Quest;
	Requirements = NewObject<UQS_Requirements>();
	Requirements->Init(GetObjectiveRequirements());
	RequirementsMet = NewObject<UQS_Requirements>();
	RequirementsMet->Init();
	for (TSubclassOf<UQS_Objective> SubObjectiveSpec : GetSubObjectiveSpecs())
	{
		UQS_Objective* NewSubObjective = NewObject<UQS_Objective>(QuestSystem, SubObjectiveSpec);
		if (NewSubObjective) {
			NewSubObjective->Init(QuestSystem, Quest, EQS_ObjectiveType::SUB);
			SubObjectives.AddUnique(NewSubObjective);
		}
	}
	return true;
}

FString UQS_Objective::GetObjectiveDetails()
{
	FString result = FString();
	result += ObjectiveDescription;
	for (UQS_Objective* SubObjective : SubObjectives) {
		result += SubObjective->GetObjectiveDetails();
	}
	return result;
}

FQS_RequirementsInitializer UQS_Objective::GetObjectiveRequirements()
{
	return ObjectiveRequirements;
}

bool UQS_Objective::AttemptProgressObjective(FString QuestTag)
{
	bool result = HasSubObjectives() ? AttemptProgressSubObjectives(QuestTag) : ProgressObjective(QuestTag);
	if (IsObjectiveComplete()) ObjectiveCompleted();
	return result;
}

bool UQS_Objective::HasSubObjectives()
{
	return SubObjectives.Num() > 0;
}

bool UQS_Objective::IsPrimaryObjective()
{
	return ObjectiveType == EQS_ObjectiveType::PRIMARY;
}

bool UQS_Objective::IsSubObjective()
{
	return ObjectiveType == EQS_ObjectiveType::SUB;
}

TArray<TSubclassOf<UQS_Objective>> UQS_Objective::GetSubObjectiveSpecs()
{
	return SubObjectiveSpecs;
}

bool UQS_Objective::AttemptProgressSubObjectives(FString QuestTag)
{
	bool result = false;
	for (UQS_Objective* SubObjective : SubObjectives) {
		result = result || SubObjective->ProgressObjective(QuestTag);
	}
	return result;
}

bool UQS_Objective::ProgressObjective(FString QuestTag)
{
	if (Requirements->HasRequirement(QuestTag)) {
		RequirementsMet->AddRequirement(QuestTag);
		return true;
	}
	return false;
}

bool UQS_Objective::IsObjectiveComplete()
{
	return Requirements->AreMet(RequirementsMet) && AreSubObjectivesComplete();
}

bool UQS_Objective::AreSubObjectivesComplete()
{
	bool result = true;
	for (UQS_Objective* SubObjective : SubObjectives) {
		result = result && SubObjective->IsObjectiveComplete();
	}
	return result;
}

void UQS_Objective::ObjectiveCompleted()
{
	if (IsPrimaryObjective() && OwningQuest) OwningQuest->ObjectiveCompleted(this);
}
