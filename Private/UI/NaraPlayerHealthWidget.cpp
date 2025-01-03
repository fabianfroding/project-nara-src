// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UI/NaraPlayerHealthWidget.h"

#include "AbilitySystemComponent.h"
#include "GAS/NaraAttributeSet.h"
#include "UI/NaraPlayerHealthIconWidget.h"

UUniformGridPanel* UNaraPlayerHealthWidget::GetHealthIconContainer_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("UNaraPlayerHealthWidget::GetUniformGridPanel_Implementation: No implementation defined!"));
	return nullptr;
}

void UNaraPlayerHealthWidget::HandleHealthChanged(float OldValue, float NewValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("UNaraPlayerHealthWidget: Handle health changed"));

	UUniformGridPanel* HealthIconContainer = GetHealthIconContainer();
	if (HealthIconContainer == nullptr)
		return;

	TArray<UWidget*> ContainerChildren = HealthIconContainer->GetAllChildren();

	for (int32 i = 1; i <= ContainerChildren.Num() - 1; i++)
	{
		//UE_LOG(LogTemp, Display, TEXT("UNaraPlayerHealthWidget::HandleHealthChanged: %d!"), i);
		if (!ContainerChildren.IsValidIndex(i - 1))
			continue;

		//UE_LOG(LogTemp, Display, TEXT("UNaraPlayerHealthWidget::HandleHealthChanged: B!"));
		UNaraPlayerHealthIconWidget* HealthIconWidget = Cast<UNaraPlayerHealthIconWidget>(ContainerChildren[i - 1]);
		if (!HealthIconWidget)
			continue;

		//UE_LOG(LogTemp, Display, TEXT("UNaraPlayerHealthWidget::HandleHealthChanged: C!"));
		HealthIconWidget->UpdateIconState(i <= NewValue);
	}
}

void UNaraPlayerHealthWidget::HandleMaxHealthChanged(float OldValue, float NewValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("UNaraPlayerHealthWidget: HandleMaxHealth changed"));
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
