// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Libraries/NaraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Player/NaraPlayerState.h"
#include "UI/NaraHUD.h"
#include "UIControllers/NaraWidgetController.h"

UOverlayWidgetController* UNaraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
    {
        if (ANaraHUD* NaraHUD = Cast<ANaraHUD>(PC->GetHUD()))
        {
            ANaraPlayerState* PS = PC->GetPlayerState<ANaraPlayerState>();
            UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
            UAttributeSet* AS = PS->GetAttributeSet();
            const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
            return NaraHUD->GetOverlayWidgetController(WidgetControllerParams);
        }
    }

    return nullptr;
}
