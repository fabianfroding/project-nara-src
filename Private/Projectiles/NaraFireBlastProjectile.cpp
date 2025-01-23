// Copyright Fabian Fröding 2025. All Right Reserved.

#include "Projectiles/NaraFireBlastProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Core/NaraGameplayTags.h"
#include "GameplayCueManager.h"
#include "Libraries/NaraAbilitySystemLibrary.h"

void ANaraFireBlastProjectile::BeginPlay()
{
	Super::BeginPlay();
	StartOutgoingTimeline();
}

void ANaraFireBlastProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValidOverlap(OtherActor)) return;
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
			UNaraAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
		}
	}
}

void ANaraFireBlastProjectile::OnHit()
{
	// NOTE: Example of how to use gameplay cues locally (The default behaviour triggers an RPC).
	if (GetOwner())
	{
		FGameplayCueParameters CueParams;
		CueParams.Location = GetActorLocation();
		UGameplayCueManager::ExecuteGameplayCue_NonReplicated(GetOwner(), FNaraGameplayTags::Get().GameplayCue_FireBlast, CueParams);
	}

	Super::OnHit();
}
