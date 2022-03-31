// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "EW_Widget_ProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class EDITORWIDGETFUNCTIONLIBRARY_API UEW_Widget_ProgressBar : public UWidget
{
	GENERATED_BODY()

	public:
	virtual void ReleaseSlateResources(bool bRelease) override;

	UFUNCTION(BlueprintCallable)
	void SetBarPercentage(float PercentageFill);

	protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SProgressBar> ProgressBarWidget;
	
};
