// Fill out your copyright notice in the Description page of Project Settings.


#include "EW_Widget_EyeDropper.h"

void UEW_Widget_EyeDropper::ReleaseSlateResources(bool bRelease)
{
    EyeDropperWidget.Reset();
}

TSharedRef<SWidget> UEW_Widget_EyeDropper::RebuildWidget()
{
    EyeDropperWidget = SNew(SObjectPropertyEntryBox)
        .AllowedClass(AActor::StaticClass())
        .OnObjectChanged_UObject(this, &UEW_Widget_EyeDropper::AssetSelected)		//this is called when you select an asset as the reference
        .ObjectPath_UObject(this, &UEW_Widget_EyeDropper::DisplayUI)				//this sets it the object path [i.e. literally displays on UX]	
        .OnIsEnabled_UObject(this, &UEW_Widget_EyeDropper::ReturnTrue)
        .OnShouldSetAsset_UObject(this, &UEW_Widget_EyeDropper::ReturnTrueForAsset);

    return EyeDropperWidget.ToSharedRef();
}

void UEW_Widget_EyeDropper::AssetSelected(const FAssetData& InAssetData)
{
    //This is called once on Dye Drop Change.
    StoredAssetData = InAssetData;
}

FString UEW_Widget_EyeDropper::DisplayUI() const
{
    //This is called on Tick, cannot change it.
    return StoredAssetData.ObjectPath.ToString();
}

bool UEW_Widget_EyeDropper::ReturnTrueForAsset(const FAssetData& InAssetData) const
{
    return true;
}

bool UEW_Widget_EyeDropper::ReturnTrue() const
{
    return true;
}

AActor* UEW_Widget_EyeDropper::GetSelectedChoice()
{
    UObject* storeAsObject = StoredAssetData.GetAsset();
    AActor* ActorReference = Cast<AActor>(storeAsObject);
    return ActorReference;
}