// Copyright Fabian Fröding 2024. All Right Reserved.

#include "ActorComponents/NaraHealthComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Characters/NaraCharacterBase.h"
#include "GAS/NaraAttributeSet.h"
#include "Kismet/GameplayStatics.h"

UNaraHealthComponent::UNaraHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	AttributeSet = nullptr;
}

void UNaraHealthComponent::TakeDamage(FGameplayEffectSpecHandle GameplayEffectSpecHandle, AActor* DamageSource)
{
	
}

bool UNaraHealthComponent::IsAlive() const
{
	return AttributeSet->GetHealth() > 0.f;
}

bool UNaraHealthComponent::IsInvulnerable()
{
	if (InvincibilityFramesDuration > 0.f && UGameplayStatics::GetTimeSeconds(this) < InvincibilityFramesTime + InvincibilityFramesDuration)
		return true;

	return false;
}

void UNaraHealthComponent::HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, float OldValue, float NewValue)
{
	// TODO: These should be handled by GAS tags.
	//if (IsInvulnerable())
		//return;
	//if (!IsAlive())
		//return;

	const float TrueDamageAmount = OldValue - FMath::Clamp(NewValue, 0.f, AttributeSet->GetMaxHealth());
	if (TrueDamageAmount > 0.f)
	{
		//PlayOnDamagedFeedback();
		UE_LOG(LogTemp, Display, TEXT("UNaraHealthComponent::HandleHealthChanged: Broadcast OnDamaged!"));
		OnDamaged.Broadcast();
	}

	// TODO: This no longer works after GAS implementation. Should arguably be handled by a GAS duration effect that apply a tag.
	if (InvincibilityFramesDuration > 0.f)
		InvincibilityFramesTime = UGameplayStatics::GetTimeSeconds(this);

	OnHealthChanged.Broadcast(this, OldValue, NewValue);

	HandleDeath();
}

void UNaraHealthComponent::HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, float OldValue, float NewValue)
{
	OnMaxHealthChanged.Broadcast(this, OldValue, NewValue);
}

void UNaraHealthComponent::InitializeWithAbilitySystem(UAbilitySystemComponent* InASC)
{
	if (InASC == nullptr)
	{
		UE_LOG(LogTemp, Error, 
			TEXT("UNaraHealthComponent::InitializeWithAbilitySystem: Invalid ability system component. Health attribute set will not be initialized!"));
		return;
	}

	InASC->AddSet<UNaraAttributeSet>();
	AttributeSet = InASC->GetSet<UNaraAttributeSet>();

	// Register to listen for attribute changes.
	//AttributeSet->OnHealthChanged.AddUObject(this, &UNaraHealthComponent::HandleHealthChanged);
	//AttributeSet->OnMaxHealthChanged.AddUObject(this, &UNaraHealthComponent::HandleMaxHealthChanged);

	// Broadcast initial values.
	OnHealthChanged.Broadcast(this, AttributeSet->GetHealth(), AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(this, AttributeSet->GetMaxHealth(), AttributeSet->GetMaxHealth());
}

void UNaraHealthComponent::HandleDeath()
{
	if (AttributeSet->GetHealth() <= 0.f)
		OnDie.Broadcast();
}
