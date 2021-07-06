// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)

#pragma once

#include "CoreMinimal.h"
#include "ThemedPanelWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Animation/WidgetAnimation.h"
#include "ThemedButtonWidget.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class EPICTECHUIDESIGNTEST_API UThemedButtonWidget : public UThemedPanelWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
        class UWidgetAnimation* RollInAnimation;

    UPROPERTY(BlueprintReadOnly, Transient)
        FWidgetAnimationDynamicEvent RollInStartEvent;

    UPROPERTY(BlueprintReadOnly, Transient)
        FWidgetAnimationDynamicEvent RollInEndEvent;

    UPROPERTY(BlueprintAssignable, Category = "Button|Event")
        FOnButtonClickedEvent OnClicked;

    UPROPERTY(BlueprintAssignable, Category = "Button|Event")
        FOnButtonPressedEvent OnPressed;

    UPROPERTY(BlueprintAssignable, Category = "Button|Event")
        FOnButtonReleasedEvent OnReleased;

    UPROPERTY(BlueprintAssignable, Category = "Button|Event")
        FOnButtonHoverEvent OnHovered;

    UPROPERTY(BlueprintAssignable, Category = "Button|Event")
        FOnButtonHoverEvent OnUnhovered;

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UButton* MainButton;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_Pressed;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FLinearColor Color_Outer_Default = FLinearColor(0.181164, 0.913099, 0.40724, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FLinearColor Color_Inner_Default = FLinearColor(0.000304, 0.064803, 0.072272, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FLinearColor Color_Outer_Hovered = FLinearColor(0.181164, 0.913099, 0.40724, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FLinearColor Color_Inner_Hovered = FLinearColor(0.003677, 0.274677, 0.219526, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FLinearColor Color_Outer_Pressed = FLinearColor(0.003677, 0.274677, 0.219526, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FLinearColor Color_Inner_Pressed = FLinearColor(0.000304, 0.064803, 0.072272, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FLinearColor Color_Outer_Disabled = FLinearColor(0.913, 0.913, 0.913, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FLinearColor Color_Inner_Disabled = FLinearColor(0.072, 0.072, 0.072, 1);

    UFUNCTION(BlueprintNativeEvent)
        void OnClick();

    UFUNCTION(BlueprintNativeEvent)
        void OnPress();

    UFUNCTION(BlueprintNativeEvent)
        void OnRelease();

    UFUNCTION(BlueprintNativeEvent)
        void OnHover();

    UFUNCTION(BlueprintNativeEvent)
        void OnUnhover();

    UFUNCTION(BlueprintNativeEvent)
        void OnDisable();

    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
