// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASAbilities/PlayerAttackAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void UPlayerAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
		return;
	}

	CachedASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	if (CachedASC && AttackActiveEffectClass)
		AttackActiveEffectHandle = CachedASC->ApplyGameplayEffectToTarget(AttackActiveEffectClass->GetDefaultObject<UGameplayEffect>(), CachedASC);

	//StartTime = UGameplayStatics::GetTimeSeconds(this);
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

	//const float TimeHeld = UGameplayStatics::GetTimeSeconds(this) - StartTime;

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
	RestoreMovement();
}

void UPlayerAttackAbility::OnPlayerAttackEnd(FGameplayEventData Payload)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
