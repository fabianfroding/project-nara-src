// Copyright Fabian Fr�ding 2024. All Right Reserved.

#include "Characters/NaraEnemyCharacter.h"

#include "AI/NaraAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Core/NaraCombatManager.h"
#include "Core/NaraGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/NaraAbilitySystemComponent.h"
#include "GAS/NaraAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

ANaraEnemyCharacter::ANaraEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UNaraAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UNaraAttributeSet>("AttributeSet");

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	if (!EnemyDeathTag.IsValid())
		EnemyDeathTag = FNaraGameplayTags::Get().CombatEvent_EnemyDeath;
}

void ANaraEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (NaraAIController = Cast<ANaraAIController>(NewController))
	{
		NaraAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		NaraAIController->RunBehaviorTree(BehaviorTree);

		NaraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);

		NaraAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), bIsRanged);
	}
}

void ANaraEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	GiveStartupAbilities();

	AbilitySystemComponent->RegisterGameplayTagEvent(FNaraGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this, &ANaraEnemyCharacter::HitReactTagChanged);

	UNaraCombatManager::Get()->RegisterEnemy(this);
}

void ANaraEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UNaraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttributes();
	OnAscRegistered.Broadcast(AbilitySystemComponent);
	AbilitySystemComponent->RegisterGameplayTagEvent(FNaraGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this, &ANaraEnemyCharacter::StunTagChanged);
}

void ANaraEnemyCharacter::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	Super::StunTagChanged(CallbackTag, NewCount);
	if (NaraAIController && NaraAIController->GetBlackboardComponent())
	{
		NaraAIController->GetBlackboardComponent()->SetValueAsBool(FName("Stunned"), bIsStunned);
	}
}

void ANaraEnemyCharacter::Destroyed()
{
	if (OnDestroySFX)
		UGameplayStatics::PlaySoundAtLocation(this, OnDestroySFX, GetActorLocation(), FRotator::ZeroRotator);

	if (OnDestroyVFX)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, OnDestroyVFX, GetActorLocation());

	Super::Destroyed();
}

void ANaraEnemyCharacter::GiveStartupAbilities()
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void ANaraEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	if (NaraAIController && NaraAIController->GetBlackboardComponent())
	{
		NaraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}

void ANaraEnemyCharacter::Die()
{
	SetLifeSpan(DeathLifeSpan);
	
	if (NaraAIController)
		NaraAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"), true);

	UNaraCombatManager::Get()->EnemyDied(this, EnemyDeathTag);

	SpawnLoot();
	Super::Die();
}

void ANaraEnemyCharacter::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ANaraEnemyCharacter::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}
