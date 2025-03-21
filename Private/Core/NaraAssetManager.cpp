// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Core/NaraAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "Core/NaraGameplayTags.h"
#include "Kismet/KismetSystemLibrary.h"

void UNaraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FNaraGameplayTags::InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData(); // Required to use Target Data type in GAS.
}

UNaraAssetManager& UNaraAssetManager::Get()
{
	check(GEngine);
	UNaraAssetManager* NaraAssetManager = Cast<UNaraAssetManager>(GEngine->AssetManager);
	return *NaraAssetManager;
}

UClass* UNaraAssetManager::LoadClassFromSoftClassPtr(TSoftClassPtr<UObject> SoftClassPtr)
{
	if (!UKismetSystemLibrary::IsValidSoftClassReference(SoftClassPtr))
	{
		UE_LOG(LogTemp, Error, TEXT("UNaraAssetManager::LoadClassFromSoftClassPtr: Invalid soft pointer to a class!"));
		return nullptr;
	}

	UClass* Class = SoftClassPtr.Get();
	if (Class)
	{
		return Class;
	}

	Class = SoftClassPtr.LoadSynchronous();
	if (Class)
	{
		UE_LOG(LogTemp, Warning, TEXT("UNAssetManager::LoadClassFromSoftClassPtr: The class %s was loaded synchronously."), *SoftClassPtr.ToSoftObjectPath().ToString());
		return Class;
	}

	UE_LOG(LogTemp, Error, TEXT("UNaraAssetManager::LoadClassFromSoftClassPtr: Failed to load asset form soft class pointer!"));
	return nullptr;
}

UObject* UNaraAssetManager::LoadObjectFromSoftObjectPtr(TSoftObjectPtr<UObject> SoftObjectPtr)
{
	if (!UKismetSystemLibrary::IsValidSoftObjectReference(SoftObjectPtr))
	{
		UE_LOG(LogTemp, Error, TEXT("UNaraAssetManager::LoadObjectFromSoftObjectPtr: Invalid soft pointer to an object!"));
		return nullptr;
	}

	UObject* Object = SoftObjectPtr.Get();
	if (Object)
	{
		return Object;
	}

	Object = SoftObjectPtr.LoadSynchronous();
	if (Object)
	{
		UE_LOG(LogTemp, Warning, TEXT("UNAssetManager::LoadObjectFromSoftObjectPtr: The object %s was synchronously."), *SoftObjectPtr.ToSoftObjectPath().ToString());
		return Object;
	}

	UE_LOG(LogTemp, Error, TEXT("UNaraAssetManager::LoadObjectFromSoftObjectPtr: Failed to load asset form soft object pointer!"));
	return nullptr;
}
