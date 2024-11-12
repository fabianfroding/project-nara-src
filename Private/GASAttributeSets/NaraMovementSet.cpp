// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASAttributeSets/NaraMovementSet.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNaraMovementSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    UE_LOG(LogTemp, Display, TEXT("UNaraMovementSet::PreAttributeChange"));
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute != GetSpeedAttribute())
        return;
    UE_LOG(LogTemp, Display, TEXT("UNaraMovementSet::PreAttributeChange: Attribute is speed attribute"));

    AActor* OwnerActor = GetOwningActor();
    if (OwnerActor == nullptr)
        return;
    UE_LOG(LogTemp, Display, TEXT("UNaraMovementSet::PreAttributeChange: Owner actor valid"));

    ACharacter* Character = Cast<ACharacter>(OwnerActor);
    if (Character && Character->GetCharacterMovement())
    {
        UE_LOG(LogTemp, Display, TEXT("UNaraMovementSet::PreAttributeChange: Update max walk speed"));
        Character->GetCharacterMovement()->MaxWalkSpeed = NewValue;
    }
}
