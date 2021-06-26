// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Animation/WidgetAnimation.h"
#include "ThemedButtonWidget.h"
#include "MenuWidget.generated.h"

UCLASS()
class EPICTECHUIDESIGNTEST_API UMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UMenuWidget(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void AddChildren(TArray<UThemedButtonWidget*> NewChildren);

    UFUNCTION(BlueprintCallable)
    void AddChild(UThemedButtonWidget* NewChild);

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UVerticalBox* ChildContainer = nullptr;

protected:
    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void AnimationStarted();
    
    UFUNCTION()
    void AnimationFinished();
   
    void TryNextRollIn();

    bool ReadyForNextAnimation;
    TArray<UWidget*> ExistingChildren;
    TArray<UThemedButtonWidget*> ExistingButtons;
    TArray<UThemedButtonWidget*> Queue_RollIn;
};
