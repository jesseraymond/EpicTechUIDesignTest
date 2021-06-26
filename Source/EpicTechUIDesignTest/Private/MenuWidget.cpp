// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)

#include "MenuWidget.h"

UMenuWidget::UMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ChildContainer)
    {
        ExistingChildren = ChildContainer->GetAllChildren();
        for (int32 i = 0; i < ExistingChildren.Num(); i++)
        {
            if (UThemedButtonWidget* ThemedButton = Cast<UThemedButtonWidget>(ExistingChildren[i]))
            {
                ThemedButton->SetVisibility(ESlateVisibility::Hidden);
                ExistingButtons.Add(ThemedButton);
            }
        }

        ChildContainer->ClearChildren();
        ReadyForNextAnimation = true;
        AddChildren(ExistingButtons);
    }
}

void UMenuWidget::AddChildren(TArray<UThemedButtonWidget*> NewChildren)
{
    for (int32 i = 0; i < NewChildren.Num(); i++)
    {
        AddChild(NewChildren[i]);
    }
}

void UMenuWidget::AddChild(UThemedButtonWidget* NewChild)
{
    if (!NewChild)
        return;

    if (ChildContainer)
    {
        ChildContainer->AddChild(NewChild);
    }

    Queue_RollIn.Add(NewChild);
    TryNextRollIn();
}

void UMenuWidget::TryNextRollIn()
{
    if (ReadyForNextAnimation)
    {
        if (Queue_RollIn.Num() > 0)
        {
            Queue_RollIn[0]->RollInStartDelegate.BindDynamic(this, &UMenuWidget::AnimationStarted);
            Queue_RollIn[0]->RollInEndDelegate.BindDynamic(this, &UMenuWidget::AnimationFinished);

            Queue_RollIn[0]->BindToAnimationStarted(Queue_RollIn[0]->RollInAnimation, Queue_RollIn[0]->RollInStartDelegate);
            Queue_RollIn[0]->BindToAnimationFinished(Queue_RollIn[0]->RollInAnimation, Queue_RollIn[0]->RollInEndDelegate);

            Queue_RollIn[0]->PlayAnimation(Queue_RollIn[0]->RollInAnimation);
            Queue_RollIn[0]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
        }
    }
}

void UMenuWidget::AnimationStarted()
{
    ReadyForNextAnimation = false;
}

void UMenuWidget::AnimationFinished()
{
    ReadyForNextAnimation = true;
    if (Queue_RollIn.Num() > 0)
    {      
        Queue_RollIn.RemoveAt(0);
        TryNextRollIn();
    }
}