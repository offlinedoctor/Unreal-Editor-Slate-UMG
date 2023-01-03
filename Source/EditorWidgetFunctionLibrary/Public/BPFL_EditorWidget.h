// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Misc/ScopedSlowTask.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "BPFL_EditorWidget.generated.h"

//FDelayOutputPin is a custom name doesn't mean anything just used for delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelayOutputPin);

UENUM(BlueprintType)
enum class ELoginDialogChoice : uint8
{
	PressedOk,
	PressedCancel
};


/**
 * 
 */

UCLASS()
class EDITORWIDGETFUNCTIONLIBRARY_API UBPFL_EditorWidget : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Editor Widget Blueprint Function Library")
	static void ShowNotification(FString NotificationString, float NotificationTimeLength);

	UFUNCTION(BlueprintCallable, Category = "Editor Widget Blueprint Function Library")
	static void ShowNotificationSuccessFail(bool WasSuccessful, FString NotificationStringOnSuccess, FString NotificationStringOnFail, float NotificationTimeLength);

	UFUNCTION(BlueprintCallable, Category = "Editor Widget Blueprint Function Library")
	static void ShowFileOpenDialog(FString DialogTitle, FString DefaultPath, FString FileTypes, TArray<FString>& OutputFilePaths);

	UFUNCTION(BlueprintCallable, Category = "Editor Widget Blueprint Function Library")
	static TArray<FString> LoadFromTextFile();

	UFUNCTION(BlueprintCallable, Category = "Editor Widget Blueprint Function Library")
	static void SaveToTextFile(FString FileContents);

	UFUNCTION(BlueprintCallable, Category = "Editor Widget Blueprint Function Library", Meta = (ExpandEnumAsExecs = "BranchChoice"))
	static void ShowConfirmationDialog(ELoginDialogChoice& BranchChoice);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Editor Widget Blueprint Function Library")
	static bool IsKeyDown(FKey InKey);

};

#define LOCTEXT_NAMESPACE "ConfirmationDialog"

UCLASS()
class EDITORWIDGETFUNCTIONLIBRARY_API UDelayLoop : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

	public:
		UPROPERTY(BlueprintAssignable)
		FDelayOutputPin Loop;

		UPROPERTY(BlueprintAssignable)
		FDelayOutputPin Complete;

		UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
		static UDelayLoop* DelayLoop(const UObject* WorldContextObject, const float DelayInSeconds = 0.05f, const int Iterations = 1);

		virtual void Activate() override;

	private:
		const UObject* WorldContextObject;
		float MyDelay;
		int MyIterations;
		bool Active;

		UFUNCTION()
		void ExecuteLoop();

		UFUNCTION()
		void ExecuteComplete();
};

#undef LOCTEXT_namespace