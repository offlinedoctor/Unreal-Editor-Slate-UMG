// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Widgets/Input/SVolumeControl.h"
#include "EW_Widget_VolumeControl.generated.h"

/**
 * 
 */
UCLASS()
class EDITORWIDGETFUNCTIONLIBRARY_API UEW_Widget_VolumeControl : public UWidget
{
	GENERATED_BODY()

	public:
	virtual void ReleaseSlateResources(bool bRelease) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float ReturnVolume();

	protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SVolumeControl> VolumeControlWidget;
	
	virtual const FText GetPaletteCategory() override
	{
		return FText::FromString("Slates");
	}

};
