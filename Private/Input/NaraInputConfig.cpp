// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Input/NaraInputConfig.h"

#include "InputAction.h"

const UInputAction* UNaraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FNaraInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.MatchesTagExact(InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("UNaraInputConfig::FindAbilityInputActionForTag: Couldn't find InputAction for tag [%s] on InputConfig [%s]!"), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
