// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBB.generated.h"

class UInputMappingContext;
class UEnhancedInputComponent;
class ACharacterBB;
class AHUDBB;

/**
 * 
 */
UCLASS(Abstract)
class UNREALCPPSTUDY_API APlayerControllerBBBase : public APlayerController
{
	GENERATED_BODY()

public:

	// The input action to map to movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionLook = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionToggleCrouch = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionToggleSprint = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionPsiBlast = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionCycleUIMode = nullptr;

	// The input mapping context to use
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|UI")
	UInputMappingContext* InputMappingContext;

protected:

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleJump();
	void HandlePsiBlast();
	void HandleToggleSprint();
	void HandleToggleCrouch();
	void HandleCycleUIMode();

private:

	// Used to store a refrence to the InputComponent cast to an EnhancedInputComponent
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	// Used to store a reference to the pawn we are controlling
	UPROPERTY()
	ACharacterBB* PlayerCharacter = nullptr;
	
	UPROPERTY()
	AHUDBB* PlayerHud = nullptr;
};