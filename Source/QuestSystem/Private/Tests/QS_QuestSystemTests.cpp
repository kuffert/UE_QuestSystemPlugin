#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Engine.h"
#include "EngineUtils.h"

// Quest System Classes
#include "QS_QuestSystemComponent.h"
#include "QS_Objective.h"
#include "QS_Quest.h"
#include "QS_FunctionLibrary.h"

// Quest System Basic Game Classes
#include "QS_QuesterGameMode.h"
#include "QS_QuesterCharacter.h"

// Quest System Mocks
#include "..\..\public\Tests\Mocks\QS_ObjectiveMocks.h"
#include "..\..\public\Tests\Mocks\QS_QuestMocks.h"
#include "..\..\public\Tests\Mocks\QS_QuestSystemComponentMocks.h"

#define QUESTSYSTEM_TESTLEVEL "/QuestSystem/TestContent/QuestSystem_TestLevel"

// Copy of the hidden method GetAnyGameWorld() in AutomationCommon.cpp.
// Marked as temporary there, hence, this one is temporary, too.
UWorld* GetTestWorld() {
	const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
	for (const FWorldContext& Context : WorldContexts) {
		if (((Context.WorldType == EWorldType::PIE) || (Context.WorldType == EWorldType::Game))
			&& (Context.World() != nullptr)) {
			return Context.World();
		}
	}
	return nullptr;
}

// -- Quest System Init Tests

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FQS_QuestSystem_TestInit, "QuestSystem.Init",
	EAutomationTestFlags::EditorContext |
	EAutomationTestFlags::ClientContext |
	EAutomationTestFlags::ProductFilter)

	bool FQS_QuestSystem_TestInit::RunTest(const FString& Parameters) {
	AutomationOpenMap(TEXT(QUESTSYSTEM_TESTLEVEL));

	UWorld* world = GetTestWorld();
	AQS_QuesterCharacter* QuesterCharacter = *TActorIterator<AQS_QuesterCharacter>(world);
	UQS_QuestSystemComponent* CharacterQuestSystemComponent = QuesterCharacter->GetQuestSystemComponent();

	TestTrue("Tests are using the proper game mode", world->GetAuthGameMode()->IsA<AQS_QuesterGameMode>());
	TestTrue("Quester character is spawned",		QuesterCharacter);
	TestTrue("Quester character has a quest system", CharacterQuestSystemComponent);

	return true;
}

// --

// -- Quest Acceptance Tests (Decoupled)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FQS_QuestSystem_TestAcceptQuest_Independent, "QuestSystem.Independent.AcceptQuest",
	EAutomationTestFlags::EditorContext |
	EAutomationTestFlags::ClientContext |
	EAutomationTestFlags::ProductFilter)

	bool FQS_QuestSystem_TestAcceptQuest_Independent::RunTest(const FString& Parameters) {
	AutomationOpenMap(TEXT(QUESTSYSTEM_TESTLEVEL));

	UQS_QuestSystemComponentMockBase* NewQuestSystemComponent = NewObject<UQS_QuestSystemComponentEmptyMock>();

	TestTrue("Quest System has 0 quests", NewQuestSystemComponent->GetQuestCount() == 0);
	bool AcceptQuestResult = NewQuestSystemComponent->AcceptQuest(UQS_BasicQuestMock::StaticClass());
	TestTrue("Quest System Successfuly Accepted Quest", AcceptQuestResult);
	TestTrue("Quest System has 1 quest", NewQuestSystemComponent->GetQuestCount() == 1);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FQS_QuestSystem_TestAcceptQuestAutoUpdateActiveQuest_Independent, "QuestSystem.Independent.AutoUpdateActiveQuest",
	EAutomationTestFlags::EditorContext |
	EAutomationTestFlags::ClientContext |
	EAutomationTestFlags::ProductFilter)

	bool FQS_QuestSystem_TestAcceptQuestAutoUpdateActiveQuest_Independent::RunTest(const FString& Parameters) {
	AutomationOpenMap(TEXT(QUESTSYSTEM_TESTLEVEL));

	UQS_QuestSystemComponentMockBase* NewQuestSystemComponent = NewObject<UQS_QuestSystemComponentEmptyMock>();

	TestTrue("Quest System has no active quest", !NewQuestSystemComponent->HasActiveQuest());
	NewQuestSystemComponent->AcceptQuest(UQS_BasicQuestMock::StaticClass());
	TestTrue("Quest System has an active quest", NewQuestSystemComponent->HasActiveQuest());

	return true;
}

// --

// -- Quest Accept Tests (Coupled)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FQS_QuestSystem_TestAcceptQuest, "QuestSystem.Coupled.AcceptQuest",
	EAutomationTestFlags::EditorContext |
	EAutomationTestFlags::ClientContext |
	EAutomationTestFlags::ProductFilter)

	bool FQS_QuestSystem_TestAcceptQuest::RunTest(const FString& Parameters) {
	AutomationOpenMap(TEXT(QUESTSYSTEM_TESTLEVEL));

	UWorld* world = GetTestWorld();
	AQS_QuesterCharacter* QuesterCharacter = *TActorIterator<AQS_QuesterCharacter>(world);
	QuesterCharacter->SetQuestSystem(NewObject<UQS_QuestSystemComponentEmptyMock>());

	TestTrue("Quester has 0 quests", QuesterCharacter->GetQuestSystemComponent()->GetQuestCount() == 0);
	bool AcceptQuestResult = QuesterCharacter->GetQuestSystemComponent()->AcceptQuest(UQS_BasicQuestMock::StaticClass());
	TestTrue("Quester Successfuly Accepted Quest", AcceptQuestResult);
	TestTrue("Quester has 1 quest", QuesterCharacter->GetQuestSystemComponent()->GetQuestCount() == 1);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FQS_QuestSystem_TestAcceptQuestAutoUpdateActiveQuest, "QuestSystem.Coupled.AutoUpdateActiveQuest",
	EAutomationTestFlags::EditorContext |
	EAutomationTestFlags::ClientContext |
	EAutomationTestFlags::ProductFilter)

	bool FQS_QuestSystem_TestAcceptQuestAutoUpdateActiveQuest::RunTest(const FString& Parameters) {
	AutomationOpenMap(TEXT(QUESTSYSTEM_TESTLEVEL));

	UWorld* world = GetTestWorld();
	AQS_QuesterCharacter* QuesterCharacter = *TActorIterator<AQS_QuesterCharacter>(world);
	QuesterCharacter->SetQuestSystem(NewObject<UQS_QuestSystemComponentEmptyMock>());

	TestTrue("Quester has no active quest", !QuesterCharacter->GetQuestSystemComponent()->HasActiveQuest());
	QuesterCharacter->GetQuestSystemComponent()->AcceptQuest(UQS_BasicQuestMock::StaticClass());
	TestTrue("Quester has an active quest", QuesterCharacter->GetQuestSystemComponent()->HasActiveQuest());

	return true;
}

// ---

// -- Quest Progression Tests (Decoupled)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FQS_QuestSystem_TestProgressQuest, "QuestSystem.Independent.ProgressQuest",
	EAutomationTestFlags::EditorContext |
	EAutomationTestFlags::ClientContext |
	EAutomationTestFlags::ProductFilter)

	bool FQS_QuestSystem_TestProgressQuest::RunTest(const FString& Parameters) {
	AutomationOpenMap(TEXT(QUESTSYSTEM_TESTLEVEL));

	UQS_QuestSystemComponentMockBase* NewQuestSystemComponent = NewObject<UQS_QuestSystemComponentEmptyMock>();
	NewQuestSystemComponent->AcceptQuest(UQS_BasicQuestMock::StaticClass());

	bool ProgressQuestResult = NewQuestSystemComponent->ProgressQuest(UQS_BasicQuestMock::StaticClass(), FString(TEXT("TestRequirement_Primary")));
	TestTrue("Quest System Successfuly Progressed Quest", ProgressQuestResult);

	UQS_BasicQuestMock* QuestMock = Cast<UQS_BasicQuestMock>(NewQuestSystemComponent->GetQuestBySpec(UQS_BasicQuestMock::StaticClass()));
	TestTrue("Quest System has one completed objective", QuestMock->CompletedObjectives == 1);

	return true;
}
