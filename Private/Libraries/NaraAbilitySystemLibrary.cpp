// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Libraries/NaraAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Characters/NaraEnemyCharacter.h"
#include "Core/NaraGameMode.h"
#include "Core/NaraGameplayTags.h"
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

bool UNaraAbilitySystemLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle)
{
    if (const FNaraGameplayEffectContext* NaraEffectContext = static_cast<const FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
    {
        return NaraEffectContext->IsSuccessfulDebuff();
    }
    return false;
}

float UNaraAbilitySystemLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
    if (const FNaraGameplayEffectContext* NaraEffectContext = static_cast<const FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
    {
        return NaraEffectContext->GetDebuffDamage();
    }
    return 0.f;
}

float UNaraAbilitySystemLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle)
{
    if (const FNaraGameplayEffectContext* NaraEffectContext = static_cast<const FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
    {
        return NaraEffectContext->GetDebuffDuration();
    }
    return 0.f;
}

float UNaraAbilitySystemLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle)
{
    if (const FNaraGameplayEffectContext* NaraEffectContext = static_cast<const FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
    {
        return NaraEffectContext->GetDebuffFrequency();
    }
    return 0.f;
}

FGameplayTag UNaraAbilitySystemLibrary::GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle)
{
    if (const FNaraGameplayEffectContext* NaraEffectContext = static_cast<const FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
    {
        if (NaraEffectContext->GetDamageType().IsValid())
        {
            return *NaraEffectContext->GetDamageType();
        }
    }
    return FGameplayTag();
}

void UNaraAbilitySystemLibrary::SetIsSuccessfulDebuff(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bInSuccessfulDebuff)
{
    if (FNaraGameplayEffectContext* NaraEffectContext = static_cast<FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
    {
        NaraEffectContext->SetIsSuccessfulDebuff(bInSuccessfulDebuff);
    }
}

void UNaraAbilitySystemLibrary::SetDebuffDamage(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, float InDamage)
{
    if (FNaraGameplayEffectContext* NaraEffectContext = static_cast<FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
    {
        NaraEffectContext->SetDebuffDamage(InDamage);
    }
}

void UNaraAbilitySystemLibrary::SetDebuffDuration(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, float InDuration)
{
    if (FNaraGameplayEffectContext* NaraEffectContext = static_cast<FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
    {
        NaraEffectContext->SetDebuffDuration(InDuration);
    }
}

void UNaraAbilitySystemLibrary::SetDebuffFrequency(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, float InFrequency)
{
    if (FNaraGameplayEffectContext* NaraEffectContext = static_cast<FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
    {
        NaraEffectContext->SetDebuffFrequency(InFrequency);
    }
}

void UNaraAbilitySystemLibrary::SetDamageType(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType)
{
    if (FNaraGameplayEffectContext* NaraEffectContext = static_cast<FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
    {
        const TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
        NaraEffectContext->SetDamageType(DamageType);
    }
}

FVector UNaraAbilitySystemLibrary::GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle)
{
    if (const FNaraGameplayEffectContext* NaraEffectContext = static_cast<const FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
    {
        return NaraEffectContext->GetKnockbackForce();
    }
    return FVector::ZeroVector;
}

void UNaraAbilitySystemLibrary::SetKnockbackForce(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, const FVector& InForce)
{
    if (FNaraGameplayEffectContext* NaraEffectContext = static_cast<FNaraGameplayEffectContext*>(EffectContextHandle.Get()))
    {
        NaraEffectContext->SetKnockbackForce(InForce);
    }
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

FGameplayEffectContextHandle UNaraAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
    const FNaraGameplayTags& GameplayTags = FNaraGameplayTags::Get();
    const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();

    FGameplayEffectContextHandle EffectContexthandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
    EffectContexthandle.AddSourceObject(SourceAvatarActor);

    SetKnockbackForce(EffectContexthandle, DamageEffectParams.KnockbackForce);

    const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass, 1.f, EffectContexthandle);

    UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);
    UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Chance, DamageEffectParams.DebuffChance);
    UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Damage, DamageEffectParams.DebuffDamage);
    UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Duration, DamageEffectParams.DebuffDuration);
    UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Frequency, DamageEffectParams.DebuffFrequency);

    DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
    return EffectContexthandle;
}

TArray<FRotator> UNaraAbilitySystemLibrary::EvenlySpacedRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators)
{
    TArray<FRotator> Rotators;

    const FVector LeftOfSpread = Forward.RotateAngleAxis(-Spread / 2.f, Axis);
    if (NumRotators > 1)
    {
        const float DeltaSpread = Spread / (NumRotators - 1);
        for (int32 i = 0; i < NumRotators; i++)
        {
            const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
            Rotators.Add(Direction.Rotation());
        }
    }
    else
    {
        Rotators.Add(Forward.Rotation());
    }
    return Rotators;
}

TArray<FVector> UNaraAbilitySystemLibrary::EvenlyRotatedVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumVectors)
{
    TArray<FVector> Vectors;

    const FVector LeftOfSpread = Forward.RotateAngleAxis(-Spread / 2.f, Axis);
    if (NumVectors > 1)
    {
        const float DeltaSpread = Spread / (NumVectors - 1);
        for (int32 i = 0; i < NumVectors; i++)
        {
            const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
            Vectors.Add(Direction);
        }
    }
    else
    {
        Vectors.Add(Forward);
    }
    return Vectors;
}

void UNaraAbilitySystemLibrary::DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FGameplayEffectSpec& Spec, 
    FAggregatorEvaluateParameters EvaluationParameters, const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs)
{
    const FNaraGameplayTags& GameplayTags = FNaraGameplayTags::Get();

    // Determine if there was a successful debuff
    const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance, false, -1.f);

    float TargetDebuffResistance = 0.f;
    const FGameplayTag ResistanceTag; // TODO: Find tag associated with resistance to the debuff type.
    
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(InTagsToDefs[ResistanceTag], EvaluationParameters, TargetDebuffResistance);
    TargetDebuffResistance = FMath::Max<float>(TargetDebuffResistance, 0.f);
    
    const float EffectiveDebuffChance = SourceDebuffChance * (100 - TargetDebuffResistance) / 100.f;
    const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance;
    
    if (bDebuff)
    {
        FGameplayEffectContextHandle ContextHandle = Spec.GetContext();

        UNaraAbilitySystemLibrary::SetIsSuccessfulDebuff(ContextHandle, true);
        //UNaraAbilitySystemLibrary::SetDamageType(ContextHandle, DamageType); // TODO: Do we even need to set damage tpye of debuff?

        const float DebuffDamage = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage, false, -1.f);
        const float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration, false, -1.f);
        const float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency, false, -1.f);

        UNaraAbilitySystemLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
        UNaraAbilitySystemLibrary::SetDebuffDuration(ContextHandle, DebuffDuration);
        UNaraAbilitySystemLibrary::SetDebuffFrequency(ContextHandle, DebuffFrequency);
    }
}
