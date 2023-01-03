// Fill out your copyright notice in the Description page of Project Settings.


#include "EW_Widget_FolderPicker.h"

void UEW_Widget_FolderPicker::ReleaseSlateResources(bool bRelease)
{
    FolderPickerWidget.Reset();
}

TSharedRef<SWidget> UEW_Widget_FolderPicker::RebuildWidget()
{
    FolderPickerWidget = SNew(SDirectoryPicker);

    return FolderPickerWidget.ToSharedRef();
}

FString UEW_Widget_FolderPicker::GetDirectory()
{
    return FolderPickerWidget->GetDirectory();
}

FString UEW_Widget_FolderPicker::GetFilePath()
{
    return FolderPickerWidget->GetFilePath();
}