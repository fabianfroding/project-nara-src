// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Player/NaraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ANaraPlayerController::ANaraPlayerController()
{

}

void ANaraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(NaraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem =  ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(NaraContext, 0);
}

void ANaraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANaraPlayerController::Move);
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
