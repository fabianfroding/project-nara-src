// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Libraries/NaraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Characters/NaraEnemyCharacter.h"
#include "Core/NaraGameMode.h"
#include "Engine/OverlapResult.h"
#include "Interfaces/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
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

void UNaraAbilitySystemLibrary::GetAlivePlayersInRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, 
    const TArray<AActor*> ActorsToIgnore, const float Radius, const FVector& SphereOrigin)
{
    FCollisionQueryParams SphereParams;
    SphereParams.AddIgnoredActors(ActorsToIgnore);

    if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
    {
        TArray<FOverlapResult> Overlaps;
        World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, 
            FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
        for (FOverlapResult& Overlap : Overlaps)
        {
            if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
            {
                OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
            }
        }
    }
}

bool UNaraAbilitySystemLibrary::AreActorsEnemies(const AActor* ActorA, const AActor* ActorB)
{
    const bool bBothArePlayers = ActorA->ActorHasTag(FName("Player")) && ActorB->ActorHasTag(FName("Player"));
    const bool bBothAreEnemies = ActorA->ActorHasTag(FName("Enemy")) && ActorB->ActorHasTag(FName("Enemy"));
    const bool bAreAllies = bBothArePlayers || bBothAreEnemies;
    return !bAreAllies;
}
