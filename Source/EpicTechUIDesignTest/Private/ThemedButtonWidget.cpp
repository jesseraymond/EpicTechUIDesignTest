// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)


#include "ThemedButtonWidget.h"

void UThemedButtonWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    Position_Inner_BottomRight_Unhover = Position_Inner_BottomRight;
    Position_Inner_BottomLeft_Unhover = Position_Inner_BottomLeft;

    if (bIsEnabled)
        OnUnhover();
    else
        OnDisable();
}

void UThemedButtonWidget::NativeConstruct()
{
    Super::NativeConstruct();

    MainButton->OnClicked.AddDynamic(this, &UThemedButtonWidget::OnClick);
    MainButton->OnPressed.AddDynamic(this, &UThemedButtonWidget::OnPress);
    MainButton->OnReleased.AddDynamic(this, &UThemedButtonWidget::OnRelease);
    MainButton->OnHovered.AddDynamic(this, &UThemedButtonWidget::OnHover);
    MainButton->OnUnhovered.AddDynamic(this, &UThemedButtonWidget::OnUnhover);
}

void UThemedButtonWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (!bIsEnabled)
        OnDisable();
    else
    {
        if (MainButton->IsHovered())
        {
            UnhoverTimeElapsed = 0;

            if (HoverTimeElapsed < CornerAnimationDuration)
            {
                HoverTimeElapsed += InDeltaTime;
                SetPositionInnerBottomRight(FMath::Lerp(Position_Inner_BottomRight, Position_Inner_BottomRight_Hover, HoverTimeElapsed / CornerAnimationDuration));
                SetPositionInnerBottomLeft(FMath::Lerp(Position_Inner_BottomLeft, Position_Inner_BottomLeft_Hover, HoverTimeElapsed / CornerAnimationDuration));
            }
        }
        else
        {
            HoverTimeElapsed = 0;

            if (UnhoverTimeElapsed < CornerAnimationDuration)
            {
                UnhoverTimeElapsed += InDeltaTime;
                SetPositionInnerBottomRight(FMath::Lerp(Position_Inner_BottomRight, Position_Inner_BottomRight_Unhover, UnhoverTimeElapsed / CornerAnimationDuration));
                SetPositionInnerBottomLeft(FMath::Lerp(Position_Inner_BottomLeft, Position_Inner_BottomLeft_Unhover, UnhoverTimeElapsed / CornerAnimationDuration));
            }
        }
    }
}

void UThemedButtonWidget::OnClick_Implementation()
{
    OnClicked.Broadcast();
}

void UThemedButtonWidget::OnPress_Implementation()
{
    SetOuterColor(Color_Outer_Pressed);
    SetInnerColor(Color_Inner_Pressed);

    if (Sound_Pressed)
        PlaySound(Sound_Pressed);

    OnPressed.Broadcast();
}

void UThemedButtonWidget::OnRelease_Implementation()
{
    SetOuterColor(Color_Outer_Hovered);
    SetInnerColor(Color_Inner_Hovered);

    OnReleased.Broadcast();
}

void UThemedButtonWidget::OnHover_Implementation()
{
    SetOuterColor(Color_Outer_Hovered);
    SetInnerColor(Color_Inner_Hovered);

    //if (MainButton)
    //    MainButton->SetColorAndOpacity(FLinearColor::White);

    //if (PanelRootContainer)
    //    PanelRootContainer->SetRenderTranslation(FVector2D::ZeroVector);

    if (Sound_Hovered)
        PlaySound(Sound_Hovered);

    PlayAnimation(HoverAnimation);

    OnHovered.Broadcast();
}

void UThemedButtonWidget::OnUnhover_Implementation()
{
    SetOuterColor(Color_Outer_Default);
    SetInnerColor(Color_Inner_Default);

    if (Sound_Unhovered)
        PlaySound(Sound_Unhovered);

    PlayAnimation(UnhoverAnimation);

    OnUnhovered.Broadcast();
}

void UThemedButtonWidget::OnDisable_Implementation()
{
    SetOuterColor(Color_Outer_Disabled);
    SetInnerColor(Color_Inner_Disabled);
}
