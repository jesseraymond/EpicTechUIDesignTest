// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "ThemedButtonWidget.generated.h"

/**
 *
 */
UCLASS()
class EPICTECHUIDESIGNTEST_API UThemedButtonWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
        class UWidgetAnimation* RollInAnimation;

    FWidgetAnimationDynamicEvent RollInStartDelegate;
    FWidgetAnimationDynamicEvent RollInEndDelegate;

protected:
    virtual void NativeConstruct() override;
};
