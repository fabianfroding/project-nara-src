// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Characters/NaraCharacter.h"

#include "AbilitySystemComponent.h"
#include "ActorComponents/NaraFlashComponent.h"
#include "ActorComponents/NaraHealthComponent.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

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

	HealthComponent = CreateDefaultSubobject<UNaraHealthComponent>(TEXT("HealthComponent"));
	FlashComponent = CreateDefaultSubobject<UNaraFlashComponent>(TEXT("FlashComponent"));
}

void ANaraCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComponent != nullptr)
		HealthComponent->InitializeWithAbilitySystem(AbilitySystemComponent);

	InitAbilityActorInfo();
}
