// Copyright Fabian Fröding 2024. All Right Reserved.

#include "ActorComponents/NaraHealthComponent.h"

#include "AbilitySystemComponent.h"
#include "GASAttributeSets/NaraHealthSet.h"
#include <Kismet/GameplayStatics.h>

UNaraHealthComponent::UNaraHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	HealthAttributeSet = CreateDefaultSubobject<UNaraHealthSet>("HealthAttributeSet");
}

void UNaraHealthComponent::TakeDamage(FGameplayEffectSpecHandle GameplayEffectSpecHandle, AActor* DamageSource)
{
	if (IsInvulnerable())
		return;

	if (!IsAlive())
		return;

	UAbilitySystemComponent* OwningASC = HealthAttributeSet->GetOwningAbilitySystemComponent();
	if (OwningASC == nullptr)
		return;

	const float HealthBefore = HealthAttributeSet->GetHealth();

	if (GameplayEffectSpecHandle.IsValid())
	{
		OwningASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

		float TrueDamageAmount = HealthBefore - FMath::Clamp(HealthAttributeSet->GetHealth(), 0.f, HealthAttributeSet->GetMaxHealth());
		if (TrueDamageAmount > 0.f)
		{
			//PlayOnDamagedFeedback();
			OnDamaged.Broadcast();
		}

		if (InvincibilityFramesDuration > 0.f)
			InvincibilityFramesTime = UGameplayStatics::GetTimeSeconds(this);

		HandleDeath();
	}
}

bool UNaraHealthComponent::IsAlive() const
{
	return HealthAttributeSet->GetHealth() > 0.f;
}

bool UNaraHealthComponent::IsInvulnerable()
{
	if (InvincibilityFramesDuration > 0.f && UGameplayStatics::GetTimeSeconds(this) < InvincibilityFramesTime + InvincibilityFramesDuration)
		return true;

	return false;
}

void UNaraHealthComponent::HandleDeath()
{
	if (HealthAttributeSet->GetHealth() <= 0.f)
		OnDie.Broadcast();
}
