// Copyright Fabian Fröding 2024. All Right Reserved.

#include "ActorComponents/NaraHealthComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Characters/NaraCharacterBase.h"
#include "GASAttributeSets/NaraHealthSet.h"
#include "Kismet/GameplayStatics.h"

UNaraHealthComponent::UNaraHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	HealthSet = nullptr;
}

void UNaraHealthComponent::TakeDamage(FGameplayEffectSpecHandle GameplayEffectSpecHandle, AActor* DamageSource)
{
	if (IsInvulnerable())
		return;

	if (!IsAlive())
		return;

	UAbilitySystemComponent* OwningASC = HealthSet->GetOwningAbilitySystemComponent();
	if (OwningASC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s no ASC!!!"), *GetOwner()->GetFName().ToString());
		return;
	}

	const float HealthBefore = HealthSet->GetHealth();
	UE_LOG(LogTemp, Warning, TEXT("UNaraHealthComponent::TakeDamage: HealthBefore: %f"), HealthBefore);

	if (GameplayEffectSpecHandle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Valid GE!!!"), *GetOwner()->GetFName().ToString());
		OwningASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

		UE_LOG(LogTemp, Warning, TEXT("UNaraHealthComponent::TakeDamage: Health after apply GE: %f"), HealthSet->GetHealth());

		const float TrueDamageAmount = HealthBefore - FMath::Clamp(HealthSet->GetHealth(), 0.f, HealthSet->GetMaxHealth());

		UE_LOG(LogTemp, Warning, TEXT("UNaraHealthComponent::TakeDamage: Tru dmg amt: %f"), TrueDamageAmount);
		if (TrueDamageAmount > 0.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Broadcast!!!"), *GetOwner()->GetFName().ToString());
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
	return HealthSet->GetHealth() > 0.f;
}

bool UNaraHealthComponent::IsInvulnerable()
{
	if (InvincibilityFramesDuration > 0.f && UGameplayStatics::GetTimeSeconds(this) < InvincibilityFramesTime + InvincibilityFramesDuration)
		return true;

	return false;
}

void UNaraHealthComponent::HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, float OldValue, float NewValue)
{
	OnHealthChanged.Broadcast(this, OldValue, NewValue);
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

	InASC->AddSet<UNaraHealthSet>();
	HealthSet = InASC->GetSet<UNaraHealthSet>();

	// Register to listen for attribute changes.
	HealthSet->OnHealthChanged.AddUObject(this, &UNaraHealthComponent::HandleHealthChanged);
	HealthSet->OnMaxHealthChanged.AddUObject(this, &UNaraHealthComponent::HandleMaxHealthChanged);

	// Broadcast initial values.
	OnHealthChanged.Broadcast(this, HealthSet->GetHealth(), HealthSet->GetHealth());
	OnMaxHealthChanged.Broadcast(this, HealthSet->GetMaxHealth(), HealthSet->GetMaxHealth());
}

void UNaraHealthComponent::HandleDeath()
{
	if (HealthSet->GetHealth() <= 0.f)
		OnDie.Broadcast();
}
