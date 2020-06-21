// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "QS_Requirements.h"
#include "QS_Objective.generated.h"

class UQS_QuestSystemComponent;
class UQS_Quest;

UENUM()
enum class EQS_ObjectiveType : uint8 {
	PRIMARY UMETA(DisplayName = "Primary Objective"),
	SUB UMETA(DisplayName = "Sub Objective")
};

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class QUESTSYSTEM_API UQS_Objective : public UObject
{
	GENERATED_BODY()

public:

	bool Init(UQS_QuestSystemComponent* QuestSystem, UQS_Quest* Quest, EQS_ObjectiveType Type);

	virtual bool AttemptProgressObjective(FString QuestTag);

	// public accessors/validators
	bool IsPrimaryObjective();
	bool IsSubObjective();
	bool HasSubObjectives();
	FString GetObjectiveDetails();
	virtual FQS_RequirementsInitializer GetObjectiveRequirements();

private:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "SubOjbectives", meta = (AllowPrivateAccess = "true"))
		TArray <TSubclassOf<UQS_Objective>> SubObjectiveSpecs;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Objective Data", meta = (AllowPrivateAccess = "true"))
		FString ObjectiveDescription;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Objective Data", meta = (AllowPrivateAccess = "true"))
		FQS_RequirementsInitializer ObjectiveRequirements;


	virtual TArray <TSubclassOf<UQS_Objective>> GetSubObjectiveSpecs();

	UPROPERTY()
	EQS_ObjectiveType ObjectiveType;
	UPROPERTY()
		UQS_Requirements* Requirements;
	UPROPERTY()
		UQS_Requirements* RequirementsMet;
	UPROPERTY()
		TArray<UQS_Objective*> SubObjectives;
	UPROPERTY()
		UQS_QuestSystemComponent* OwningQuestSystem;
	UPROPERTY()
		UQS_Quest* OwningQuest;


	// private objective management functionality 

	bool AttemptProgressSubObjectives(FString QuestTag);

	bool ProgressObjective(FString QuestTag);

	bool IsObjectiveComplete();

	bool AreSubObjectivesComplete();

	void ObjectiveCompleted();

};
