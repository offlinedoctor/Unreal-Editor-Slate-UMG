// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "BPFL_EditorWidget.generated.h"

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
	static void ShowFileOpenDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, TArray<FString>& OutFileNames);

};
