// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDBB.generated.h"

class ACharacterBB;
class UMinimalLayoutBase;
class UModerateLayoutBase;
class UOverloadLayoutBase;

UENUM(BlueprintType)
enum class EHudViewMode : uint8
{
	CleanAndPristine UMETA(ToolTip = "Get that mess outta my face!"),
	Minimal UMETA(ToolTip = "Just the facts maam"),
	Moderate UMETA(ToolTip = "Keep me well informed"),
	SensoryOverLoad UMETA(ToolTip = "My other ui is a derivatives trading screen")
};

inline EHudViewMode& operator++(EHudViewMode& viewmode) 
{
	if (viewmode == EHudViewMode::SensoryOverLoad)
	{
		viewmode = EHudViewMode::CleanAndPristine;
	}
	else
	{
		viewmode = static_cast<EHudViewMode>(static_cast<int>(viewmode) + 1);
	}

	return viewmode;
}

inline EHudViewMode& operator--(EHudViewMode& viewmode)
{
	if (viewmode == EHudViewMode::CleanAndPristine)
	{
		viewmode = EHudViewMode::SensoryOverLoad;
	}
	else
	{
		viewmode = static_cast<EHudViewMode>(static_cast<int>(viewmode) - 1);
	}

	return viewmode;
}

/**
 * 
 */
UCLASS()
class UNREALCPPSTUDY_API AHUDBB : public AHUD
{
	GENERATED_BODY() 

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMinimalLayoutBase> MinimalLayoutClass = nullptr;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UModerateLayoutBase> ModerateLayoutClass = nullptr;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverloadLayoutBase> OverloadLayoutClass = nullptr;

	UFUNCTION(BlueprintCallable)
	void CycleToNextViewMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Determines what UI elements should be displayed
	UPROPERTY(EditAnywhere)
	EHudViewMode CurrentViewMode = EHudViewMode::Moderate;

	// whenever we change the view mode, this private function is called to show the appropriate widgets.
	void UpdateWidgets();

	// Release any delegate bindings.
	void ClearAllHandlers();

	UPROPERTY()
	TObjectPtr<UWorld> World = nullptr;

	UPROPERTY()
	TObjectPtr<UMinimalLayoutBase> MinimalLayoutWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UModerateLayoutBase> ModerateLayoutWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UOverloadLayoutBase> OverloadLayoutWidget = nullptr;

	UPROPERTY()
	TObjectPtr<ACharacterBB> PlayerCharacter = nullptr;
};
