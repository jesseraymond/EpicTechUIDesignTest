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
UCLASS()
class EPICTECHUIDESIGNTEST_API UThemedButtonWidget : public UThemedPanelWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UButton* MainButton;

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

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_Pressed;

    UPROPERTY(EditAnywhere)
        FLinearColor Color_OuterBorder_Default = FLinearColor(0.181164, 0.913099, 0.40724, 1);

    UPROPERTY(EditAnywhere)
        FLinearColor Color_InnerBorder_Default = FLinearColor(0.000304, 0.064803, 0.072272, 1);

    UPROPERTY(EditAnywhere)
        FLinearColor Color_OuterBorder_Hovered = FLinearColor(0.181164, 0.913099, 0.40724, 1);

    UPROPERTY(EditAnywhere)
        FLinearColor Color_InnerBorder_Hovered = FLinearColor(0.003677, 0.274677, 0.219526, 1);

    UPROPERTY(EditAnywhere)
        FLinearColor Color_OuterBorder_Pressed = FLinearColor(0.003677, 0.274677, 0.219526, 1);

    UPROPERTY(EditAnywhere)
        FLinearColor Color_InnerBorder_Pressed = FLinearColor(0.000304, 0.064803, 0.072272, 1);

    UPROPERTY(EditAnywhere)
        FLinearColor Color_OuterBorder_Disabled = FLinearColor(0.913, 0.913, 0.913, 1);

    UPROPERTY(EditAnywhere)
        FLinearColor Color_InnerBorder_Disabled = FLinearColor(0.072, 0.072, 0.072, 1);

    UFUNCTION(BlueprintCallable)
        void OnClick();

    UFUNCTION(BlueprintCallable)
        void OnPress();

    UFUNCTION(BlueprintCallable)
        void OnRelease();

    UFUNCTION(BlueprintCallable)
        void OnHover();

    UFUNCTION(BlueprintCallable)
        void OnUnhover();

        void OnDisable();

protected:
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
