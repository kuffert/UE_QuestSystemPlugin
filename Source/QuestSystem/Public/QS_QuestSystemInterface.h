// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QS_QuestSystemInterface.generated.h"

class UQS_Quest;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQS_QuestSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class QUESTSYSTEM_API IQS_QuestSystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool AcceptQuest(TSubclassOf<UQS_Quest> QuestSpec);
	virtual bool ProgressQuest(TSubclassOf<UQS_Quest> QuestSpec, FString QuestTag);
};
