// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Animation/WidgetAnimation.h"
#include "ThemedButtonWidget.h"
#include "MenuWidget.generated.h"

UCLASS()
class EPICTECHUIDESIGNTEST_API UMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, Category = "Button|Event")
        FOnButtonPressedEvent OnMenuButtonPressed;

    UFUNCTION(BlueprintCallable)
        void AddChildren(TArray<UThemedButtonWidget*> NewChildren, TArray<UVerticalBoxSlot*> NewSlots);

    UFUNCTION(BlueprintCallable)
        void AddChild(UThemedButtonWidget* NewChild, UVerticalBoxSlot* NewSlot = nullptr);

    UFUNCTION(BlueprintCallable)
        void ClearChildren();

    UFUNCTION(BlueprintCallable)
        void RemoveChildren(TArray<UThemedButtonWidget*> ChildrenToRemove);

    UFUNCTION(BlueprintCallable)
        void RemoveChild(UThemedButtonWidget* ChildToRemove);

    UFUNCTION(BlueprintCallable)
        void ReanimateMenu();

    UFUNCTION(BlueprintCallable)
        TArray<UWidget*> GetChildren();


protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UVerticalBox* ChildContainer;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_MenuItem_RollIn_Started;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_MenuItem_RollIn_Finished;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_MenuItem_RollOut_Started;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_MenuItem_RollOut_Finished;

    bool ReadyForNextRollIn = true;
    bool ReadyForNextRollOut = true;
    bool IsReanimating;
    TArray<UWidget*> ExistingChildren;
    TArray<UVerticalBoxSlot*> ExistingSlots;
    TArray<UThemedButtonWidget*> ExistingButtons;
    TArray<UThemedButtonWidget*> ReanimatedChildren;
    TArray<UVerticalBoxSlot*> ReanimatedSlots;
    TArray<UThemedButtonWidget*> Queue_RollIn;
    TArray<UThemedButtonWidget*> Queue_RollOut;

    UFUNCTION(BlueprintNativeEvent)
        void OnMenuButtonPress();

    UFUNCTION()
        void MenuItemRollInAnimationStarted();
    
    UFUNCTION()
        void MenuItemRollInAnimationFinished();

    UFUNCTION()
        void MenuItemRollOutAnimationStarted();

    UFUNCTION()
        void MenuItemRollOutAnimationFinished();

    virtual void NativeConstruct() override;
    void TryNextMenuItemRollIn();
    void TryNextMenuItemRollOut();
};
