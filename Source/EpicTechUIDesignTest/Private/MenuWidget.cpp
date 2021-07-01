// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)

#include "MenuWidget.h"

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

                if (UVerticalBoxSlot* BoxSlot = Cast<UVerticalBoxSlot>(ThemedButton->Slot))
                    ExistingSlots.Add(BoxSlot);
                
                ExistingButtons.Add(ThemedButton);
            }
        }

        ChildContainer->ClearChildren();
        ReadyForNextAnimation = true;
        AddChildren(ExistingButtons, ExistingSlots);
    }
}

void UMenuWidget::AddChildren(TArray<UThemedButtonWidget*> NewChildren, TArray<UVerticalBoxSlot*> NewSlots)
{
    for (int32 i = 0; i < NewChildren.Num(); i++)
    {
        if (NewSlots[i])
        {
            AddChild(NewChildren[i], NewSlots[i]);
        }
        else
        {
            AddChild(NewChildren[i]);
        }
    }
}

void UMenuWidget::AddChild(UThemedButtonWidget* NewChild, UVerticalBoxSlot* NewSlot)
{
    if (!NewChild)
        return;

    if (ChildContainer)
    {
        ChildContainer->AddChild(NewChild);

        if (NewSlot)
        {
            if (UVerticalBoxSlot* BoxSlot = Cast<UVerticalBoxSlot>(NewChild->Slot))
            {
                BoxSlot->SetHorizontalAlignment(NewSlot->HorizontalAlignment);
                BoxSlot->SetVerticalAlignment(NewSlot->VerticalAlignment);
                BoxSlot->SetPadding(NewSlot->Padding);
                BoxSlot->SetSize(NewSlot->Size);
            }
        }
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
            Queue_RollIn[0]->RollInStartEvent.BindDynamic(this, &UMenuWidget::AnimationStarted);
            Queue_RollIn[0]->RollInEndEvent.BindDynamic(this, &UMenuWidget::AnimationFinished);

            Queue_RollIn[0]->BindToAnimationStarted(Queue_RollIn[0]->RollInAnimation, Queue_RollIn[0]->RollInStartEvent);
            Queue_RollIn[0]->BindToAnimationFinished(Queue_RollIn[0]->RollInAnimation, Queue_RollIn[0]->RollInEndEvent);

            Queue_RollIn[0]->PlayAnimation(Queue_RollIn[0]->RollInAnimation);
            Queue_RollIn[0]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
        }
    }
}

void UMenuWidget::AnimationStarted()
{
    ReadyForNextAnimation = false;

    if (Sound_RollInStarted)
        PlaySound(Sound_RollInStarted);
}

void UMenuWidget::AnimationFinished()
{
    if (Sound_RollInFinished)
        PlaySound(Sound_RollInFinished);

    ReadyForNextAnimation = true;
    if (Queue_RollIn.Num() > 0)
    {      
        Queue_RollIn.RemoveAt(0);
        TryNextRollIn();
    }
}