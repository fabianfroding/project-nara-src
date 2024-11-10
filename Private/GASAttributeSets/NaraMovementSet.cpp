// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASAttributeSets/NaraMovementSet.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNaraMovementSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute != GetSpeedAttribute())
        return;

    AActor* OwnerActor = GetOwningActor();
    if (OwnerActor == nullptr)
        return;

    ACharacter* Character = Cast<ACharacter>(OwnerActor);
    if (Character && Character->GetCharacterMovement())
    {
        Character->GetCharacterMovement()->MaxWalkSpeed = NewValue;
    }
}
