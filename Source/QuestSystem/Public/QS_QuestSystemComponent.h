// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QS_QuestSystemInterface.h"
#include "QS_QuestSystemComponent.generated.h"

class UQS_Quest;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UQS_QuestSystemComponent : public UActorComponent, public IQS_QuestSystemInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQS_QuestSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// IQS_QuestSystemInterface overrides
	virtual bool AcceptQuest(TSubclassOf<UQS_Quest> QuestSpec) override;
	virtual bool ProgressQuest(TSubclassOf<UQS_Quest> QuestSpec, FString QuestTag) override;


	// public accessors/validators
	
	UQS_Quest* GetQuestBySpec(TSubclassOf<UQS_Quest> QuestSpec);

	UFUNCTION(BlueprintPure, Category = "Accessors")
	virtual bool HasQuest(TSubclassOf<UQS_Quest> QuestSpec);

	UFUNCTION(BlueprintPure, Category = "Accessors")
	virtual FString GetActiveQuestDetails();

	UFUNCTION(BlueprintPure, Category = "Accessors")
	virtual bool HasActiveQuest();

	UFUNCTION(BlueprintPure, Category = "Accessors")
	virtual int GetQuestCount();

private:
	UPROPERTY()
	TArray<UQS_Quest*> Quests;
	UPROPERTY()
	UQS_Quest* ActiveQuest;

	// quest management functionality
	bool AddNewQuest(UQS_Quest* NewQuest);
	bool UpdateActiveQuest(UQS_Quest* NewActiveQuest);
	bool AttemptProgressQuestBySpec(TSubclassOf<UQS_Quest> QuestSpec, FString QuestTag);
	bool AttemptProgressAllQuests(FString QuestTag);
		
};
