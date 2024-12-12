// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Libraries/NaraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Core/NaraGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/NaraEnemyCharacter.h"
#include "Player/NaraPlayerState.h"
#include "Types/NaraAbilityTypes.h"
#include "UI/NaraHUD.h"
#include "UIControllers/NaraWidgetController.h"

UOverlayWidgetController* UNaraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
    {
        if (ANaraHUD* NaraHUD = Cast<ANaraHUD>(PC->GetHUD()))
        {
            ANaraPlayerState* PS = PC->GetPlayerState<ANaraPlayerState>();
            UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
            UAttributeSet* AS = PS->GetAttributeSet();
            const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
            return NaraHUD->GetOverlayWidgetController(WidgetControllerParams);
        }
    }

    return nullptr;
}

void UNaraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
    ANaraGameMode* NaraGameMode = Cast<ANaraGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
    if (NaraGameMode == nullptr)
        return;

    // TODO: This function is incomplete.
}

void UNaraAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
    ANaraGameMode* NaraGameMode = Cast<ANaraGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
    if (NaraGameMode == nullptr)
        return;

    // TODO: This function is incomplete.
}

bool UNaraAbilitySystemLibrary::IsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle)
{
    if (const FNaraGameplayEffectContext* NaraEffectContext = static_cast<const FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
        return NaraEffectContext->IsBlockedHit();
    return false;
}

void UNaraAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
    if (FNaraGameplayEffectContext* NaraEffectContext = static_cast<FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
        NaraEffectContext->SetIsBlockedHit(bInIsBlockedHit);
}

bool UNaraAbilitySystemLibrary::IsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle)
{
    if (const FNaraGameplayEffectContext* NaraEffectContext = static_cast<const FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
        return NaraEffectContext->IsCriticalHit();
    return false;
}

void UNaraAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
    if (FNaraGameplayEffectContext* NaraEffectContext = static_cast<FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
        NaraEffectContext->SetIsCriticalHit(bInIsCriticalHit);
}
