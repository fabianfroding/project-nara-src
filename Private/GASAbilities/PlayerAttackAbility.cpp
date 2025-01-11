// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASAbilities/PlayerAttackAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
		return;
	}

	UAbilityTask_WaitInputRelease* WaitInputReleaseTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	if (WaitInputReleaseTask)
	{
		if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
		{
			// TODO: This should add a move speed modifiers instead. This will not reset to correct value if it has modifiers and they are removed while ability is active etc.
			DefaultMoveSpeed = Character->GetCharacterMovement()->MaxWalkSpeed;
			Character->GetCharacterMovement()->MaxWalkSpeed = 0.01f;
		}

		WaitInputReleaseTask->OnRelease.AddDynamic(this, &UPlayerAttackAbility::OnInputReleased);
		WaitInputReleaseTask->ReadyForActivation();
	}
}

void UPlayerAttackAbility::RestoreMovement()
{
	if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
	{
		// TODO: Change this to remove modifier when implemented.
		Character->GetCharacterMovement()->MaxWalkSpeed = DefaultMoveSpeed;
		Character->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;
	}
}

void UPlayerAttackAbility::OnInputReleased(float TimeHeld)
{
	check(EventAttackMontageTag.IsValid());

	if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
		Character->GetCharacterMovement()->DisableMovement();

	if (AttackMontage)
	{
		UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AttackMontage, 1.0f, NAME_None, false);
		if (MontageTask)
		{
			MontageTask->OnCompleted.AddDynamic(this, &UPlayerAttackAbility::RestoreMovement);
			MontageTask->OnInterrupted.AddDynamic(this, &UPlayerAttackAbility::RestoreMovement);
			MontageTask->OnCancelled.AddDynamic(this, &UPlayerAttackAbility::RestoreMovement);
			MontageTask->ReadyForActivation();
		}
	}

	UAbilityTask_WaitGameplayEvent* GameplayEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EventAttackMontageTag, nullptr, false, true);
	if (GameplayEventTask)
	{
		GameplayEventTask->EventReceived.AddDynamic(this, &UPlayerAttackAbility::OnGameplayEventReceived);
		GameplayEventTask->ReadyForActivation();
	}
}

void UPlayerAttackAbility::OnGameplayEventReceived(FGameplayEventData Payload)
{
	check(SpawnProjectileSocketTag.IsValid());
	const FVector SpawnLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + (GetAvatarActorFromActorInfo()->GetActorForwardVector() * 2.f);
	SpawnProjectile(SpawnLocation, SpawnProjectileSocketTag, true);
	RestoreMovement();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
