// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFL_EditorWidget.h"


void UBPFL_EditorWidget::ShowNotification(FString NotificationString, float NotificationTimeLength)
{
    FNotificationInfo Info(("SpawnNotification_Notification", FText::FromString(NotificationString)));
    Info.ExpireDuration = NotificationTimeLength;
    FSlateNotificationManager::Get().AddNotification(Info);
}

void UBPFL_EditorWidget::ShowNotificationSuccessFail(bool WasSuccessful, FString NotificationString, float NotificationTimeLength)
{
    FNotificationInfo Info(("SpawnNotification_Notification", FText::FromString(NotificationString)));
    Info.ExpireDuration = NotificationTimeLength;

    //Allow an icon to be shown
    Info.bUseSuccessFailIcons = true;

    //Denote what icon to show
    if (WasSuccessful)
    {
        Info.Image = FEditorStyle::GetBrush(TEXT("MessageLog.Success"));
    }
    else
    {
        Info.Image = FEditorStyle::GetBrush(TEXT("MessageLog.Error"));
    }
    
    FSlateNotificationManager::Get().AddNotification(Info);
}