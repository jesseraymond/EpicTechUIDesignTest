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
        ReadyForNextMenuItemAnimation = true;
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
        NewChild->OnPressed.AddDynamic(this, &UMenuWidget::OnMenuButtonPress);

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
    TryNextMenuItemRollIn();
}

void UMenuWidget::TryNextMenuItemRollIn()
{
    if (ReadyForNextMenuItemAnimation)
    {
        if (Queue_RollIn.Num() > 0)
        {
            Queue_RollIn[0]->RollInStartEvent.BindDynamic(this, &UMenuWidget::MenuItemAnimationStarted);
            Queue_RollIn[0]->RollInEndEvent.BindDynamic(this, &UMenuWidget::MenuItemAnimationFinished);

            Queue_RollIn[0]->BindToAnimationStarted(Queue_RollIn[0]->RollInAnimation, Queue_RollIn[0]->RollInStartEvent);
            Queue_RollIn[0]->BindToAnimationFinished(Queue_RollIn[0]->RollInAnimation, Queue_RollIn[0]->RollInEndEvent);

            Queue_RollIn[0]->PlayAnimation(Queue_RollIn[0]->RollInAnimation);
            Queue_RollIn[0]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
        }
    }
}

void UMenuWidget::MenuItemAnimationStarted()
{
    ReadyForNextMenuItemAnimation = false;

    if (Sound_MenuItem_RollIn_Started)
        PlaySound(Sound_MenuItem_RollIn_Started);
}

void UMenuWidget::MenuItemAnimationFinished()
{
    if (Sound_MenuItem_RollIn_Finished)
        PlaySound(Sound_MenuItem_RollIn_Finished);

    ReadyForNextMenuItemAnimation = true;
    if (Queue_RollIn.Num() > 0)
    {      
        Queue_RollIn.RemoveAt(0);
        TryNextMenuItemRollIn();
    }
}

TArray<UWidget*> UMenuWidget::GetChildren()
{
    if (ChildContainer)
    {
        return ChildContainer->GetAllChildren();
    }
    else
    {
        return TArray<UWidget*>{ nullptr };
    }
}

void UMenuWidget::OnMenuButtonPress_Implementation()
{
    OnMenuButtonPressed.Broadcast();
}