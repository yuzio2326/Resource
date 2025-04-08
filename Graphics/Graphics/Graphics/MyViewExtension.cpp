// MyViewExtension.cpp

#include "MyViewExtension.h"
#include "RHIStaticStates.h"
#include "ShaderParameterUtils.h"
#include "GlobalShader.h"
#include "MyTestShader.h"
#include "RenderGraphBuilder.h"
#include "CommonRenderResources.h"

FMyViewExtension::FMyViewExtension(const FAutoRegister& AutoRegister)
    : FSceneViewExtensionBase(AutoRegister), StaticMesh(nullptr), Color(FLinearColor::White)
{
}

void FMyViewExtension::SetupViewFamily(FSceneViewFamily& InViewFamily)
{
    // ViewFamily 설정
}

void FMyViewExtension::SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView)
{
    // View 설정
}

void FMyViewExtension::BeginRenderViewFamily(FSceneViewFamily& InViewFamily)
{
    // 렌더링 초기 설정
}

//void FMyViewExtension::PostRenderBasePassDeferred_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView, const FRenderTargetBindingSlots& RenderTargets, TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTextures)
//{
//    UE_LOG(LogTemp, Warning, TEXT("PostRenderBasePassDeferred_RenderThread called"));
//
//    TShaderMapRef<FMyShaderVS> MyShaderVS(GetGlobalShaderMap(GMaxRHIFeatureLevel));
//    TShaderMapRef<FMyShaderPS> MyShaderPS(GetGlobalShaderMap(GMaxRHIFeatureLevel));
//
//    FGraphicsPipelineStateInitializer GraphicsPSOInit;
//    GraphBuilder.RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
//
//    GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GFilterVertexDeclaration.VertexDeclarationRHI;
//    GraphicsPSOInit.BoundShaderState.VertexShaderRHI = MyShaderVS.GetVertexShader();
//    GraphicsPSOInit.BoundShaderState.PixelShaderRHI = MyShaderPS.GetPixelShader();
//    GraphicsPSOInit.PrimitiveType = PT_TriangleList;
//
//    GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
//    GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
//    GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
//
//    SetGraphicsPipelineState(GraphBuilder.RHICmdList, GraphicsPSOInit);
//
//    GraphBuilder.RHICmdList.DrawPrimitive(0, 1, 1); // 하나의 삼각형을 드로우
//}

void FMyViewExtension::SetStaticMesh(UStaticMesh* InStaticMesh)
{
    StaticMesh = InStaticMesh;
}

void FMyViewExtension::SetColor(const FLinearColor& InColor)
{
    Color = InColor;
}

BEGIN_SHADER_PARAMETER_STRUCT(FMyViewExtensionDrawPassParameters, )
    RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()


void FMyViewExtension::PostRenderBasePassDeferred_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView, const FRenderTargetBindingSlots& RenderTargets, TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTextures)
{
    // 파라미터 할당 및 설정
    FMyViewExtensionDrawPassParameters* PassParameters = GraphBuilder.AllocParameters<FMyViewExtensionDrawPassParameters>();
    PassParameters->RenderTargets = RenderTargets;

    // 패스 추가
    GraphBuilder.AddPass(
        RDG_EVENT_NAME("MyViewExtensionDrawPass"),
        PassParameters,
        ERDGPassFlags::Raster,
        [this, &InView](FRHICommandList& RHICmdList)
        {
            TShaderMapRef<FMyShaderVS> MyShaderVS(GetGlobalShaderMap(GMaxRHIFeatureLevel));
            TShaderMapRef<FMyShaderPS> MyShaderPS(GetGlobalShaderMap(GMaxRHIFeatureLevel));

            FStaticMeshRenderData* RenderData = StaticMesh->GetRenderData();
            const FStaticMeshLODResources& LODResource = RenderData->LODResources[0];

            // 정점 데이터 추출
            TResourceArray<FVector3f> PositionData;
            for (int32 i = 0; i < LODResource.GetNumVertices(); ++i)
            {
                PositionData.Add(FVector3f(LODResource.VertexBuffers.PositionVertexBuffer.VertexPosition(i)));
            }

            // Vertex Buffer 생성
            FRHIResourceCreateInfo CreateInfo(TEXT("MyVertexBuffer"), &PositionData);
            FBufferRHIRef VertexBufferRHI = RHICmdList.CreateVertexBuffer(PositionData.GetResourceDataSize(), BUF_Static, CreateInfo);
            if (!VertexBufferRHI)
            {
                UE_LOG(LogTemp, Warning, TEXT("VertexBufferRHI creation failed"));
                return;
            }
            /*void* VertexBufferData = RHILockBuffer(VertexBufferRHI, 0, PositionData.Num() * sizeof(FVector3f), RLM_WriteOnly);
            if (!VertexBufferData)
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to lock VertexBufferRHI"));
                return;
            }
            FMemory::Memcpy(VertexBufferData, PositionData.GetData(), PositionData.Num() * sizeof(FVector3f));
            RHIUnlockBuffer(VertexBufferRHI);*/

            // Vertex Declaration 설정
            FVertexDeclarationElementList Elements;
            Elements.Add(FVertexElement(0, 0, VET_Float3, 0, sizeof(FVector3f), false));
            FVertexDeclarationRHIRef VertexDeclarationRHI = RHICreateVertexDeclaration(Elements);

            if (!VertexDeclarationRHI.IsValid())
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to create VertexDeclarationRHI"));
                return;
            }

            // 월드, 뷰, 프로젝션 행렬 설정
            FMatrix44f WorldMatrix = FMatrix44f::Identity;
            FMatrix44f ViewMatrix = FMatrix44f(InView.ViewMatrices.GetViewMatrix());
            FMatrix44f ProjectionMatrix = FMatrix44f(InView.ViewMatrices.GetProjectionMatrix());

            FMyShaderParameters MyShaderParameters;
            MyShaderParameters.WorldMatrix = WorldMatrix;
            MyShaderParameters.ViewMatrix = ViewMatrix;
            MyShaderParameters.ProjectionMatrix = ProjectionMatrix;

            FMyShaderParametersRef ShaderParametersRef = TUniformBufferRef<FMyShaderParameters>::CreateUniformBufferImmediate(MyShaderParameters, UniformBuffer_SingleFrame);
            if (!ShaderParametersRef.IsValid())
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to create ShaderParametersRef"));
                return;
            }

            // 그래픽 파이프라인 상태 설정 및 렌더링 명령 실행
            {
                FGraphicsPipelineStateInitializer GraphicsPSOInit;
                RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
                GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = VertexDeclarationRHI;
                GraphicsPSOInit.BoundShaderState.VertexShaderRHI = MyShaderVS.GetVertexShader();
                GraphicsPSOInit.BoundShaderState.PixelShaderRHI = MyShaderPS.GetPixelShader();
                GraphicsPSOInit.PrimitiveType = PT_TriangleList;

                GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false>::GetRHI();
                GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
                GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
                SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

                FRHIBatchedShaderParameters BatchedParameters;
                MyShaderVS->SetParameters(BatchedParameters, ShaderParametersRef);
                RHICmdList.SetBatchedShaderParameters(MyShaderVS.GetVertexShader(), BatchedParameters);
                RHICmdList.SetStreamSource(0, VertexBufferRHI, 0);
                RHICmdList.DrawIndexedPrimitive(
                    LODResource.IndexBuffer.IndexBufferRHI,
                    0,
                    0,
                    LODResource.GetNumVertices(),
                    0,
                    LODResource.GetNumTriangles(),
                    1
                );
            }
        }
    );
}
