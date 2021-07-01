// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)


#include "ThemedPanelWidget.h"
#include "Components/OverlaySlot.h"

void UThemedPanelWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    SetOuterBorderColor(Color_OuterBorder);
    SetInnerBorderColor(Color_InnerBorder);
    SetOuterBorderShear(Shear_OuterBorder);
    SetInnerBorderShear(Shear_InnerBorder);
    SetOuterBorderRotation(Angle_Rotation_OuterBorder);
    SetInnerBorderRotation(Angle_Rotation_InnerBorder);
    SetInnerBorderUniformPadding(UniformPadding_InnerBorder);
}
void UThemedPanelWidget::SetOuterBorderColor(FLinearColor NewColor)
{
    Color_OuterBorder = NewColor;
    
    if (OuterBorder)
        OuterBorder->SetBrushColor(NewColor);
}

void UThemedPanelWidget::SetInnerBorderColor(FLinearColor NewColor)
{
    Color_InnerBorder = NewColor;

    if (InnerBorder)
        InnerBorder->SetBrushColor(NewColor);
}

void UThemedPanelWidget::SetOuterBorderShear(FVector2D NewShear)
{
    Shear_OuterBorder = NewShear;

    if (OuterBorder)
        OuterBorder->SetRenderShear(NewShear);
}

void UThemedPanelWidget::SetInnerBorderShear(FVector2D NewShear)
{
    Shear_InnerBorder = NewShear;

    if (InnerBorder)
        InnerBorder->SetRenderShear(NewShear);
}

void UThemedPanelWidget::SetOuterBorderRotation(float NewRotation)
{
    Angle_Rotation_OuterBorder = NewRotation;

    if (OuterBorder)
        OuterBorder->SetRenderTransformAngle(NewRotation);
}

void UThemedPanelWidget::SetInnerBorderRotation(float NewRotation)
{
    Angle_Rotation_InnerBorder = NewRotation;

    if (InnerBorder)
        InnerBorder->SetRenderTransformAngle(NewRotation);
}

void UThemedPanelWidget::SetInnerBorderUniformPadding(float NewValue)
{
    UniformPadding_InnerBorder = NewValue;

    if (InnerBorder)
        if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(InnerBorder->Slot))
            OverlaySlot->SetPadding(FMargin(NewValue));

    // Workaround Note:
    // For some reason, FMargins with UProperties would not compile. I hadn't seen this issue before and had no luck finding any similar issues online while troubleshooting.
    // Since there are other properties available to customize the skewing of the border, switching the property type to a float representing a uniform thickness seemed acceptable.
    
}

