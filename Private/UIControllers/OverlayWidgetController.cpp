// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UIControllers/OverlayWidgetController.h"

#include "GAS/NaraAbilitySystemComponent.h"

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	if (UNaraAbilitySystemComponent* NaraASC = Cast<UNaraAbilitySystemComponent>(ASC))
	{
		NaraASC->EffectAssetTags.AddLambda(
			[](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
					GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, Msg);
				}
			}
		);
	}
}
