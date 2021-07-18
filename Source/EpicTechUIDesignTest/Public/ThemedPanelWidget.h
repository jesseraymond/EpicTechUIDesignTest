// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "Components/Border.h"
#include "Components/Overlay.h"
#include "Components/SizeBox.h"
#include "Layout/Margin.h"
#include "ThemedPanelWidget.generated.h"


UCLASS()
class EPICTECHUIDESIGNTEST_API UThemedPanelWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UPanelWidget* PanelRootContainer;

    UFUNCTION(BlueprintCosmetic)
        void UpdateDynamicMaterialInstanceProperties();

    UFUNCTION(BlueprintCosmetic)
        void SetContentPadding(FMargin NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetOuterColor(FLinearColor NewValue);
    
    UFUNCTION(BlueprintCosmetic)
        void SetInnerColor(FLinearColor NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetPositionOuterTopLeft(FVector2D NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetPositionOuterTopRight(FVector2D NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetPositionOuterBottomRight(FVector2D NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetPositionOuterBottomLeft(FVector2D NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetPositionInnerTopLeft(FVector2D NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetPositionInnerTopRight(FVector2D NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetPositionInnerBottomRight(FVector2D NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetPositionInnerBottomLeft(FVector2D NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetBlur(FVector2D NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetMaterialScale(FVector2D NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetBrushSize(FVector2D NewValue = FVector2D::ZeroVector);

    UFUNCTION(BlueprintCosmetic)
        void SetWidgetSize(FVector2D NewValue = FVector2D::ZeroVector);

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UBorder* DynamicMaterialHost;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UOverlay* ContentContainer;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UNamedSlot* ContentSlot;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class USizeBox* SizeControl;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Size_Widget = FVector2D::ZeroVector;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Size_Brush = FVector2D(32, 32);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Scale_Material = FVector2D(1, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FMargin Padding_Content = FMargin(70, 35);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        UMaterial* DynamicMaterial;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        UMaterialInstanceDynamic* DynamicMaterialInstance;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FLinearColor Color_Outer = FLinearColor(1, 1, 1, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FLinearColor Color_Inner = FLinearColor(0.003677, 0.274677, 0.219526, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Outer_TopLeft = FVector2D(0.35,0.35);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Outer_TopRight = FVector2D(1.05, 0);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Outer_BottomLeft = FVector2D(-0.05, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Outer_BottomRight = FVector2D(0.5, 0.8);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Inner_TopLeft = FVector2D(0.75, 0.8);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Inner_TopRight = FVector2D(0.9, 0.2);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Inner_BottomLeft = FVector2D(0.15, 0.9);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Inner_BottomRight = FVector2D(0.25, 0.55);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Blur = FVector2D(0.04, 0.04);

    virtual void NativePreConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
