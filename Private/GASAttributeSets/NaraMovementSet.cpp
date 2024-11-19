// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASAttributeSets/NaraMovementSet.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNaraMovementSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute != GetSpeedAttribute())
        return;

    UAbilitySystemComponent* OwningASC = GetOwningAbilitySystemComponent();
    check(OwningASC);

    ACharacter* Character = Cast<ACharacter>(OwningASC->GetAvatarActor());
    if (Character && Character->GetCharacterMovement())
    {
        Character->GetCharacterMovement()->MaxWalkSpeed = NewValue;
    }
}
