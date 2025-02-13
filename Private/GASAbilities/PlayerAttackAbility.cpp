// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASAbilities/PlayerAttackAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!bHasProjectileReturned)
		return;

	if (!CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
		return;
	}

	if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
	{
		if (Character->GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
			return;
	}

	CachedASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	if (CachedASC)
	{
		if (AttackActiveEffectClass)
			AttackActiveEffectHandle = CachedASC->ApplyGameplayEffectToTarget(AttackActiveEffectClass->GetDefaultObject<UGameplayEffect>(), CachedASC);

		CachedASC->BlockAbilitiesWithTags(CustomBlockedAbilityTags);
	}
}

void UPlayerAttackAbility::RestoreMovement()
{
	if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
		Character->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;

	if (CachedASC && AttackActiveEffectHandle.IsValid())
		CachedASC->RemoveActiveGameplayEffect(AttackActiveEffectHandle);
}

void UPlayerAttackAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	check(EventAttackMontageTag.IsValid());

	//const float TimeHeld = UGameplayStatics::GetTimeSeconds(this) - StartTime; // If we want some modifier that allows charging up the attack.

	if (!bHasProjectileReturned)
		return;
	bHasProjectileReturned = false;

	if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
		Character->GetCharacterMovement()->DisableMovement();

	if (AttackMontage)
	{
		UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AttackMontage, 1.0f, NAME_None, false);
		if (MontageTask)
		{
			MontageTask->OnCompleted.AddUniqueDynamic(this, &UPlayerAttackAbility::RestoreMovement);
			MontageTask->OnInterrupted.AddUniqueDynamic(this, &UPlayerAttackAbility::RestoreMovement);
			MontageTask->OnCancelled.AddUniqueDynamic(this, &UPlayerAttackAbility::RestoreMovement);
			MontageTask->ReadyForActivation();
		}
	}

	UAbilityTask_WaitGameplayEvent* GameplayEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EventAttackMontageTag, nullptr, false, true);
	if (GameplayEventTask)
	{
		GameplayEventTask->EventReceived.AddUniqueDynamic(this, &UPlayerAttackAbility::OnGameplayEventReceived);
		GameplayEventTask->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* PlayerAttackEndTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, PlayerAttackEndTag, nullptr, false, true);
	if (PlayerAttackEndTask)
	{
		PlayerAttackEndTask->EventReceived.AddUniqueDynamic(this, &UPlayerAttackAbility::OnPlayerAttackEnd);
		PlayerAttackEndTask->ReadyForActivation();
	}
}

void UPlayerAttackAbility::OnGameplayEventReceived(FGameplayEventData Payload)
{
	check(SpawnProjectileSocketTag.IsValid());
	const FVector SpawnLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + (GetAvatarActorFromActorInfo()->GetActorForwardVector() * 1000.f);
	SpawnProjectile(SpawnLocation, SpawnProjectileSocketTag, false);

	if (CachedASC)
		CachedASC->UnBlockAbilitiesWithTags(CustomBlockedAbilityTags);

	RestoreMovement();
}

void UPlayerAttackAbility::OnPlayerAttackEnd(FGameplayEventData Payload)
{
	bHasProjectileReturned = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
