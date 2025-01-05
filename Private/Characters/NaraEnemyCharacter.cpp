// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Characters/NaraEnemyCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/NaraAIController.h"
#include "Core/NaraGameplayTags.h"
#include "GAS/NaraAbilitySystemComponent.h"
#include "GAS/NaraAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	BaseWalkSpeed = 125.f;
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
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	GiveStartupAbilities();

	UNaraAttributeSet* NaraAS = CastChecked<UNaraAttributeSet>(AttributeSet);
	if (NaraAS)
	{
		// NOTE: For some reason we can't use FOnAttributeChangeData in header files, 
		// so we need to use a lambda here in the .cpp instead of definiing and using a function in the header file.
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NaraAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->RegisterGameplayTagEvent(FNaraGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this, &ANaraEnemyCharacter::HitReactTagChanged);
		
		OnHealthChanged.Broadcast(NaraAS->GetHealth());
	}
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
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (NaraAIController && NaraAIController->GetBlackboardComponent())
	{
		NaraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}

void ANaraEnemyCharacter::Die()
{
	SetLifeSpan(DeathLifeSpan); // TODO: On lifespan expire, create poof effect to make the enemy disappear.
	
	if (NaraAIController)
		NaraAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"), true);

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
