// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GASAttributeSets/NaraAttributeSet.h"

#include "NaraHealthSet.generated.h"

UCLASS()
class NARA_API UNaraHealthSet : public UNaraAttributeSet
{
	GENERATED_BODY()

private:
	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;

public:
	mutable FNaraAttributeEvent OnHealthChanged;
	mutable FNaraAttributeEvent OnMaxHealthChanged;

public:
	UNaraHealthSet();

protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
};
