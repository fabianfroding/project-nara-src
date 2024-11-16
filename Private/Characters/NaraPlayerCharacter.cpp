// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Characters/NaraPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Core/NaraAssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/NaraPlayerState.h"

ANaraPlayerCharacter::ANaraPlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ANaraPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	ANaraPlayerState* NaraPlayerState = GetPlayerState<ANaraPlayerState>();
	check(NaraPlayerState);
	NaraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(NaraPlayerState, this);
	AbilitySystemComponent = NaraPlayerState->GetAbilitySystemComponent();
	AttributeSet = NaraPlayerState->GetAttributeSet();

	for (TSoftClassPtr<UGameplayAbility> SoftStartingAbility : StartingAbilities)
	{
		UClass* AbilityClass = UNaraAssetManager::LoadClassFromSoftClassPtr(SoftStartingAbility.Get());
		if (!UKismetSystemLibrary::IsValidClass(AbilityClass))
			continue;

		FGameplayAbilitySpec AbilitySpec(AbilityClass);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}
