// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASAttributeSets/NaraHealthSet.h"

UNaraHealthSet::UNaraHealthSet()
{
	InitMaxHealth(3.f);
	InitHealth(3.f);
}

void UNaraHealthSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// NOTE: Not the best place to do clamping since other calculations are done efter PreAttributeChange, which can still modify the new value.
	NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());

	HealthBeforeAttributeChange = GetHealth();
	MaxHealthBeforeAttributeChange = GetMaxHealth();
}

void UNaraHealthSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (GetMaxHealth() != MaxHealthBeforeAttributeChange)
	{
		OnMaxHealthChanged.Broadcast(nullptr, nullptr, MaxHealthBeforeAttributeChange, GetMaxHealth());
	}

	if (GetHealth() != HealthBeforeAttributeChange)
	{
		UE_LOG(LogTemp, Display, TEXT("UNaraHealthSet::PostAttributeChange: OnHealthChanged.Broadcast"));
		OnHealthChanged.Broadcast(nullptr, nullptr, HealthBeforeAttributeChange, GetHealth());
	}
}

void UNaraHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	/*if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		UE_LOG(LogTemp, Display, TEXT("UNaraHealthSet::PostGameplayEffectExecute: Health from GetHealth: %f"), GetHealth());
		UE_LOG(LogTemp, Display, TEXT("UNaraHealthSet::PostGameplayEffectExecute: Magnitude: %f"), Data.EvaluatedData.Magnitude);
	}*/

	FEffectProperties Props;
	SetEffectProperties(Data, Props);
}
