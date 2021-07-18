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
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UButton* MainButton;

    UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
        class UWidgetAnimation* RollInAnimation;

    UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
        class UWidgetAnimation* RollOutAnimation;

    UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
        class UWidgetAnimation* HoverAnimation;

    UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
        class UWidgetAnimation* UnhoverAnimation;

    UPROPERTY(BlueprintReadOnly, Transient)
        FWidgetAnimationDynamicEvent RollInStartEvent;

    UPROPERTY(BlueprintReadOnly, Transient)
        FWidgetAnimationDynamicEvent RollInEndEvent;

    UPROPERTY(BlueprintReadOnly, Transient)
        FWidgetAnimationDynamicEvent RollOutStartEvent;

    UPROPERTY(BlueprintReadOnly, Transient)
        FWidgetAnimationDynamicEvent RollOutEndEvent;

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
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_Pressed;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_Hovered;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_Unhovered;

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

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Inner_TopLeft_Hover = FVector2D(0.15, 0.8);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Inner_TopRight_Hover = FVector2D(0, 0.4);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Inner_BottomLeft_Hover = FVector2D(0.15, 0.8);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Inner_BottomRight_Hover= FVector2D(0, 0.4);
    
    FVector2D Position_Inner_TopLeft_Unhover;
    FVector2D Position_Inner_TopRight_Unhover;
    FVector2D Position_Inner_BottomLeft_Unhover;
    FVector2D Position_Inner_BottomRight_Unhover;
    float HoverTimeElapsed;
    float UnhoverTimeElapsed;
    float CornerAnimationDuration = 0.35;

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



