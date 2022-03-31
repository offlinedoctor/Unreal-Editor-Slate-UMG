// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Widgets/Colors/SColorWheel.h"
#include "EW_Widget_ColorSelector.generated.h"

/**
 * 
 */
UCLASS()
class EDITORWIDGETFUNCTIONLIBRARY_API UEW_Widget_ColorSelector : public UWidget
{
	GENERATED_BODY()
	
	public:
	virtual void ReleaseSlateResources(bool bRelease) override;

	UFUNCTION(BlueprintPure)
	FLinearColor GetWheelColor();

	void CaptureColorChosen(FLinearColor NewColor);
	FLinearColor GetColorChosenDisplayUI() const;

	protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SColorWheel> WidgetColorWheel;

	private:
	FLinearColor CaptureColor;
};
