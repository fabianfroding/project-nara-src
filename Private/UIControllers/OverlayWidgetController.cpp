// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UIControllers/OverlayWidgetController.h"

#include "GAS/NaraAbilitySystemComponent.h"
#include "GASAttributeSets/NaraAttributeSet.h"

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
					const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
					GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, Msg);

					FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				}
			}
		);
	}
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
