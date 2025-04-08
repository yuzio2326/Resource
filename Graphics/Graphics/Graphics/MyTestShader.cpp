#include "MyTestShader.h"

#if !UE_SERVER
void  FMyShaderVS::InternalDestroy(void* Object, const FTypeLayoutDesc&, const FPointerTableBase* PtrTable, bool bIsFrozen) 
{
    Freeze::DestroyObject(static_cast< FMyShaderVS*>(Object), PtrTable, bIsFrozen);
}

FTypeLayoutDesc& FMyShaderVS::StaticGetTypeLayout() 
{
    static_assert(TValidateInterfaceHelper< FMyShaderVS, InterfaceType>::Value, "Invalid interface for " "FMyShaderVS"); 
    alignas(FTypeLayoutDesc) static uint8 TypeBuffer[sizeof(FTypeLayoutDesc)] = { 0 }; 
    FTypeLayoutDesc& TypeDesc = *(FTypeLayoutDesc*)TypeBuffer; 
    
    if (!TypeDesc.IsInitialized) 
    {
        TypeDesc.IsInitialized = true; 
        TypeDesc.Name = L"FMyShaderVS";
        TypeDesc.WriteFrozenMemoryImageFunc = TGetFreezeImageHelper< FMyShaderVS>::Do(); 
        TypeDesc.UnfrozenCopyFunc = &Freeze::DefaultUnfrozenCopy; 
        TypeDesc.AppendHashFunc = &Freeze::DefaultAppendHash; 
        TypeDesc.GetTargetAlignmentFunc = &Freeze::DefaultGetTargetAlignment; 
        TypeDesc.ToStringFunc = &Freeze::DefaultToString; 
        TypeDesc.DestroyFunc = &InternalDestroy; 
        TypeDesc.Size = sizeof(FMyShaderVS); 
        TypeDesc.Alignment = alignof(FMyShaderVS); 
        TypeDesc.Interface = InterfaceType; 
        TypeDesc.SizeFromFields = ~0u; 
        TypeDesc.GetDefaultObjectFunc = &TGetDefaultObjectHelper< FMyShaderVS, InterfaceType>::Do; InternalLinkType<1>::Initialize(TypeDesc);
        InternalInitializeBases< FMyShaderVS>(TypeDesc); 
        FTypeLayoutDesc::Initialize(TypeDesc);
    } return TypeDesc;
};  

const FTypeLayoutDesc& FMyShaderVS::GetTypeLayout() const 
{
    return StaticGetTypeLayout();
};  

FMyShaderVS::ShaderMetaType& FMyShaderVS::GetStaticType() 
{
    static FMyShaderVS::ShaderMetaType StaticType(FMyShaderVS::StaticGetTypeLayout(), L"FMyShaderVS", L"/KDT3D/MyTest.usf", L"MainVS", SF_Vertex, FMyShaderVS::FPermutationDomain::PermutationCount, FMyShaderVS::ConstructSerializedInstance, FMyShaderVS::ConstructCompiledInstance, FMyShaderVS::ShouldCompilePermutationImpl, FMyShaderVS::GetRayTracingPayloadType, FMyShaderVS::ModifyCompilationEnvironmentImpl, FMyShaderVS::ValidateCompiledResult, sizeof(FMyShaderVS), FMyShaderVS::GetRootParametersMetadata()); return StaticType;
}  

FShaderTypeRegistration FMyShaderVS::ShaderTypeRegistration{ TFunctionRef<::FShaderType & ()>{FMyShaderVS::GetStaticType} };;

//IMPLEMENT_SHADER_TYPE(, FMyShaderVS, TEXT("/KDT3D/MyTest.usf"), TEXT("MainVS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FMyShaderPS, TEXT("/KDT3D/MyTest.usf"), TEXT("MainPS"), SF_Pixel);
IMPLEMENT_UNIFORM_BUFFER_STRUCT(FMyShaderParameters, "MyShaderParameters");
#endif