// Fill out your copyright notice in the Description page of Project Settings.


#include "QS_Requirements.h"

void UQS_Requirements::Init() {
	Tags = TArray<FString>();
}

void UQS_Requirements::Init(FQS_RequirementsInitializer RequirementsInitializer) {
	Tags = RequirementsInitializer.Tags;
}

bool UQS_Requirements::AreMet(UQS_Requirements* OtherRequirements)
{
	bool result = true;
	for (FString Requirement : OtherRequirements->GetRequirements()) {
		result = result && HasRequirement(Requirement);
	}
	return result;
}

bool UQS_Requirements::HasRequirement(FString Requirement)
{
	for (FString Tag : Tags) {
		if (Tag == Requirement) return true;
	}
	return false;
}

bool UQS_Requirements::AddRequirement(FString Requirement)
{
	return Tags.AddUnique(Requirement);
}

TArray<FString> UQS_Requirements::GetRequirements()
{
	return Tags;
}
