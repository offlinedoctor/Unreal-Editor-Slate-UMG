// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "AssetData.h"	
#include "PropertyCustomizationHelpers.h"
#include "EW_Widget_EyeDropper.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = "Slates")
class EDITORWIDGETFUNCTIONLIBRARY_API UEW_Widget_EyeDropper : public UWidget
{
	GENERATED_BODY()

	public:
	virtual void ReleaseSlateResources(bool bRelease) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AActor* GetSelectedChoice();

	protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SObjectPropertyEntryBox> EyeDropperWidget;

	virtual const FText GetPaletteCategory() override
	{
		return FText::FromString("Slates");
	}
	
	private:
	FAssetData StoredAssetData;
	FString DisplayUI()	const;
	void AssetSelected(const FAssetData& InAssetData);
	bool ReturnTrueForAsset(const FAssetData& InAssetData) const;
	bool ReturnTrue() const;

};
