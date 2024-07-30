// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBB.h"
#include "CharacterBB.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HUDBB.h"

void APlayerControllerBBBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// Store a reference to the HUD
	PlayerHud = Cast<AHUDBB>(GetHUD());
	checkf(PlayerHud, TEXT("Unable to get reference to the HUD"));

	// Store a reference to player's pawn
	PlayerCharacter = Cast<ACharacterBB>(aPawn);
	checkf(PlayerCharacter, TEXT("APlayerControllerBBASE derived classes should only possess ACharacterBBBase"));

	// Get a reference to the EnhencedInputComponent
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Unable to get a reference to the EnhancedInputComponent"));

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get referance to the EnhancedInputLocalSubsystem"));

	// Wipe existing mappings, and add our mapping
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);

	// Bind the input actions
	// Only attempt to bind if a valid value was provided
	if (ActionMove)
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &APlayerControllerBBBase::HandleMove);
	}

	if (ActionLook)
	{
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &APlayerControllerBBBase::HandleLook);
	}

	if (ActionJump)
	{
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this, &APlayerControllerBBBase::HandleJump);
	}

	if (ActionPsiBlast)
	{
		EnhancedInputComponent->BindAction(ActionPsiBlast, ETriggerEvent::Triggered, this, &APlayerControllerBBBase::HandlePsiBlast);
	}

	if (ActionToggleSprint)
	{
		EnhancedInputComponent->BindAction(ActionToggleSprint, ETriggerEvent::Triggered, this, &APlayerControllerBBBase::HandleToggleSprint);
	}

	if (ActionToggleCrouch)
	{
		EnhancedInputComponent->BindAction(ActionToggleCrouch, ETriggerEvent::Triggered, this, &APlayerControllerBBBase::HandleToggleCrouch);
	}

	if (ActionCycleUIMode)
	{
		EnhancedInputComponent->BindAction(ActionCycleUIMode, ETriggerEvent::Triggered, this, &APlayerControllerBBBase::HandleCycleUIMode);
	}
}

void APlayerControllerBBBase::OnUnPossess()
{
	// Unbind things here...
	EnhancedInputComponent->ClearActionBindings();

	// Call the parent method
	Super::OnUnPossess();
}

void APlayerControllerBBBase::HandleLook(const FInputActionValue& InputActionValue)
{
	// Input is a Vector2D
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();

	// Add yaw and pitch input to controller
	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}

void APlayerControllerBBBase::HandleMove(const FInputActionValue& InputActionValue)
{
	// Value is a Vector2D
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	//Add movement to the player's character pawn
	if (PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
	}
}

void APlayerControllerBBBase::HandleJump()
{
	//Make the player's character pawn jump, disabling crouch if it was active
	if (PlayerCharacter)
	{
		PlayerCharacter->UnCrouch();
		PlayerCharacter->Jump();
	}
}

void APlayerControllerBBBase::HandlePsiBlast()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->PsiBlast();
	}
}

void APlayerControllerBBBase::HandleToggleSprint()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->ToggleRunning();
	}
}

void APlayerControllerBBBase::HandleToggleCrouch()
{
	if (PlayerCharacter && PlayerCharacter->bIsCrouched) 
	{
		PlayerCharacter->UnCrouch();
	}
	else
	{
		PlayerCharacter->Crouch();
	}
		
}

void APlayerControllerBBBase::HandleCycleUIMode()
{
	if (PlayerHud)
	{
		PlayerHud->CycleToNextViewMode();
	}
}
