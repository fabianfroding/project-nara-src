// Copyright Fabian Fröding 2024. All Right Reserved.

#include "AbilitySystemComponent.h"
#include "Characters/NaraCharacterBase.h"

#include "GASAttributeSets/NaraMovementSet.h"

void ANaraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	InitializeMovementSetWithAbilitySystem(AbilitySystemComponent);
}

void ANaraCharacterBase::InitAbilityActorInfo()
{

}

void ANaraCharacterBase::InitializeDefaultAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultAttributes);

	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultAttributes, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ANaraCharacterBase::InitializeMovementSetWithAbilitySystem(UAbilitySystemComponent* InASC)
{
	if (InASC == nullptr)
	{
		UE_LOG(LogTemp, Error,
			TEXT("ANaraCharacterBase::InitializeMovementSetWithAbilitySystem: Invalid ability system component. Movement attribute set will not be initialized!"));
		return;
	}

	InASC->AddSet<UNaraMovementSet>();
	MovementSet = InASC->GetSet<UNaraMovementSet>();
}

UAbilitySystemComponent* ANaraCharacterBase::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}
