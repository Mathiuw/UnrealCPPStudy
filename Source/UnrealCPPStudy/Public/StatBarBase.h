// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBBBase.h"
#include "Brushes/SlateColorBrush.h"
#include "StatBarBase.generated.h"

class UVerticalBox;
class UBorder;
class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class UNREALCPPSTUDY_API UStatBarBase : public UWidgetBBBase
{
	GENERATED_BODY()
	
public:
	//Function that can be called to update the bar using int values
	UFUNCTION()
	void OnIntStatUpdated(int32 OldValue, int32 NewValue, int32 MaxValue);

	//Function that can be called to update the bar using float values
	UFUNCTION()
	void OnFloatStatUpdated(float OldValue, float NewValue, float MaxValue);

#if WITH_EDITOR
	virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif 

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	TObjectPtr<UBorder> MainBorder = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	TObjectPtr<UVerticalBox> PercentBars = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	TObjectPtr<UImage> IconImage = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	TObjectPtr<UBorder> PercentBar_Empty = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	TObjectPtr<UBorder> PercentBar_Filled = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	TObjectPtr<UTextBlock> ValueText = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = "Stat Bar")
	FSlateBrush IconBrush;

	UPROPERTY(EditAnywhere, Category = "Stat Bar")
	FLinearColor BarBackgroundColor = FLinearColor(0.3f, 0.f, 0.f, 0.3f);

	UPROPERTY(EditAnywhere, Category = "Stat Bar")
	FLinearColor BarForegroundColor = FLinearColor(1.f, 0.f, 0.f, 0.75f);

	UPROPERTY(EditAnywhere, Category = "Stat Bar")
	bool isFullSize = true;

	// Internal variable to store the current 'filled' amount
	// 'Clamped' to stop the value going outside of what we consider a % to be
	UPROPERTY(EditAnywhere, Category = "Stat Bar|Testing", meta = (ClampMin = 0, UIMin = 0, UIMax = 1, ClampMax = 1, Units="Percent"))
	float CurrentPercentage = 0.f;

	// This is the 'actual' value of the current amount
	UPROPERTY(EditAnywhere, Category = "Stat Bar|Testing", meta = (ClampMin = 0, UIMin = 0))
	float CurrentValue = 100.f;

	// This does not need to be a property as iy is never serialized,
	// and is totally dependant on the current value
	FText CurrentValueText;

	// This function works out what should be displayed in the TextBox,
	// Based on the CurrentValue
	void ProcessCurrentValueText();

	//Called after any changes are made to redraw the bar
	void UpdateWidget();

};
