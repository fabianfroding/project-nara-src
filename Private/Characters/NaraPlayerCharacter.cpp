// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Characters/NaraPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Core/NaraGameplayTags.h"
#include "Core/NaraGameMode.h"
#include "Core/NaraSaveGame.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/NaraAbilitySystemComponent.h"
#include "GAS/NaraAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Libraries/NaraAbilitySystemLibrary.h"
#include "Player/NaraPlayerController.h"
#include "Player/NaraPlayerState.h"
#include "UI/NaraGameHUD.h"

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

void ANaraPlayerCharacter::AddCharacterAbilities()
{
	// TODO: Load in abilities form disk.
}

void ANaraPlayerCharacter::SaveProgress(const FName& CheckpointTag)
{
	ANaraGameMode* NaraGameMode = Cast<ANaraGameMode>(UGameplayStatics::GetGameMode(this));
	if (NaraGameMode)
	{
		UNaraSaveGame* SaveData = NaraGameMode->RetrieveInGameSaveData();
		if (SaveData == nullptr) return;

		SaveData->PlayerStartTag = CheckpointTag;

		SaveData->PlayerHealth = UNaraAttributeSet::GetHealthAttribute().GetNumericValue(GetAttributeSet());
		SaveData->PlayerMaxHealth = UNaraAttributeSet::GetMaxHealthAttribute().GetNumericValue(GetAttributeSet());

		SaveData->bFirstTimeLoadIn = false;

		if (!HasAuthority()) return;

		UNaraAbilitySystemComponent* NaraASC = Cast<UNaraAbilitySystemComponent>(AbilitySystemComponent);
		FForEachAbility SaveAbilityDelegate;
		SaveData->SavedAbilities.Empty();
		SaveAbilityDelegate.BindLambda([this, NaraASC, SaveData](const FGameplayAbilitySpec& AbilitySpec)
			{
				/*const FGameplayTag AbilityTag = NaraASC->GetAbilityTagFromSpec(AbilitySpec);
				UAbilityInfo* AbilityInfo = UNaraAbilitySystemLibrary::GetAbilityInfo(this);
				FNaraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);

				FSavedAbility SavedAbility;
				SavedAbility.GameplayAbility = Info.Ability;
				SavedAbility.AbilityTag = AbilityTag;

				SaveData->SavedAbilities.AddUnique(SavedAbility);*/
			});
		NaraASC->ForEachAbility(SaveAbilityDelegate);

		NaraGameMode->SaveInGameProgressData(SaveData);
	}
}

void ANaraPlayerCharacter::LoadProgress()
{
	ANaraGameMode* NaraGameMode = Cast<ANaraGameMode>(UGameplayStatics::GetGameMode(this));
	if (NaraGameMode)
	{
		UNaraSaveGame* SaveData = NaraGameMode->RetrieveInGameSaveData();
		if (SaveData == nullptr) return;

		if (SaveData->bFirstTimeLoadIn)
		{
			InitAbilityActorInfo();
			AddCharacterAbilities();
		}
		else
		{
			if (UNaraAbilitySystemComponent* AuraASC = Cast<UNaraAbilitySystemComponent>(AbilitySystemComponent))
			{
				AuraASC->AddCharacterAbilitiesFromSaveData(SaveData);
			}
			UNaraAbilitySystemLibrary::InitializeDefaultAttributesFromSaveData(this, AbilitySystemComponent, SaveData);
		}
	}
}

bool ANaraPlayerCharacter::IsDead_Implementation() const
{
	if (UNaraAttributeSet* NaraAS = Cast<UNaraAttributeSet>(GetPlayerState<ANaraPlayerState>()->GetAttributeSet()))
		return NaraAS->GetHealth() <= 0;
	return false;
}

void ANaraPlayerCharacter::InitAbilityActorInfo()
{
	ANaraPlayerState* NaraPlayerState = GetPlayerState<ANaraPlayerState>();
	check(NaraPlayerState);
	NaraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(NaraPlayerState, this);

	Cast<UNaraAbilitySystemComponent>(NaraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	AbilitySystemComponent = NaraPlayerState->GetAbilitySystemComponent();
	AttributeSet = NaraPlayerState->GetAttributeSet();
	OnAscRegistered.Broadcast(AbilitySystemComponent);
	AbilitySystemComponent->RegisterGameplayTagEvent(FNaraGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this, &ANaraPlayerCharacter::StunTagChanged);

	if (ANaraPlayerController* NaraPlayerController = Cast<ANaraPlayerController>(GetController()))
	{
		if (ANaraGameHUD* NaraGameHUD = Cast<ANaraGameHUD>(NaraPlayerController->GetHUD()))
		{
			NaraGameHUD->InitOverlay(NaraPlayerController, NaraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	//InitializeDefaultAttributes();
	LoadProgress();

	OnPlayerInitAbilityActorInfo.Broadcast(AbilitySystemComponent);
}
