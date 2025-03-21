// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UI/NaraPlayerHealthWidget.h"

#include "AbilitySystemComponent.h"
#include "Characters/NaraPlayerCharacter.h"
#include "GAS/NaraAttributeSet.h"
#include "UI/NaraPlayerHealthIconWidget.h"

void UNaraPlayerHealthWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ANaraPlayerCharacter* NaraPlayerCharacter = Cast<ANaraPlayerCharacter>(GetOwningPlayerPawn()))
		NaraPlayerCharacter->OnPlayerInitAbilityActorInfo.AddUniqueDynamic(this, &UNaraPlayerHealthWidget::BindCallbacksToDependencies);
}

void UNaraPlayerHealthWidget::BindCallbacksToDependencies(UAbilitySystemComponent* ASC)
{
	if (!ASC)
		return;

	if (const UNaraAttributeSet* NaraAttributeSet = Cast<UNaraAttributeSet>(ASC->GetAttributeSet(UNaraAttributeSet::StaticClass())))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(NaraAttributeSet->GetHealthAttribute()).AddUObject(this, &UNaraPlayerHealthWidget::HealthChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(NaraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UNaraPlayerHealthWidget::MaxHealthChanged);
		const float MaxHealth = ASC->GetNumericAttribute(NaraAttributeSet->GetMaxHealthAttribute());
		HandleMaxHealthChanged(MaxHealth, MaxHealth); // TODO: Load max health from save data when save system is done.
	}
}

UUniformGridPanel* UNaraPlayerHealthWidget::GetHealthIconContainer_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("UNaraPlayerHealthWidget::GetUniformGridPanel_Implementation: No implementation defined!"));
	return nullptr;
}

void UNaraPlayerHealthWidget::HandleHealthChanged(float OldValue, float NewValue)
{
	UUniformGridPanel* HealthIconContainer = GetHealthIconContainer();
	if (HealthIconContainer == nullptr)
		return;

	const TArray<UWidget*>& ContainerChildren = HealthIconContainer->GetAllChildren();
	for (int32 i = 0; i < ContainerChildren.Num(); i++)
	{
		if (UNaraPlayerHealthIconWidget* HealthIconWidget = Cast<UNaraPlayerHealthIconWidget>(ContainerChildren[i]))
			HealthIconWidget->UpdateIconState(NewValue >= i + 1);
	}
}

void UNaraPlayerHealthWidget::HandleMaxHealthChanged(float OldValue, float NewValue)
{
	if (!ContainerIconClass)
	{
		UE_LOG(LogTemp, Error, TEXT("UNaraPlayerHealthWidget::NativeConstruct: ContainerIconClass is not set!"));
		return;
	}

	if (UUniformGridPanel* HealthIconContainer = GetHealthIconContainer())
	{
		HealthIconContainer->ClearChildren();
		for (int32 i = 1; i <= NewValue; i++)
		{
			UNaraPlayerHealthIconWidget* HealthIcon = CreateWidget<UNaraPlayerHealthIconWidget>(this, ContainerIconClass);
			if (HealthIcon != nullptr)
				UUniformGridSlot* GridSlot = HealthIconContainer->AddChildToUniformGrid(HealthIcon, 0, i);
		}
	}
}
