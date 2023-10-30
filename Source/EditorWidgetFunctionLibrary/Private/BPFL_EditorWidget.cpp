// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFL_EditorWidget.h"
#include "DesktopPlatform/Public/IDesktopPlatform.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Engine/GameEngine.h"
#include "EngineGlobals.h"
#include "SlateCore.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "Framework/Application/SlateApplication.h"
#include "Misc/FileHelper.h"
#include "Dialog/SCustomDialog.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SWindow.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SBoxPanel.h"
#include "EditorStyleSet.h"
#include "Interfaces/IMainFrameModule.h"


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

void UBPFL_EditorWidget::ShowFileOpenDialog(FString DialogTitle, FString DefaultPath, FString FileTypes, TArray<FString>& OutputFilePaths)
{
    void* ParentWindowPtr = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle();
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        uint32 SelectionFlag = 0; //A value of 0 represents single file selection while a value of 1 represents multiple file selection
        DesktopPlatform->OpenFileDialog(ParentWindowPtr, DialogTitle, DefaultPath, FString(""), FileTypes, SelectionFlag, OutputFilePaths);
    }
}

//Add safety checks if user presses cancel

TArray<FString> UBPFL_EditorWidget::LoadFromTextFile()
{
    TArray<FString> FilePath;

    ShowFileOpenDialog("Text File to Load", " ", " ", FilePath);

    IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
    TArray<FString> FileContents;
    if (FileManager.FileExists(*FilePath[0]))
    {
        FFileHelper::LoadFileToStringArray(FileContents, *FilePath[0], FFileHelper::EHashOptions::None);
    }

    return FileContents;
}

//Add safety checks if user presses cancel

void UBPFL_EditorWidget::SaveToTextFile(FString InputString)
{
    TArray<FString> FilePath;
    TArray<FString> FileContents;

    ShowFileOpenDialog("Text File to Load", " ", " ", FilePath);

    InputString.ParseIntoArrayLines(FileContents, false);

    IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
    if (FileManager.FileExists(*FilePath[0]))
    {
        FFileHelper::SaveStringArrayToFile(FileContents, *FilePath[0]);
    }

}

#define LOCTEXT_NAMESPACE "ConfirmationDialog"

void UBPFL_EditorWidget::ShowConfirmationDialog(ELoginDialogChoice& BranchChoice)
{
        //This is the contents of the Dialogue Prompt itself, we sequester it into its neat area!
        TSharedRef<SVerticalBox> DialogContents = SNew(SVerticalBox)
        + SVerticalBox::Slot()
        [
            SNew(STextBlock)
            .Text(LOCTEXT("HelperLabel", "Press Confirm to confirm the action, or otherwise Cancel the action."))
        ];

        //The Dialogue Box that will pop up (it automatically has OK & CANCEL button. If you pressed OK, it executes 0, if you press CANCEL it executes 1)
        TSharedRef<SCustomDialog> HelloWorldDialog = SNew(SCustomDialog)
        .Title(LOCTEXT("1", "Cancel"))
        .DialogContent(DialogContents)	//Without this, it crashes. Fills the Slate with other Slates (from before)
        .Buttons({ SCustomDialog::FButton(LOCTEXT("Confirmation", "Confirm")), SCustomDialog::FButton(LOCTEXT("Cancel", "Cancel")) });

        // returns 0 when OK is pressed, 1 when Cancel is pressed
        int ButtonPressed = HelloWorldDialog->ShowModal();

        switch (ButtonPressed)
        {
            case 0:
                UE_LOG(LogTemp, Warning, TEXT("Confirm Pressed"));
                BranchChoice = ELoginDialogChoice::PressedOk;
                break;
            case 1:
                UE_LOG(LogTemp, Warning, TEXT("Cancelled Pressed"));
                BranchChoice = ELoginDialogChoice::PressedCancel;
                break;
            default:
                UE_LOG(LogTemp, Warning, TEXT("Default"));
                BranchChoice = ELoginDialogChoice::PressedCancel;
                break;
        }
}

#undef LOCTEXT_namespace

bool UBPFL_EditorWidget::IsKeyDown(FKey InKey)
{
    FViewport* EditorViewport = GEditor->GetActiveViewport();
    return EditorViewport->KeyState(InKey);
}


UDelayLoop::UDelayLoop(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr), MyDelay(0.0f), MyIterations(0), Active(false)
{

}

UDelayLoop* UDelayLoop::DelayLoop(const UObject* WorldContextObject, const float DelayInSeconds, const int Iterations)
{
    UDelayLoop* Node = NewObject<UDelayLoop>();
    Node->WorldContextObject = WorldContextObject;
    Node->MyDelay = DelayInSeconds;
    Node->MyIterations = Iterations;
    return Node;
}


void UDelayLoop::Activate()
{
    if (nullptr == WorldContextObject)
    {
        FFrame::KismetExecutionMessage(TEXT("Invalid WorldContextObject."), ELogVerbosity::Error);
        return;
    }
    if (Active)
    {
        FFrame::KismetExecutionMessage(TEXT("DelayLoop is already running."), ELogVerbosity::Warning);
    }
    if (MyDelay <= 0.0f)
    {
        FFrame::KismetExecutionMessage(TEXT("DelayLoop delay can't be less or equal to 0."), ELogVerbosity::Warning);
    }
    if (MyIterations <= 0)
    {
        FFrame::KismetExecutionMessage(TEXT("DelayLoop iterations can't be less or equal to 0."), ELogVerbosity::Warning);
    }

    Active = true;

    FScopedSlowTask SlateNotificationBar(MyIterations, LOCTEXT("LookingForUnusedAssetsText", "Looking for assets to remove"));
    SlateNotificationBar.MakeDialog();
    


    for (int i = 0; i <= MyIterations; i++)
    {
        FTimerHandle IterationTimer;
        SlateNotificationBar.EnterProgressFrame(1.0f/(float) MyIterations);
        WorldContextObject->GetWorld()->GetTimerManager().SetTimer(IterationTimer, this, &UDelayLoop::ExecuteLoop, MyDelay * i);
    }

    FTimerHandle CompleteTimer;
    WorldContextObject->GetWorld()->GetTimerManager().SetTimer(CompleteTimer, this, &UDelayLoop::ExecuteComplete, MyDelay * (MyIterations + 1));
}

void UDelayLoop::ExecuteLoop()
{


    Loop.Broadcast();
}

void UDelayLoop::ExecuteComplete()
{
    Complete.Broadcast();
    Active = false;
}