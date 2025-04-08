// MyShaderParameters.h

#pragma once

#include "CoreMinimal.h"
#include "UniformBuffer.h"
#include "ShaderParameters.h"
#include "GlobalShader.h"
#include "ShaderParameterUtils.h"
#include "RHIStaticStates.h"

BEGIN_UNIFORM_BUFFER_STRUCT(FMyShaderParameters, )
    SHADER_PARAMETER(FMatrix44f, WorldMatrix)
    SHADER_PARAMETER(FMatrix44f, ViewMatrix)
    SHADER_PARAMETER(FMatrix44f, ProjectionMatrix)
END_UNIFORM_BUFFER_STRUCT()

typedef TUniformBufferRef<FMyShaderParameters> FMyShaderParametersRef;

class FMyShaderVS : public FGlobalShader
{
    DECLARE_SHADER_TYPE(FMyShaderVS, Global);

public:
    FMyShaderVS() {}
    FMyShaderVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
        : FGlobalShader(Initializer)
    {
        // 유니폼 버퍼 바인딩
        MyShaderParameters.Bind(Initializer.ParameterMap, TEXT("MyShaderParameters"));
    }

    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
    {
        return true;
    }
    void SetParameters(FRHIBatchedShaderParameters& BatchedParameters, FMyShaderParametersRef& ShaderParametersRef) 
    {
        SetUniformBufferParameter(BatchedParameters, GetUniformBufferParameter<FMyShaderParameters>(), ShaderParametersRef);
    }

private:
    LAYOUT_FIELD(FShaderUniformBufferParameter, MyShaderParameters)
};

class FMyShaderPS : public FGlobalShader
{
    DECLARE_SHADER_TYPE(FMyShaderPS, Global);

public:
    FMyShaderPS() {}
    FMyShaderPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
        : FGlobalShader(Initializer)
    {
    }

    static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
    {
        return true;
    }
};