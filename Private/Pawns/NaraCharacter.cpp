// Copyright Epic Games, Inc. All Rights Reserved.

#include "Pawns/NaraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Pawns/Components/NaraHealthComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ANaraCharacter::ANaraCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	HealthComponent = CreateDefaultSubobject<UNaraHealthComponent>(TEXT("HealthComponent"));

	AbilitySystemComponent->OnComponentActivated.AddUniqueDynamic(this, &ANaraCharacter::OnAbilitySystemComponentInitialized);
}

void ANaraCharacter::OnAbilitySystemComponentInitialized(UActorComponent* Component, bool bReset)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	check(ASC);
	HealthComponent->InitializeWithAbilitySystem(ASC);
	AbilitySystemComponent->OnComponentActivated.RemoveDynamic(this, &ANaraCharacter::OnAbilitySystemComponentInitialized);
}
