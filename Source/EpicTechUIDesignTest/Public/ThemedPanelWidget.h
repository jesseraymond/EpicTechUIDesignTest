// Technical UI Designer Test for Epic Games by Jesse Raymond (June 2021)

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "Components/Border.h"
#include "Components/Overlay.h"
#include "ThemedPanelWidget.generated.h"

/**
 *
 */
UCLASS()
class EPICTECHUIDESIGNTEST_API UThemedPanelWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCosmetic)
        void UpdateDynamicMaterialInstanceProperties();

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
        void SetSmoothness(float NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetOuterMaskThickness(float NewValue);

    UFUNCTION(BlueprintCosmetic)
        void SetInnerMaskThickness(float NewValue);

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UBorder* DynamicMaterialHost;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UOverlay* ContentContainer;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UNamedSlot* ContentSlot;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        UMaterial* DynamicMaterial;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        UMaterialInstanceDynamic* DynamicMaterialInstance;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FLinearColor Color_Outer = FLinearColor(0.181164, 0.913099, 0.40724, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FLinearColor Color_Inner = FLinearColor(0.000304, 0.064803, 0.072272, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Outer_TopLeft = FVector2D(0.0625, 0.0625);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Outer_TopRight = FVector2D(1, 0);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Outer_BottomRight = FVector2D(0.90625, 0.94);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Outer_BottomLeft = FVector2D(0, 1);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Inner_TopLeft = FVector2D(0.1, 0.13);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Inner_TopRight = FVector2D(1, 0.02);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Inner_BottomRight = FVector2D(0.87, 0.88);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FVector2D Position_Inner_BottomLeft = FVector2D(0.005, 0.98);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float Smoothness = 0.005;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float Thickness_OuterMask = 0.25;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float Thickness_InnerMask = 0.35;

    virtual void NativePreConstruct() override;
};
