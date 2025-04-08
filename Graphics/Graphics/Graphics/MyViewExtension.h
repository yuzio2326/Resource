// MyViewExtension.h

#pragma once

#include "CoreMinimal.h"
#include "RendererInterface.h"
#include "Engine/StaticMesh.h"
#include "SceneViewExtension.h"

class GRAPHICS_API FMyViewExtension : public FSceneViewExtensionBase
{
public:
    FMyViewExtension(const FAutoRegister& AutoRegister);

    virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;
    virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;
    virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;
    
    virtual void PostRenderBasePassDeferred_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView, const FRenderTargetBindingSlots& RenderTargets, TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTextures);

    void SetStaticMesh(UStaticMesh* InStaticMesh);
    void SetColor(const FLinearColor& InColor);

    /**
     * Called if no IsActive functors returned a definitive answer to whether this extension should be active this frame.
     */
    virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const { return true; }

private:
    UStaticMesh* StaticMesh;
    FLinearColor Color;
};
