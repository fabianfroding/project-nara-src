// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "GameplayEffectTypes.h"

#include "NaraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FNaraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;

public:
	bool IsBlockedHit() const { return bIsBlockedHit; }
	bool IsCriticalHit() const { return bIsCriticalHit; }

	void SetIsBlockedHit(const bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetIsCriticalHit(const bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }

	/* Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FNaraGameplayEffectContext* Duplicate() const
	{
		FNaraGameplayEffectContext* NewContext = new FNaraGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/* Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

};

template<>
struct TStructOpsTypeTraits<FNaraGameplayEffectContext> : TStructOpsTypeTraitsBase2<FNaraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};
