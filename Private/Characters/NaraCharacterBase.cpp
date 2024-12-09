// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Characters/NaraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/NaraAbilitySystemComponent.h"
#include "Nara/Nara.h"

ANaraCharacterBase::ANaraCharacterBase()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void ANaraCharacterBase::InitAbilityActorInfo() {}

void ANaraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultAttributes, 1.f);
}

void ANaraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);

	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

UAbilitySystemComponent* ANaraCharacterBase::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void ANaraCharacterBase::AddCharacterAbilities()
{
	UNaraAbilitySystemComponent* NaraASC = CastChecked<UNaraAbilitySystemComponent>(AbilitySystemComponent);
	NaraASC->AddCharacterAbilities(StartupAbilities);
}

FVector ANaraCharacterBase::GetCombatSocketLocation()
{
	if (IsValid(Weapon))
		return Weapon->GetSocketLocation(WeaponTipSocketName);

	UE_LOG(LogTemp, Warning, TEXT("ANaraCharacterBase::GetCombatSocketLocation: No valid Weapon in actor %s. Using GetActorLocation() instead!"), *GetFName().ToString());
	return GetActorLocation();
}

UAnimMontage* ANaraCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void ANaraCharacterBase::Die()
{
	if (Weapon != nullptr)
		Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	HandleDeath();
}

void ANaraCharacterBase::HandleDeath()
{
	// Ragdoll sequence
	if (Weapon != nullptr)
	{
		Weapon->SetSimulatePhysics(true);
		Weapon->SetEnableGravity(true);
		Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
