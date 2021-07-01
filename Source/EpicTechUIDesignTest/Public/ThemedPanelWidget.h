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
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UBorder* OuterBorder;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UBorder* InnerBorder;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UOverlay* ContentContainer;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Widgets")
        class UNamedSlot* ContentSlot;
    
    UPROPERTY(EditAnywhere)
        FLinearColor Color_OuterBorder = FLinearColor(0.181164, 0.913099, 0.40724, 1);

    UPROPERTY(EditAnywhere)
        FLinearColor Color_InnerBorder = FLinearColor(0.000304, 0.064803, 0.072272, 1);
    
    UPROPERTY(EditAnywhere)
        FVector2D Shear_OuterBorder = FVector2D(-4, -2);
    
    UPROPERTY(EditAnywhere)
        FVector2D Shear_InnerBorder = FVector2D(-8, 0);
    
    UPROPERTY(EditAnywhere)
        float Angle_Rotation_OuterBorder = 1;
    
    UPROPERTY(EditAnywhere)
        float Angle_Rotation_InnerBorder = -1;

    UPROPERTY(EditAnywhere)
        float UniformPadding_InnerBorder = 9;

    UFUNCTION(BlueprintCosmetic)
        void SetOuterBorderColor(FLinearColor NewColor);
    
    UFUNCTION(BlueprintCosmetic)
        void SetInnerBorderColor(FLinearColor NewColor);
    
    UFUNCTION(BlueprintCosmetic)
        void SetOuterBorderShear(FVector2D NewShear);
    
    UFUNCTION(BlueprintCosmetic)
        void SetInnerBorderShear(FVector2D NewShear);
    
    UFUNCTION(BlueprintCosmetic)
        void SetOuterBorderRotation(float NewRotation);
    
    UFUNCTION(BlueprintCosmetic)
        void SetInnerBorderRotation(float NewRotation);

    UFUNCTION(BlueprintCosmetic)
        void SetInnerBorderUniformPadding(float NewValue);

    protected:
        virtual void NativePreConstruct() override;
};
