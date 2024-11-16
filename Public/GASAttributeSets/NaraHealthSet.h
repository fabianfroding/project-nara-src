// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GASAttributeSets/NaraAttributeSet.h"

#include "NaraHealthSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class NARA_API UNaraHealthSet : public UNaraAttributeSet
{
	GENERATED_BODY()

private:
	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;

public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UNaraHealthSet, Health);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UNaraHealthSet, MaxHealth);

	mutable FNaraAttributeEvent OnHealthChanged;
	mutable FNaraAttributeEvent OnMaxHealthChanged;

public:
	UNaraHealthSet();

protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
};
