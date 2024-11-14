// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UI/NaraPlayerHealthWidget.h"

#include "AbilitySystemComponent.h"
#include "ActorComponents/NaraHealthComponent.h"
#include "GASAttributeSets/NaraHealthSet.h"
#include "UI/NaraPlayerHealthIconWidget.h"

// TODO: It might actually be better to subscribe directly to the Health Attribute Set's OnValueChanged event (if it exist, there should be some equivalent).
// TODO: Might also cache the attribute set instead of the health component.

void UNaraPlayerHealthWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CachedHealthComponent = UNaraHealthComponent::FindHealthComponent(GetOwningPlayerPawn());
	if (CachedHealthComponent == nullptr)
		return;

	CachedHealthComponent->OnDamaged.AddUniqueDynamic(this, &UNaraPlayerHealthWidget::UpdateHealthDisplay);

	/*const UNaraHealthSet* HealthSet = CachedHealthComponent->GetHealthSet();
	UAbilitySystemComponent* AbilitySystemComponent = CachedHealthComponent->GetAbilitySystemComponent();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			HealthSet->GetHealthAttribute()).AddUObject(this, &UNaraPlayerHealthWidget::OnHealthAttributeChanged);
	}*/
}

void UNaraPlayerHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();

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
				UE_LOG(LogTemp, Display, TEXT("UNaraPlayerHealthWidget::NativeConstruct: %d"), i);
				UNaraPlayerHealthIconWidget* HealthIcon = CreateWidget<UNaraPlayerHealthIconWidget>(this, ContainerIconClass);
				if (HealthIcon != nullptr)
					UUniformGridSlot* GridSlot = HealthIconContainer->AddChildToUniformGrid(HealthIcon, 0, i);
			}
		}
	}

	UpdateHealthDisplay();
}

UUniformGridPanel* UNaraPlayerHealthWidget::GetHealthIconContainer_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("UNaraPlayerHealthWidget::GetUniformGridPanel_Implementation: No implementation defined!"));
	return nullptr;
}

void UNaraPlayerHealthWidget::UpdateHealthDisplay()
{
	if (CachedHealthComponent == nullptr)
		return;

	UUniformGridPanel* HealthIconContainer = GetHealthIconContainer();
	if (HealthIconContainer == nullptr)
		return;

	TArray<UWidget*> ContainerChildren = HealthIconContainer->GetAllChildren();
	if (ContainerChildren.IsEmpty())
		return;

	const UNaraHealthSet* HealthSet = CachedHealthComponent->GetHealthSet();
	if (HealthSet == nullptr)
		return;

	const float MaxHealth = HealthSet->GetMaxHealth();
	const float CurrentHealth = HealthSet->GetHealth();

	for (int32 i = 1; i <= MaxHealth; i++)
	{
		if (!ContainerChildren.IsValidIndex(i - 1))
			continue;

		UNaraPlayerHealthIconWidget* HealthIconWidget = Cast<UNaraPlayerHealthIconWidget>(ContainerChildren[i - 1]);
		if (!HealthIconWidget)
			continue;

		HealthIconWidget->UpdateIconState(i <= CurrentHealth);
	}
}
