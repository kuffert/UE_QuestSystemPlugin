// Fill out your copyright notice in the Description page of Project Settings.


#include "QS_FunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "QS_QuesterInterface.h"

// public library functions

bool UQS_FunctionLibrary::AcceptQuest(AActor* Actor, TSubclassOf<UQS_Quest> QuestSpec) {
	UQS_QuestSystemComponent* QuestComponent = GetActorQuestSystemComponent(Actor);
	return QuestComponent->AcceptQuest(QuestSpec);
}

bool UQS_FunctionLibrary::ProgressQuest(AActor* Actor, TSubclassOf<UQS_Quest> QuestSpec, FString QuestTag) {
	UQS_QuestSystemComponent* QuestComponent = GetActorQuestSystemComponent(Actor);
	return QuestComponent->ProgressQuest(QuestSpec, QuestTag);
}


// Private helper functions

UQS_QuestSystemComponent* UQS_FunctionLibrary::GetActorQuestSystemComponent(AActor* Actor)
{
	IQS_QuesterInterface* QuesterActor = Cast<IQS_QuesterInterface>(Actor);
	if (QuesterActor) return QuesterActor->GetQuestSystemComponent();
	return nullptr;
}

IQS_QuesterInterface* UQS_FunctionLibrary::GetActorAsQuesterActor(AActor* Actor)
{
	return Cast<IQS_QuesterInterface>(Actor);
}
