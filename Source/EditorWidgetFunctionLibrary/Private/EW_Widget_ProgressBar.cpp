// Fill out your copyright notice in the Description page of Project Settings.


#include "EW_Widget_ProgressBar.h"

void UEW_Widget_ProgressBar::ReleaseSlateResources(bool bRelease)
{
    ProgressBarWidget.Reset();
}

TSharedRef<SWidget> UEW_Widget_ProgressBar::RebuildWidget()
{
    ProgressBarWidget = SNew(SProgressBar);
    return ProgressBarWidget.ToSharedRef();
}

void UEW_Widget_ProgressBar::SetBarPercentage(float PercentageFill)
{
    ProgressBarWidget->SetPercent(PercentageFill);
}