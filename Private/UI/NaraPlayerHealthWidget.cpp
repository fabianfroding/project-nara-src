// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UI/NaraPlayerHealthWidget.h"

#include "AbilitySystemComponent.h"
#include "ActorComponents/NaraHealthComponent.h"
#include "GASAttributeSets/NaraHealthSet.h"
#include "UI/NaraPlayerHealthIconWidget.h"

void UNaraPlayerHealthWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CachedHealthComponent = UNaraHealthComponent::FindHealthComponent(GetOwningPlayerPawn());
	if (CachedHealthComponent == nullptr)
		return;

	CachedHealthComponent->OnHealthChanged.AddUniqueDynamic(this, &UNaraPlayerHealthWidget::HandleHealthChanged);
	CachedHealthComponent->OnMaxHealthChanged.AddUniqueDynamic(this, &UNaraPlayerHealthWidget::HandleMaxHealthChanged);
}

UUniformGridPanel* UNaraPlayerHealthWidget::GetHealthIconContainer_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("UNaraPlayerHealthWidget::GetUniformGridPanel_Implementation: No implementation defined!"));
	return nullptr;
}

void UNaraPlayerHealthWidget::HandleHealthChanged(UNaraHealthComponent* HealthComponent, float OldValue, float NewValue)
{
	UE_LOG(LogTemp, Display, TEXT("UNaraPlayerHealthWidget::HandleHealthChanged"));
	if (CachedHealthComponent == nullptr)
		return;

	UUniformGridPanel* HealthIconContainer = GetHealthIconContainer();
	if (HealthIconContainer == nullptr)
		return;

	TArray<UWidget*> ContainerChildren = HealthIconContainer->GetAllChildren();

	const UNaraHealthSet* HealthSet = CachedHealthComponent->GetHealthSet();
	if (HealthSet == nullptr)
		return;

	const float MaxHealth = HealthSet->GetMaxHealth();
	const float CurrentHealth = HealthSet->GetHealth();

	for (int32 i = 1; i <= MaxHealth; i++)
	{
		UE_LOG(LogTemp, Display, TEXT("UNaraPlayerHealthWidget::HandleHealthChanged: %d!"), i);
		if (!ContainerChildren.IsValidIndex(i - 1))
			continue;

		UE_LOG(LogTemp, Display, TEXT("UNaraPlayerHealthWidget::HandleHealthChanged: B!"));
		UNaraPlayerHealthIconWidget* HealthIconWidget = Cast<UNaraPlayerHealthIconWidget>(ContainerChildren[i - 1]);
		if (!HealthIconWidget)
			continue;

		UE_LOG(LogTemp, Display, TEXT("UNaraPlayerHealthWidget::HandleHealthChanged: C!"));
		HealthIconWidget->UpdateIconState(i <= CurrentHealth);
	}
}

void UNaraPlayerHealthWidget::HandleMaxHealthChanged(UNaraHealthComponent* HealthComponent, float OldValue, float NewValue)
{
	if (!ContainerIconClass)
	{
		UE_LOG(LogTemp, Error, TEXT("UNaraPlayerHealthWidget::NativeConstruct: ContainerIconClass is not set!"));
		return;
	}

	if (UUniformGridPanel* HealthIconContainer = GetHealthIconContainer())
	{
		HealthIconContainer->ClearChildren();

		const UNaraHealthSet* HealthSet = CachedHealthComponent->GetHealthSet();
		if (HealthSet != nullptr)
		{
			for (int32 i = 1; i <= HealthSet->GetMaxHealth(); i++)
			{
				UNaraPlayerHealthIconWidget* HealthIcon = CreateWidget<UNaraPlayerHealthIconWidget>(this, ContainerIconClass);
				if (HealthIcon != nullptr)
					UUniformGridSlot* GridSlot = HealthIconContainer->AddChildToUniformGrid(HealthIcon, 0, i);
			}
		}
	}
}
