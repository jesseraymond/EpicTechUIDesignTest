// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)


#include "ThemedButtonWidget.h"

void UThemedButtonWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (!bIsEnabled)
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

    OnHovered.Broadcast();
}

void UThemedButtonWidget::OnUnhover_Implementation()
{
    SetOuterColor(Color_Outer_Default);
    SetInnerColor(Color_Inner_Default);

    OnUnhovered.Broadcast();
}

void UThemedButtonWidget::OnDisable_Implementation()
{
    SetOuterColor(Color_Outer_Disabled);
    SetInnerColor(Color_Inner_Disabled);
}
