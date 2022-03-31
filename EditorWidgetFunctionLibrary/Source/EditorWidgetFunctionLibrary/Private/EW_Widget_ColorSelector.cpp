// Fill out your copyright notice in the Description page of Project Settings.

#include "EW_Widget_ColorSelector.h"
#include "Widgets/DeclarativeSyntaxSupport.h"


void UEW_Widget_ColorSelector::ReleaseSlateResources(bool bRelease)
{
	WidgetColorWheel.Reset();
}

TSharedRef<SWidget> UEW_Widget_ColorSelector::RebuildWidget()
{
    WidgetColorWheel = SNew(SColorWheel)
              .OnValueChanged_UObject(this, &UEW_Widget_ColorSelector::CaptureColorChosen)
              .SelectedColor_UObject(this, &UEW_Widget_ColorSelector::GetColorChosenDisplayUI);

	return WidgetColorWheel.ToSharedRef();
}

void UEW_Widget_ColorSelector::CaptureColorChosen(FLinearColor NewColor)
{
    //On Colour Pick Change, we'll capture the value and store it.
    CaptureColor.R = NewColor.R;
    CaptureColor.G = NewColor.G;
    CaptureColor.B = 1.0f;
}

FLinearColor UEW_Widget_ColorSelector::GetColorChosenDisplayUI() const
{
    //This is called each tick and ensures the ColourWheel SlateUI actually updates itself and acknowledges
    //the new colour value.
    return CaptureColor;
}

FLinearColor UEW_Widget_ColorSelector::GetWheelColor()
{
    FLinearColor RGB_EquivalentColor = CaptureColor;
    RGB_EquivalentColor.A = 1.0f;
    return RGB_EquivalentColor.HSVToLinearRGB();
}