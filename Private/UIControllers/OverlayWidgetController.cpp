// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UIControllers/OverlayWidgetController.h"

#include "Data/AbilityInfo.h"
#include "GAS/NaraAbilitySystemComponent.h"
#include "GAS/NaraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UNaraAttributeSet* NaraAttributeSet = Cast<UNaraAttributeSet>(AS);

	OnHealthChanged.Broadcast(NaraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(NaraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(NaraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(NaraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	UNaraAttributeSet* NaraAttributeSet = CastChecked<UNaraAttributeSet>(AS);
	ASC->GetGameplayAttributeValueChangeDelegate(NaraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(NaraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(NaraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(NaraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

	if (UNaraAbilitySystemComponent* NaraASC = Cast<UNaraAbilitySystemComponent>(ASC))
	{
		if (NaraASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(NaraASC);
		}
		else
		{
			NaraASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}

		NaraASC->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					// "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False.
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag("Message");
					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UNaraAbilitySystemComponent* NaraAbilitySystemComponent)
{
	// TODO: Get information about all given abilities, look up their Ability Info, and broadcast it to widgets.
	if (!NaraAbilitySystemComponent->bStartupAbilitiesGiven) 
		return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, NaraAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
	{
		//TODO need a way to figure out the ability tag for a given ability spec.
		/*FNaraAbilityInfo Info = AbilityInfo.Get()->FindAbilityInfoForTag(NaraAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = NaraAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);*/
	});
	NaraAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}
