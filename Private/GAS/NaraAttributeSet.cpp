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
#include "Types/NaraAbilityTypes.h"

UNaraAttributeSet::UNaraAttributeSet()
{
	const FNaraGameplayTags& GameplayTags = FNaraGameplayTags::Get();

	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetManaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetMaxManaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetMoveSpeedAttribute);
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
}

void UNaraAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMoveSpeedAttribute())
		HandleMoveSpeedChanged(GetOwningAbilitySystemComponent()->GetAvatarActor());
}

void UNaraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// NOTE: PostGameplayEffectExecute does not trigger for effect with Duration Policy set to Infinite. (Not sure about HasDuration).

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		HandleHealthChanged(Props);

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
		HandleManaChanged(Props);

	if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
		HandleMoveSpeedChanged(Props.TargetAvatarActor);
}

void UNaraAttributeSet::Debuff(const FEffectProperties& Props)
{
	const FNaraGameplayTags& GameplayTags = FNaraGameplayTags::Get();
	FGameplayEffectContextHandle EffectContext = Props.SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(Props.SourceAvatarActor);

	const FGameplayTag DamageType = UNaraAbilitySystemLibrary::GetDamageType(Props.EffectContextHandle);
	const float DebuffDamage = UNaraAbilitySystemLibrary::GetDebuffDamage(Props.EffectContextHandle);
	const float DebuffDuration = UNaraAbilitySystemLibrary::GetDebuffDuration(Props.EffectContextHandle);
	const float DebuffFrequency = UNaraAbilitySystemLibrary::GetDebuffFrequency(Props.EffectContextHandle);

	FString DebuffName = FString::Printf(TEXT("DynamicDebuff_%s"), *DamageType.ToString());
	UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage(), FName(DebuffName));

	Effect->DurationPolicy = EGameplayEffectDurationType::HasDuration;
	Effect->Period = DebuffFrequency;
	Effect->DurationMagnitude = FScalableFloat(DebuffDuration);

	// TODO: Apply the debuff tag here, not based on any damage type.
	//Effect->InheritableOwnedTagsContainer.AddTag(GameplayTags.DamageTypesToDebuffs[DamageType]);
	
	// If debuff tag is stun debuff tag, then disable input like so:
	//Effect->InheritableOwnedTagsContainer.AddTag(GameplayTags.Player_Block_InputHeld);
	//Effect->InheritableOwnedTagsContainer.AddTag(GameplayTags.Player_Block_InputPressed);
	//Effect->InheritableOwnedTagsContainer.AddTag(GameplayTags.Player_Block_InputReleased);

	Effect->StackingType = EGameplayEffectStackingType::AggregateBySource;
	Effect->StackLimitCount = 1;

	const int32 Index = Effect->Modifiers.Num();
	Effect->Modifiers.Add(FGameplayModifierInfo());
	FGameplayModifierInfo& ModifierInfo = Effect->Modifiers[Index];

	ModifierInfo.ModifierMagnitude = FScalableFloat(DebuffDamage);
	ModifierInfo.ModifierOp = EGameplayModOp::Additive;

	if (FGameplayEffectSpec* MutableSpec = new FGameplayEffectSpec(Effect, EffectContext, 1.f))
	{
		FNaraGameplayEffectContext* NaraContext = static_cast<FNaraGameplayEffectContext*>(MutableSpec->GetContext().Get());
		TSharedPtr<FGameplayTag> DebuffDamageType = MakeShareable(new FGameplayTag(DamageType));
		NaraContext->SetDamageType(DebuffDamageType);

		Props.TargetASC->ApplyGameplayEffectSpecToSelf(*MutableSpec);
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

void UNaraAttributeSet::SendHealthEvent(const FEffectProperties& Props)
{
	// Example of sending attribute event.
	const FNaraGameplayTags& GameplayTags = FNaraGameplayTags::Get();
	FGameplayEventData Payload;
	Payload.EventTag = GameplayTags.Attributes_Health;

	UAbilitySystemComponent* ASC = Props.TargetCharacter->FindComponentByClass<UAbilitySystemComponent>();
	if (ASC)
	{
		const UNaraAttributeSet* NaraAttributeSet = ASC->GetSet<UNaraAttributeSet>();
		if (NaraAttributeSet)
		{
			float HealthValue = NaraAttributeSet->GetHealth();
			Payload.EventMagnitude = HealthValue;
		}
	}

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Props.SourceCharacter, GameplayTags.Attributes_Health, Payload);
}

void UNaraAttributeSet::HandleHealthChanged(FEffectProperties& Props)
{
	if (UNaraAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle))
	{
		return;
	}

	SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
	if (CombatInterface && GetHealth() < GetMaxHealth())
	{
		// TODO: This should only execute once.
		CombatInterface->StartFlash();
	}

	if (GetHealth() <= 0.f)
	{
		if (CombatInterface)
		{
			// TODO: This should only execute once.
			CombatInterface->Die();
		}
	}
	else
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FNaraGameplayTags::Get().Effects_HitReact);
		Props.TargetASC->TryActivateAbilitiesByTag(TagContainer, false);

		const FVector& KnockbackForce = UNaraAbilitySystemLibrary::GetKnockbackForce(Props.EffectContextHandle);
		if (!KnockbackForce.IsNearlyZero(1.f))
		{
			Props.TargetCharacter->LaunchCharacter(KnockbackForce, true, true);
		}

		if (UNaraAbilitySystemLibrary::IsSuccessfulDebuff(Props.EffectContextHandle))
		{
			Debuff(Props);
		}
	}

	// Example of where to call FNaraAttributeEvent for health.
}

void UNaraAttributeSet::HandleManaChanged(FEffectProperties& Props)
{
	SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
}

void UNaraAttributeSet::HandleMoveSpeedChanged(AActor* TargetActor)
{
	if (ACharacter* Character = Cast<ACharacter>(TargetActor))
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
	}
}
