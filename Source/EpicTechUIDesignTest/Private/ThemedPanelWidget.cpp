// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)


#include "ThemedPanelWidget.h"
#include "Components/OverlaySlot.h"

void UThemedPanelWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    UpdateDynamicMaterialInstanceProperties();
}

void UThemedPanelWidget::UpdateDynamicMaterialInstanceProperties()
{
    if (DynamicMaterialHost)
    {
        if (DynamicMaterial && !DynamicMaterialInstance)
            DynamicMaterialInstance = UMaterialInstanceDynamic::Create(DynamicMaterial, this);

        if (DynamicMaterialInstance)
        {
            DynamicMaterialHost->SetBrushFromMaterial(DynamicMaterialInstance);

            FLinearColor OuterColor;
            DynamicMaterialInstance->GetVectorParameterValue(FName(TEXT("Color_Outer")), OuterColor);
            if (OuterColor != Color_Outer)
                SetOuterColor(Color_Outer);

            FLinearColor InnerColor;
            DynamicMaterialInstance->GetVectorParameterValue(FName(TEXT("Color_Inner")), InnerColor);
            if (InnerColor != Color_Inner)
                SetInnerColor(Color_Inner);

            FLinearColor OuterTopLeft;
            DynamicMaterialInstance->GetVectorParameterValue(FName(TEXT("Position_Outer_TopLeft")), OuterTopLeft);
            if (!(OuterTopLeft.R == Position_Outer_TopLeft.X && OuterTopLeft.G == Position_Outer_TopLeft.Y))
                SetPositionOuterTopLeft(Position_Outer_TopLeft);

            FLinearColor OuterTopRight;
            DynamicMaterialInstance->GetVectorParameterValue(FName(TEXT("Position_Outer_TopRight")), OuterTopRight);
            if (!(OuterTopRight.R == Position_Outer_TopRight.X && OuterTopRight.G == Position_Outer_TopRight.Y))
                SetPositionOuterTopRight(Position_Outer_TopRight);

            FLinearColor OuterBottomRight;
            DynamicMaterialInstance->GetVectorParameterValue(FName(TEXT("Position_Outer_BottomRight")), OuterBottomRight);
            if (!(OuterBottomRight.R == Position_Outer_BottomRight.X && OuterBottomRight.G == Position_Outer_BottomRight.Y))
                SetPositionOuterBottomRight(Position_Outer_BottomRight);

            FLinearColor OuterBottomLeft;
            DynamicMaterialInstance->GetVectorParameterValue(FName(TEXT("Position_Outer_BottomLeft")), OuterBottomLeft);
            if (!(OuterBottomLeft.R == Position_Outer_BottomLeft.X && OuterBottomLeft.G == Position_Outer_BottomLeft.Y))
                SetPositionOuterBottomLeft(Position_Outer_BottomLeft);

            FLinearColor InnerTopLeft;
            DynamicMaterialInstance->GetVectorParameterValue(FName(TEXT("Position_Inner_TopLeft")), InnerTopLeft);
            if (!(InnerTopLeft.R == Position_Inner_TopLeft.X && InnerTopLeft.G == Position_Inner_TopLeft.Y))
                SetPositionInnerTopLeft(Position_Inner_TopLeft);

            FLinearColor InnerTopRight;
            DynamicMaterialInstance->GetVectorParameterValue(FName(TEXT("Position_Inner_TopRight")), InnerTopRight);
            if (!(InnerTopRight.R == Position_Inner_TopRight.X && InnerTopRight.G == Position_Inner_TopRight.Y))
                SetPositionInnerTopRight(Position_Inner_TopRight);

            FLinearColor InnerBottomRight;
            DynamicMaterialInstance->GetVectorParameterValue(FName(TEXT("Position_Inner_BottomRight")), InnerBottomRight);
            if (!(InnerBottomRight.R == Position_Inner_BottomRight.X && InnerBottomRight.G == Position_Inner_BottomRight.Y))
                SetPositionInnerBottomRight(Position_Inner_BottomRight);

            FLinearColor InnerBottomLeft;
            DynamicMaterialInstance->GetVectorParameterValue(FName(TEXT("Position_Inner_BottomLeft")), InnerBottomLeft);
            if (!(InnerBottomLeft.R == Position_Inner_BottomLeft.X && InnerBottomLeft.G == Position_Inner_BottomLeft.Y))
                SetPositionInnerBottomLeft(Position_Inner_BottomLeft);

            float Smooth;
            DynamicMaterialInstance->GetScalarParameterValue(FName(TEXT("Smoothness")), Smooth);
            if (Smooth != Smoothness)
                SetSmoothness(Smoothness);

            float OuterMask;
            DynamicMaterialInstance->GetScalarParameterValue(FName(TEXT("Thickness_OuterMask")), OuterMask);
            if (OuterMask != Thickness_OuterMask)
                SetOuterMaskThickness(Thickness_OuterMask);

            float InnerMask;
            DynamicMaterialInstance->GetScalarParameterValue(FName(TEXT("Thickness_InnerMask")), InnerMask);
            if (InnerMask != Thickness_InnerMask)
                SetInnerMaskThickness(Thickness_InnerMask);
        }
    }
}

void UThemedPanelWidget::SetOuterColor(FLinearColor NewValue)
{
    Color_Outer = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("Color_Outer", NewValue);
}

void UThemedPanelWidget::SetInnerColor(FLinearColor NewValue)
{
    Color_Inner = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("Color_Inner", NewValue);
}

void UThemedPanelWidget::SetPositionOuterTopLeft(FVector2D NewValue)
{
    Position_Outer_TopLeft = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("V2_OuterTopLeft", FLinearColor(NewValue.X, NewValue.Y, 0, 1));
}

void UThemedPanelWidget::SetPositionOuterTopRight(FVector2D NewValue)
{
    Position_Outer_TopRight = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("V2_OuterTopRight", FLinearColor(NewValue.X, NewValue.Y, 0, 1));
}

void UThemedPanelWidget::SetPositionOuterBottomRight(FVector2D NewValue)
{
    Position_Outer_BottomRight = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("V2_OuterBottomRight", FLinearColor(NewValue.X, NewValue.Y, 0, 1));
}

void UThemedPanelWidget::SetPositionOuterBottomLeft(FVector2D NewValue)
{
    Position_Outer_BottomLeft = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("V2_OuterBottomLeft", FLinearColor(NewValue.X, NewValue.Y, 0, 1));
}

void UThemedPanelWidget::SetPositionInnerTopLeft(FVector2D NewValue)
{
    Position_Inner_TopLeft = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("V2_InnerTopLeft", FLinearColor(NewValue.X, NewValue.Y, 0, 1));
}

void UThemedPanelWidget::SetPositionInnerTopRight(FVector2D NewValue)
{
    Position_Inner_TopRight = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("V2_InnerTopRight", FLinearColor(NewValue.X, NewValue.Y, 0, 1));
}

void UThemedPanelWidget::SetPositionInnerBottomRight(FVector2D NewValue)
{
    Position_Inner_BottomRight = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("V2_InnerBottomRight", FLinearColor(NewValue.X, NewValue.Y, 0, 1));
}

void UThemedPanelWidget::SetPositionInnerBottomLeft(FVector2D NewValue)
{
    Position_Inner_BottomLeft = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("V2_InnerBottomLeft", FLinearColor(NewValue.X, NewValue.Y, 0, 1));
}

void UThemedPanelWidget::SetSmoothness(float NewValue)
{
    Smoothness = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetScalarParameterValue("Smoothness", NewValue);
}

void UThemedPanelWidget::SetOuterMaskThickness(float NewValue)
{
    Thickness_OuterMask = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetScalarParameterValue("Thickness_OuterMask", NewValue);
}

void UThemedPanelWidget::SetInnerMaskThickness(float NewValue)
{
    Thickness_InnerMask = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetScalarParameterValue("Thickness_InnerMask", NewValue);
}

