// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFL_EditorWidget.h"
#include "DesktopPlatform/Public/IDesktopPlatform.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Engine/GameEngine.h"
#include "EngineGlobals.h"
#include "SlateCore.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "Framework/Application/SlateApplication.h"

void UBPFL_EditorWidget::ShowNotification(FString NotificationString, float NotificationTimeLength)
{
    FNotificationInfo Info(("SpawnNotification_Notification", FText::FromString(NotificationString)));
    Info.ExpireDuration = NotificationTimeLength;
    FSlateNotificationManager::Get().AddNotification(Info);
}

void UBPFL_EditorWidget::ShowNotificationSuccessFail(bool WasSuccessful, FString NotificationStringOnSuccess, FString NotificationStringOnFail, float NotificationTimeLength)
{
    FText BlankText;
    FNotificationInfo Info(("SpawnNotification_Notification", BlankText));
    Info.ExpireDuration = NotificationTimeLength;

    //Allow an icon to be shown
    Info.bUseSuccessFailIcons = true;

    //Denote what icon to show
    if (WasSuccessful)
    {
        Info.Text = FText::FromString(NotificationStringOnSuccess);
        Info.Image = FEditorStyle::GetBrush(TEXT("Tutorials.Browser.Completed"));
    }
    else
    {
        Info.Text = FText::FromString(NotificationStringOnFail);
        Info.Image = FEditorStyle::GetBrush(TEXT("MessageLog.Error"));
    }

    FSlateNotificationManager::Get().AddNotification(Info);
}

void UBPFL_EditorWidget::ShowFileOpenDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, TArray<FString>& OutFileNames)
{
    void* ParentWindowPtr = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle();
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        uint32 SelectionFlag = 0; //A value of 0 represents single file selection while a value of 1 represents multiple file selection
        DesktopPlatform->OpenFileDialog(ParentWindowPtr, DialogTitle, DefaultPath, FString(""), FileTypes, SelectionFlag, OutFileNames);
    }
}