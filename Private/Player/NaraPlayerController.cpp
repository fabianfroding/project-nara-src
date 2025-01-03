// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Player/NaraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GAS/NaraAbilitySystemComponent.h"
#include "Input/NaraInputComponent.h"

UNaraAbilitySystemComponent* ANaraPlayerController::GetASC()
{
	if (NaraASC == nullptr)
	{
		NaraASC = Cast<UNaraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return NaraASC;
}

void ANaraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(NaraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem =  ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
		Subsystem->AddMappingContext(NaraContext, 0);
}

void ANaraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UNaraInputComponent* NaraInputComponent = CastChecked<UNaraInputComponent>(InputComponent);

	NaraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANaraPlayerController::Move);
	NaraInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ANaraPlayerController::Jump);
	NaraInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ANaraPlayerController::StopJumping);

	NaraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void ANaraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(FVector(1.f, 0.f, 0.f), InputAxisVector.Y);
		ControlledPawn->AddMovementInput(FVector(0.f, 1.f, 0.f), InputAxisVector.X);
	}
}

void ANaraPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if (ACharacter* ControlledPawn = GetPawn<ACharacter>())
	{
		ControlledPawn->Jump();
	}
}

void ANaraPlayerController::StopJumping(const FInputActionValue& InputActionValue)
{
	if (ACharacter* ControlledPawn = GetPawn<ACharacter>())
	{
		ControlledPawn->StopJumping();
	}
}

void ANaraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (GetASC()) 
		GetASC()->AbilityInputTagPressed(InputTag);
}

void ANaraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void ANaraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}
