// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBBBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UNREALCPPSTUDY_API UWidgetBBBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

#if WITH_EDITOR

	virtual const FText GetPaletteCategory() override;

#endif

protected:


private:

};
