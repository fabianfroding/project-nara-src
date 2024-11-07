// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/Components/NaraHealthComponent.h"

#include "AbilitySystemComponent.h"
#include "GAS/AttributeSets/NaraHealthSet.h"

UNaraHealthComponent::UNaraHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNaraHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNaraHealthComponent::TakeDamage(FGameplayEffectSpecHandle GameplayEffectSpecHandle, AActor* DamageSource)
{
	//if (IsInvulnerable())
	//	return;

	if (!IsAlive())
		return;

	const float HealthBefore = HealthAttributeSet->GetHealth();

	if (GameplayEffectSpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

		//float TrueDamageAmount = HealthBefore - FMath::Clamp(HealthAttributeSet->GetHealth(), 0.f, HealthAttributeSet->GetMaxHealth());
		//if (TrueDamageAmount > 0.f)
		//{
			//PlayOnDamagedFeedback();
			//OnDamaged.Broadcast(TrueDamageAmount, DamageSource);
		//}

		/*if (InvulnerabilityFramesDuration > 0.f)
		{
			UWorld* World = GetWorld();
			if (IsValid(World))
			{
				SetInvulnerability(InvulnerabilityFramesKey, true);
				World->GetTimerManager().SetTimer(InvulnerabilityFramesTimer, this, &UNHealthComponent::ResetInvulnerabilityFrames, InvulnerabilityFramesDuration, false);
			}
		}*/

		HandleDeath();
	}
}

void UNaraHealthComponent::InitializeWithAbilitySystem(UAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error,
			TEXT("UNaraHealthComponent::InitializeWithAbilitySystem: Cannot initialize health component for owner [%s] with NULL ability system."),
			*GetNameSafe(Owner));
		return;
	}

	HealthAttributeSet = AbilitySystemComponent->GetSet<UNaraHealthSet>();
	if (!HealthAttributeSet)
	{
		UE_LOG(LogTemp, Error, 
			TEXT("UNaraHealthComponent::InitializeWithAbilitySystem: Cannot initialize health component for owner [%s] with NULL health set on the ability system."), 
			*GetNameSafe(Owner));
		return;
	}
}

bool UNaraHealthComponent::IsAlive() const
{
	return HealthAttributeSet->GetHealth() > 0.f;
}

void UNaraHealthComponent::HandleDeath()
{
	if (HealthAttributeSet->GetHealth() <= 0.f)
		OnDie.Broadcast();
}
