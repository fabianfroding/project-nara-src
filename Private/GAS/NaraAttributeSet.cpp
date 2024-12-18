// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GAS/NaraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Core/NaraGameplayTags.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayEffectExtension.h"
#include "Interfaces/CombatInterface.h"
#include "Libraries/NaraAbilitySystemLibrary.h"

UNaraAttributeSet::UNaraAttributeSet()
{
	const FNaraGameplayTags& GameplayTags = FNaraGameplayTags::Get();

	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetManaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetMaxManaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetAttackPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetAttackSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetMoveSpeedAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Fire, GetFireResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Lighting, GetLightingResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Arcane, GetArcaneResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Physical, GetPhysicalResistanceAttribute);
}

void UNaraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// NOTE: Clamps whats returned from querying the modifier. For really clamping the attribute, use PostGameplayEffectExecute.
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}

	if (Attribute == GetMoveSpeedAttribute())
	{
		ACharacter* Character = Cast<ACharacter>(GetOwningAbilitySystemComponent()->GetAvatarActor());
		if (Character && Character->GetCharacterMovement())
		{
			Character->GetCharacterMovement()->MaxWalkSpeed = NewValue;
		}
	}
}

void UNaraAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHealthAttribute() && OldValue != NewValue)
	{
		//OnMaxHealthChanged.Broadcast(nullptr, nullptr, OldValue, NewValue);
	}

	if (Attribute == GetHealthAttribute() && OldValue != NewValue)
	{
		//OnHealthChanged.Broadcast(nullptr, nullptr, OldValue, NewValue);
	}
}

void UNaraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("UNaraAttributeSet::PostGameplayEffectExecute: Change health on %s, Health: %f"), *Props.TargetAvatarActor->GetFName().ToString(), GetHealth());
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.f;
			if (bFatal)
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
				if (CombatInterface)
					CombatInterface->Die();
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FNaraGameplayTags::Get().Effects_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer, false);
			}

			if (UNaraAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle))
			{
				// Do stuff if blocked etc.
			}
		}
	}
}

void UNaraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController != nullptr)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}
