// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDBB.h"
#include "CharacterBB.h"
#include "HSPBarBase.h"
#include "MinimalLayoutBase.h"
#include "ModerateLayoutBase.h"
#include "OverloadLayoutBase.h"
#include "StatBarBase.h"

void AHUDBB::CycleToNextViewMode()
{
	++CurrentViewMode;
	UE_LOG(LogTemp, Warning, TEXT("CycleToNextViewMode %s"), *UEnum::GetValueAsString(CurrentViewMode));
	UpdateWidgets();
}

void AHUDBB::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
	checkf(World, TEXT("Failed to reference world"));

	checkf(MinimalLayoutClass, TEXT("Invalid MinimalLayoutClass reference"));
	checkf(ModerateLayoutClass, TEXT("Invalid ModerateLayoutClass reference"));
	checkf(OverloadLayoutClass, TEXT("Invalid OverloadLayoutClass reference"));

	MinimalLayoutWidget = CreateWidget<UMinimalLayoutBase>(World, MinimalLayoutClass);
	MinimalLayoutWidget->AddToViewport();
	MinimalLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	ModerateLayoutWidget = CreateWidget<UModerateLayoutBase>(World, ModerateLayoutClass);
	ModerateLayoutWidget->AddToViewport();
	ModerateLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	OverloadLayoutWidget = CreateWidget<UOverloadLayoutBase>(World, OverloadLayoutClass);
	OverloadLayoutWidget->AddToViewport();
	OverloadLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	if (APlayerController* PlayerController = GetOwningPlayerController())
	{
		PlayerCharacter = Cast<ACharacterBB>(PlayerController->GetPawn());
	}
	checkf(PlayerCharacter, TEXT("Unable to get a reference to the player character"));

	UpdateWidgets();
}

void AHUDBB::UpdateWidgets()
{
	ClearAllHandlers();

	MinimalLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);
	ModerateLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);
	OverloadLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	switch (CurrentViewMode)
	{
	case EHudViewMode::CleanAndPristine:
		//Nothing to show
		break;
	case EHudViewMode::Minimal:
		PlayerCharacter->OnHealthChanged.AddDynamic(MinimalLayoutWidget->HSPBar->HealthBar, &UStatBarBase::OnIntStatUpdated );
		PlayerCharacter->OnStaminaChanged.AddDynamic(MinimalLayoutWidget->HSPBar->StaminaBar, &UStatBarBase::OnFloatStatUpdated);
		PlayerCharacter->OnPsiPowerChanged.AddDynamic(MinimalLayoutWidget->HSPBar->PsiBar, &UStatBarBase::OnFloatStatUpdated);
			
		MinimalLayoutWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case EHudViewMode::Moderate:
		PlayerCharacter->OnHealthChanged.AddDynamic(ModerateLayoutWidget->HSPBar->HealthBar, &UStatBarBase::OnIntStatUpdated);
		PlayerCharacter->OnStaminaChanged.AddDynamic(ModerateLayoutWidget->HSPBar->StaminaBar, &UStatBarBase::OnFloatStatUpdated);
		PlayerCharacter->OnPsiPowerChanged.AddDynamic(ModerateLayoutWidget->HSPBar->PsiBar, &UStatBarBase::OnFloatStatUpdated);

		ModerateLayoutWidget->SetVisibility(ESlateVisibility::Visible);

		break;
	case EHudViewMode::SensoryOverLoad:
		PlayerCharacter->OnHealthChanged.AddDynamic(OverloadLayoutWidget->HSPBar->HealthBar, &UStatBarBase::OnIntStatUpdated);
		PlayerCharacter->OnStaminaChanged.AddDynamic(OverloadLayoutWidget->HSPBar->StaminaBar, &UStatBarBase::OnFloatStatUpdated);
		PlayerCharacter->OnPsiPowerChanged.AddDynamic(OverloadLayoutWidget->HSPBar->PsiBar, &UStatBarBase::OnFloatStatUpdated);

		OverloadLayoutWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	default:
		break;
	}

	// This ensures that even if something has not changed recently, the newly switched-to widget will get sent
	// the latest character stats, so it can update itself.
	PlayerCharacter->BroadcastCurrentStats();
}

void AHUDBB::ClearAllHandlers()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->OnHealthChanged.Clear();
		PlayerCharacter->OnStaminaChanged.Clear();
		PlayerCharacter->OnPsiPowerChanged.Clear();
		PlayerCharacter->OnKeyWalletAction.Clear();
	}
}
