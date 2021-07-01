// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)


#include "ThemedButtonWidget.h"

void UThemedButtonWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (!bIsEnabled)
    {
        OnDisable();
    }
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
    {
        OnDisable();
    }
}

void UThemedButtonWidget::OnClick()
{
    OnClicked.Broadcast();
}

void UThemedButtonWidget::OnPress()
{
    if (OuterBorder)
        OuterBorder->SetBrushColor(Color_OuterBorder_Pressed);
    if (InnerBorder)
        InnerBorder->SetBrushColor(Color_InnerBorder_Pressed);

    if (Sound_Pressed)
        PlaySound(Sound_Pressed);

    OnPressed.Broadcast();
}

void UThemedButtonWidget::OnRelease()
{
    if (OuterBorder)
        OuterBorder->SetBrushColor(Color_OuterBorder_Hovered);
    if (InnerBorder)
        InnerBorder->SetBrushColor(Color_InnerBorder_Hovered);

    OnReleased.Broadcast();
}

void UThemedButtonWidget::OnHover()
{
    if (OuterBorder)
        OuterBorder->SetBrushColor(Color_OuterBorder_Hovered);
    if (InnerBorder)
        InnerBorder->SetBrushColor(Color_InnerBorder_Hovered);

    OnHovered.Broadcast();
}

void UThemedButtonWidget::OnUnhover()
{
    if (OuterBorder)
        OuterBorder->SetBrushColor(Color_OuterBorder);
    if (InnerBorder)
        InnerBorder->SetBrushColor(Color_InnerBorder);

    OnUnhovered.Broadcast();
}

void UThemedButtonWidget::OnDisable()
{
    if (OuterBorder)
        OuterBorder->SetBrushColor(Color_OuterBorder_Disabled);
    if (InnerBorder)
        InnerBorder->SetBrushColor(Color_InnerBorder_Disabled);
}
