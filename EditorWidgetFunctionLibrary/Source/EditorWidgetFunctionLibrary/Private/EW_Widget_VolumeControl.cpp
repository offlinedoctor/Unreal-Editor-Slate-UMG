// Fill out your copyright notice in the Description page of Project Settings.


#include "EW_Widget_VolumeControl.h"

void UEW_Widget_VolumeControl::ReleaseSlateResources(bool bRelease)
{
    VolumeControlWidget.Reset();
}

TSharedRef<SWidget> UEW_Widget_VolumeControl::RebuildWidget()
{
    VolumeControlWidget = SNew(SVolumeControl);

    return VolumeControlWidget.ToSharedRef();
}

float UEW_Widget_VolumeControl::ReturnVolume()
{
    return VolumeControlWidget->GetVolume();
}
