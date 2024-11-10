// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"

#include "NaraAssetManager.generated.h"

UCLASS()
class NARA_API UNaraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static UNaraAssetManager* GetAssetManager();

	UFUNCTION(BlueprintPure)
	static UObject* LoadObjectFromSoftObjectPtr(TSoftObjectPtr<UObject> SoftObjectPtr);

	UFUNCTION(BlueprintPure)
	static UClass* LoadClassFromSoftClassPtr(TSoftClassPtr<UObject> SoftClassPtr);
	
};
