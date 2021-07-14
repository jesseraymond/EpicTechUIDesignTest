// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)


#include "ThemedPanelWidget.h"
#include "Components/OverlaySlot.h"
#include "Components/CanvasPanelSlot.h"

void UThemedPanelWidget::NativePreConstruct()
{
    Super::NativePreConstruct();
    UpdateDynamicMaterialInstanceProperties();
}

void UThemedPanelWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    SetWidgetSize(Size_Widget);
}

void UThemedPanelWidget::UpdateDynamicMaterialInstanceProperties()
{
    if (DynamicMaterialHost)
    {
        if (DynamicMaterial && !DynamicMaterialInstance)
        {
            DynamicMaterialInstance = UMaterialInstanceDynamic::Create(DynamicMaterial, this);
            DynamicMaterialHost->SetBrushFromMaterial(DynamicMaterialInstance);
        }

        if (DynamicMaterialInstance)
        {
            SetContentPadding(Padding_Content);
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
            SetMaterialScale(Scale_Material);
            SetBrushSize(Size_Brush);
            SetWidgetSize(Size_Widget);
        }
    }
}

void UThemedPanelWidget::SetContentPadding(FMargin NewValue)
{
    Padding_Content = NewValue;

    if (ContentContainer)
        if (UOverlaySlot* ContentContainerSlot = Cast<UOverlaySlot>(ContentContainer->Slot))
            ContentContainerSlot->SetPadding(Padding_Content);
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

void UThemedPanelWidget::SetBlur(FVector2D NewValue)
{
    Blur = NewValue;

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("V2_Blur", FLinearColor(NewValue.X, NewValue.Y, 0, 1));
}

void UThemedPanelWidget::SetMaterialScale(FVector2D NewValue)
{
    Scale_Material = NewValue;

    if (DynamicMaterialHost)
        DynamicMaterialHost->SetRenderScale(NewValue);
}

void UThemedPanelWidget::SetBrushSize(FVector2D NewValue)
{
    if (DynamicMaterialHost)
        DynamicMaterialHost->Background.SetImageSize(NewValue);

    if (DynamicMaterialInstance)
        DynamicMaterialInstance->SetVectorParameterValue("V2_BrushSize", FLinearColor(NewValue.X, NewValue.Y, 0, 1));
}

void UThemedPanelWidget::SetWidgetSize(FVector2D NewValue)
{

    if (NewValue == FVector2D::ZeroVector && DynamicMaterialHost)
    {
        FVector2D DesiredSize = DynamicMaterialHost->GetDesiredSize();
        FVector2D LocalSize = DynamicMaterialHost->GetCachedGeometry().GetLocalSize();
        ForceLayoutPrepass();

        if (DesiredSize != FVector2D::ZeroVector)
        {
            NewValue = DesiredSize;
        }
        else if (LocalSize != FVector2D::ZeroVector)
        {
            NewValue = LocalSize;
        }
        else if (UCanvasPanelSlot* RootWidgetSlot = Cast<UCanvasPanelSlot>(Slot))
        {
            if (RootWidgetSlot->GetSize() != FVector2D::ZeroVector)
                NewValue = RootWidgetSlot->GetSize();
        }
    }

    if (NewValue != FVector2D::ZeroVector)
    {
        if (SizeControl)
        {
            SizeControl->bOverride_HeightOverride = true;
            SizeControl->bOverride_WidthOverride = true;
            SizeControl->SetWidthOverride(NewValue.X);
            SizeControl->SetHeightOverride(NewValue.Y);
        }
    }

    if (DynamicMaterialInstance)
    {
        DynamicMaterialInstance->SetVectorParameterValue("V2_WidgetSize", FLinearColor(NewValue.X, NewValue.Y, 0, 1));
    }
}

