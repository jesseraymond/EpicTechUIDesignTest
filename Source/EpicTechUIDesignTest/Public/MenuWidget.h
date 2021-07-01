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
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UVerticalBox* ChildContainer;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_RollInStarted;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        USoundBase* Sound_RollInFinished;

    UFUNCTION(BlueprintCallable)
    void AddChildren(TArray<UThemedButtonWidget*> NewChildren, TArray<UVerticalBoxSlot*> NewSlots);

    UFUNCTION(BlueprintCallable)
    void AddChild(UThemedButtonWidget* NewChild, UVerticalBoxSlot* NewSlot = nullptr);

protected:
    bool ReadyForNextAnimation;
    TArray<UWidget*> ExistingChildren;
    TArray<UThemedButtonWidget*> ExistingButtons;
    TArray<UThemedButtonWidget*> Queue_RollIn;

    virtual void NativeConstruct() override;
    void TryNextRollIn();

    UFUNCTION()
    void AnimationStarted();
    
    UFUNCTION()
    void AnimationFinished();

private:
    TArray<UVerticalBoxSlot*> ExistingSlots;
};
