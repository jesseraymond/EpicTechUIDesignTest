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
        
        if (!IsReanimating)
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

void UMenuWidget::ClearChildren()
{
    for (int32 i = 0; i < GetChildren().Num(); i++)
    {
        if (UThemedButtonWidget* ButtonChild = Cast<UThemedButtonWidget>(GetChildren()[i]))
        {
            RemoveChild(ButtonChild);
        }
        else
        {
            ChildContainer->RemoveChild(GetChildren()[i]);
        }
    }
}

void UMenuWidget::RemoveChildren(TArray<UThemedButtonWidget*> ChildrenToRemove)
{
    for (int32 i = 0; i < ChildrenToRemove.Num(); i++)
    {
        RemoveChild(ChildrenToRemove[i]);
    }
}

void UMenuWidget::RemoveChild(UThemedButtonWidget* ChildToRemove)
{
    if (!ChildToRemove)
        return;

    Queue_RollOut.Add(ChildToRemove);
    TryNextMenuItemRollOut();
}

void UMenuWidget::TryNextMenuItemRollIn()
{
    if (ReadyForNextRollIn)
    {
        if (Queue_RollIn.Num() > 0)
        {
            if (!Queue_RollIn[0]->RollInStartEvent.IsBound())
            {
                Queue_RollIn[0]->RollInStartEvent.BindDynamic(this, &UMenuWidget::MenuItemRollInAnimationStarted);
                Queue_RollIn[0]->BindToAnimationStarted(Queue_RollIn[0]->RollInAnimation, Queue_RollIn[0]->RollInStartEvent);
            }

            if (!Queue_RollIn[0]->RollInEndEvent.IsBound())
            {
                Queue_RollIn[0]->RollInEndEvent.BindDynamic(this, &UMenuWidget::MenuItemRollInAnimationFinished);
                Queue_RollIn[0]->BindToAnimationFinished(Queue_RollIn[0]->RollInAnimation, Queue_RollIn[0]->RollInEndEvent);
            }
            
            Queue_RollIn[0]->PlayAnimation(Queue_RollIn[0]->RollInAnimation);
            Queue_RollIn[0]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
        }
    }
}

void UMenuWidget::TryNextMenuItemRollOut()
{
    if (ReadyForNextRollOut)
    {
        if (Queue_RollOut.Num() > 0)
        {
            if (!Queue_RollOut[0]->RollOutStartEvent.IsBound())
            {
                Queue_RollOut[0]->RollOutStartEvent.BindDynamic(this, &UMenuWidget::MenuItemRollOutAnimationStarted);
                Queue_RollOut[0]->BindToAnimationStarted(Queue_RollOut[0]->RollOutAnimation, Queue_RollOut[0]->RollOutStartEvent);
            }

            if (!Queue_RollOut[0]->RollOutEndEvent.IsBound())
            {
                Queue_RollOut[0]->RollOutEndEvent.BindDynamic(this, &UMenuWidget::MenuItemRollOutAnimationFinished);
                Queue_RollOut[0]->BindToAnimationFinished(Queue_RollOut[0]->RollOutAnimation, Queue_RollOut[0]->RollOutEndEvent);
            }

            Queue_RollOut[0]->PlayAnimation(Queue_RollOut[0]->RollOutAnimation);
        }
    }
}

void UMenuWidget::MenuItemRollInAnimationStarted()
{
    ReadyForNextRollIn = false;

    if (Sound_MenuItem_RollIn_Started)
        PlaySound(Sound_MenuItem_RollIn_Started);
}

void UMenuWidget::MenuItemRollInAnimationFinished()
{
    if (Sound_MenuItem_RollIn_Finished)
        PlaySound(Sound_MenuItem_RollIn_Finished);

    ReadyForNextRollIn = true;
    if (Queue_RollIn.Num() > 0)
    {
        if (Queue_RollIn[0]->MainButton)
            Queue_RollIn[0]->MainButton->SetColorAndOpacity(FLinearColor::White);

        if (Queue_RollIn[0]->PanelRootContainer)
            Queue_RollIn[0]->PanelRootContainer->SetRenderTranslation(FVector2D::ZeroVector);

        Queue_RollIn.RemoveAt(0);
        TryNextMenuItemRollIn();
    }
}

void UMenuWidget::MenuItemRollOutAnimationStarted()
{
    ReadyForNextRollOut = false;

    if (Sound_MenuItem_RollOut_Started)
        PlaySound(Sound_MenuItem_RollOut_Started);
}


void UMenuWidget::MenuItemRollOutAnimationFinished()
{
    if (Sound_MenuItem_RollOut_Finished)
        PlaySound(Sound_MenuItem_RollOut_Finished);

    ReadyForNextRollOut = true;
    if (Queue_RollOut.Num() > 0)
    {
        if (IsReanimating)
        {
            if (Queue_RollOut.Num() == 1)
            {
                AddChildren(ReanimatedChildren, ReanimatedSlots);
                IsReanimating = false;
            }
        }
        else
        {
            if (ChildContainer)
            {
                if (ChildContainer->HasChild(Queue_RollOut[0]))
                    ChildContainer->RemoveChild(Queue_RollOut[0]);
            }
        }

        Queue_RollOut.RemoveAt(0);
        TryNextMenuItemRollOut();
    }
}

void UMenuWidget::ReanimateMenu()
{
    IsReanimating = true;
    ReanimatedChildren.Empty();
    ReanimatedSlots.Empty();
    Queue_RollIn.Empty();
    Queue_RollOut.Empty();
    
    for (int32 i = 0; i < GetChildren().Num(); i++)
    {
        if (UThemedButtonWidget* ButtonChild = Cast<UThemedButtonWidget>(GetChildren()[i]))
        {
            ReanimatedChildren.Add(ButtonChild);

            if (UVerticalBoxSlot* BoxSlot = Cast<UVerticalBoxSlot>(ButtonChild->Slot))
                ReanimatedSlots.Add(BoxSlot);
        }
    }

    RemoveChildren(ReanimatedChildren);
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