// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QS_FunctionLibrary.generated.h"

class UQS_QuestSystemComponent;
class IQS_QuesterInterface;
class UQS_Quest;

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQS_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Attempts to have an Actor accept a quest. Actor must have a QuestSystemComponent, and implement the Quester Interface.
	UFUNCTION(BlueprintCallable, Category = "Quest System")
	static bool AcceptQuest(AActor* Actor, TSubclassOf<UQS_Quest> QuestSpec);

	// Attempts to progress quests for the given Actor. Actor must have a QuestSystemComponent, and implement the Quester Interface.
	UFUNCTION(BlueprintCallable, Category = "Quest System")
	static bool ProgressQuest(AActor* Actor, TSubclassOf<UQS_Quest> QuestSpec, FString QuestTag);

private:
	static UQS_QuestSystemComponent* GetActorQuestSystemComponent(AActor* Actor);
	static IQS_QuesterInterface* GetActorAsQuesterActor(AActor* Actor);
};
