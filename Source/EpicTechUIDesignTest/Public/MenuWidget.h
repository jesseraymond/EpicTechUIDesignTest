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
        TArray<UWidget*> GetChildren();


protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UVerticalBox* ChildContainer;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_MenuItem_RollIn_Started;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_MenuItem_RollIn_Finished;

    bool ReadyForNextMenuItemAnimation;
    TArray<UWidget*> ExistingChildren;
    TArray<UVerticalBoxSlot*> ExistingSlots;
    TArray<UThemedButtonWidget*> ExistingButtons;
    TArray<UThemedButtonWidget*> Queue_RollIn;

    UFUNCTION(BlueprintNativeEvent)
        void OnMenuButtonPress();

    UFUNCTION()
        void MenuItemAnimationStarted();
    
    UFUNCTION()
        void MenuItemAnimationFinished();

    virtual void NativeConstruct() override;
    void TryNextMenuItemRollIn();
};
