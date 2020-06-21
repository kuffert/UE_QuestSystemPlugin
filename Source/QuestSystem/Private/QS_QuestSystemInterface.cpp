// Fill out your copyright notice in the Description page of Project Settings.


#include "QS_QuestSystemInterface.h"
#include "Templates/SubclassOf.h"

// Add default functionality here for any IQS_QuestSystemInterface functions that are not pure virtual.

bool IQS_QuestSystemInterface::AcceptQuest(TSubclassOf<UQS_Quest> QuestSpec) {
	return false;
}

bool IQS_QuestSystemInterface::ProgressQuest(TSubclassOf<UQS_Quest> QuestSpec, FString QuestTag) {
	return false;
}
