// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QS_QuestSystemComponent.h"
#include "QS_QuesterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQS_QuesterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class QUESTSYSTEM_API IQS_QuesterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UQS_QuestSystemComponent* GetQuestSystemComponent();
};
