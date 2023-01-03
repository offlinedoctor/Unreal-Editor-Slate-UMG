// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Widgets/Input/SDirectoryPicker.h"
#include "EW_Widget_FolderPicker.generated.h"

/**
 * 
 */
UCLASS()
class EDITORWIDGETFUNCTIONLIBRARY_API UEW_Widget_FolderPicker : public UWidget
{
	GENERATED_BODY()

	public:
	virtual void ReleaseSlateResources(bool bRelease) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetFilePath();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetDirectory();

	protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SDirectoryPicker> FolderPickerWidget;

	virtual const FText GetPaletteCategory() override
	{
		return FText::FromString("Slates");
	}

};
