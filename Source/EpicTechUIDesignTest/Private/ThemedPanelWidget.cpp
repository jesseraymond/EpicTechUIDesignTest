// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)


#include "ThemedPanelWidget.h"
#include "Components/BorderSlot.h"
#include "Components/CanvasPanelSlot.h"

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

            if (ContentContainer)
                if (UBorderSlot* BorderSlot = Cast<UBorderSlot>(ContentContainer->Slot))
                       BorderSlot->SetPadding(Padding_Content);

            SetOuterColor(Color_Outer);
            SetInnerColor(Color_Inner);
            SetPositionOuterTopLeft(Position_Outer_TopLeft);
            SetPositionOuterTopRight(Position_Outer_TopRight);
            SetPositionOuterBottomRight(Position_Outer_BottomRight);
            SetPositionOuterBottomLeft(Position_Outer_BottomLeft);
            SetPositionInnerTopLeft(Position_Inner_TopLeft);
            SetPositionInnerTopRight(Position_Inner_TopRight);
            SetPositionInnerBottomRight(Position_Inner_BottomRight);
            SetPositionInnerBottomLeft(Position_Inner_BottomLeft);
            SetBlur(Blur);
        }
    }
}

void UThemedPanelWidget::SetContentPadding(FMargin NewValue)
{
    Padding_Content = NewValue;

    if (ContentContainer)
        if (UBorderSlot* BorderSlot = Cast<UBorderSlot>(ContentContainer->Slot))
            BorderSlot->SetPadding(Padding_Content);
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
    SynchronizeProperties();
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

void UThemedPanelWidget::SetBlur(FVector2D NewValue)
{
    Blur = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("V2_Blur", FLinearColor(NewValue.X, NewValue.Y, 0, 1));
}

