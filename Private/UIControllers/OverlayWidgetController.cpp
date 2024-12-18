// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UIControllers/OverlayWidgetController.h"

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
