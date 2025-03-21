// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"

#include "NaraAttributeSet.generated.h"

class ACharacter;
struct FGameplayEffectSpec;

#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

public:
	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

// TStaticFuncPtr is generic to any signature chosen.
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

DECLARE_MULTICAST_DELEGATE_FourParams(FNaraAttributeEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/, float /*OldValue*/, float /*NewValue*/);

UCLASS()
class NARA_API UNaraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	/* Attributes */
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UNaraAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UNaraAttributeSet, MaxHealth);

	// NOTE: Mana in this project is used as an ambigious term for whatever resource the entity requires to use abilities etc.
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UNaraAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UNaraAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData ManaRegen;
	ATTRIBUTE_ACCESSORS(UNaraAttributeSet, ManaRegen);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UNaraAttributeSet, MoveSpeed);

	// TODO: Add cast time to allow faster player heal etc.

public:
	UNaraAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

protected:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	void Debuff(const FEffectProperties& Props);

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

	void SendHealthEvent(const FEffectProperties& Props);

private:
	void HandleHealthChanged(FEffectProperties& Props);
	void HandleManaChanged(FEffectProperties& Props);
	void HandleMoveSpeedChanged(AActor* TargetActor);
	
};
