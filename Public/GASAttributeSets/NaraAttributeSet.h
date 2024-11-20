// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"

#include "NaraAttributeSet.generated.h"

class UAbilitySystemComponent;
struct FGameplayEffectSpec;

DECLARE_MULTICAST_DELEGATE_FourParams(FNaraAttributeEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/, float /*OldValue*/, float /*NewValue*/);

UCLASS()
class NARA_API UNaraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
};
