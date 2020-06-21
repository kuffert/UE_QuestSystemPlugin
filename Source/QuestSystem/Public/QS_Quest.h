// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "QS_Quest.generated.h"

class UQS_QuestSystemComponent;
class UQS_Objective;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class QUESTSYSTEM_API UQS_Quest : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION()
	bool Init(UQS_QuestSystemComponent* QuestSystem);

	// public accessors/validators
	FString GetQuestDetails();

	virtual bool AttemptProgressQuest(FString QuestTag);

	virtual void ObjectiveCompleted(UQS_Objective* CompletedObjective);

private:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Quest Data", meta = (AllowPrivateAccess = "true"))
	FString QuestDescription;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Quest Objectives", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UQS_Objective>> ObjectiveSpecs;

	virtual TArray <TSubclassOf<UQS_Objective>> GetObjectiveSpecs();

	UPROPERTY()
		TArray<UQS_Objective*> Objectives;
	UPROPERTY()
		UQS_Objective* CurrentObjective;
	UPROPERTY()
		UQS_QuestSystemComponent* OwningQuestSystem;

	// private quest management functionality
	virtual bool AttemptProgressCurrentObjective(FString QuestTag);

	void UpdateCurrentObjective(int ObjectiveIndex);
};
