// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Characters/NaraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core/NaraGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/NaraAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Nara/Nara.h"
#include "Niagara/DebuffNiagaraComponent.h"

ANaraCharacterBase::ANaraCharacterBase()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->bRenderCustomDepth = true;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	StunDebuffComponent = CreateDefaultSubobject<UDebuffNiagaraComponent>("StunDebuffComponent");
	StunDebuffComponent->SetupAttachment(GetRootComponent());
	StunDebuffComponent->DebuffTag = FNaraGameplayTags::Get().Debuff_Stun;
}

float ANaraCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// For custom on damage taken logic needed for NaraCharacters, define that here and hook up to own damage system.
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ANaraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	FlashHandler.Initialize(this);
}

int32 ANaraCharacterBase::GetMinionCount_Implementation()
{
	return MinionCount;
}

void ANaraCharacterBase::IncrementMinionCount_Implementation(int32 Amount)
{
	MinionCount += Amount;
}

FOnASCRegistered& ANaraCharacterBase::GetOnASCRegisteredDelegate()
{
	return OnAscRegistered;
}

USkeletalMeshComponent* ANaraCharacterBase::GetWeapon_Implementation()
{
	return Weapon;
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
	NaraASC->AddCharacterPassiveAbilities(StartupPassiveAbilities);
}

FVector ANaraCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& SocketTag)
{
	const FNaraGameplayTags& GameplayTags = FNaraGameplayTags::Get();
	if (IsValid(Weapon) && SocketTag.MatchesTagExact(GameplayTags.CombatSocket_Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}

	if (SocketTag.MatchesTagExact(GameplayTags.CombatSocket_HandLeft))
	{
		return GetMesh()->GetSocketLocation(UnarmedLeftSocketName);
	}

	if (SocketTag.MatchesTagExact(GameplayTags.CombatSocket_HandRight))
	{
		return GetMesh()->GetSocketLocation(UnarmedRightSocketName);
	}

	if (SocketTag.MatchesTagExact(GameplayTags.CombatSocket_Tail))
	{
		return GetMesh()->GetSocketLocation(TailSocketName);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("ANaraCharacterBase::GetCombatSocketLocation: No valid Weapon in actor %s. Using GetActorLocation() instead!"), *GetFName().ToString());
	return GetActorLocation();
}

bool ANaraCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* ANaraCharacterBase::GetAvatar_Implementation()
{
	return this;
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

void ANaraCharacterBase::StartFlash()
{
	FlashHandler.StartFlash(GetWorld());
}

FOnDeathSignature& ANaraCharacterBase::GetOnDeathDelegate()
{
	return OnDeathDelegate;
}

TArray<FTaggedMontage> ANaraCharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

UNiagaraSystem* ANaraCharacterBase::GetHurtVFX_Implementation()
{
	return HurtVFX;
}

FTaggedMontage ANaraCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag == MontageTag)
			return TaggedMontage;
	}
	return FTaggedMontage();
}

void ANaraCharacterBase::HandleDeath()
{
	UGameplayStatics::PlaySoundAtLocation(this, DeathSFX, GetActorLocation());

	// Ragdoll sequence. TODO: Remove when using assets with death animations.
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

	bDead = true;
	StunDebuffComponent->Deactivate();
	OnDeathDelegate.Broadcast(this);
}

void ANaraCharacterBase::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsStunned = NewCount > 0;
}
