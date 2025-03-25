// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DIGIMON/Components/SkillComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSkillComponent() {}

// Begin Cross Module References
DIGIMON_API UClass* Z_Construct_UClass_USkillComponent();
DIGIMON_API UClass* Z_Construct_UClass_USkillComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
UPackage* Z_Construct_UPackage__Script_DIGIMON();
// End Cross Module References

// Begin Class USkillComponent
void USkillComponent::StaticRegisterNativesUSkillComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USkillComponent);
UClass* Z_Construct_UClass_USkillComponent_NoRegister()
{
	return USkillComponent::StaticClass();
}
struct Z_Construct_UClass_USkillComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Components/SkillComponent.h" },
		{ "ModuleRelativePath", "Components/SkillComponent.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USkillComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_USkillComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_DIGIMON,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USkillComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USkillComponent_Statics::ClassParams = {
	&USkillComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USkillComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_USkillComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USkillComponent()
{
	if (!Z_Registration_Info_UClass_USkillComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USkillComponent.OuterSingleton, Z_Construct_UClass_USkillComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USkillComponent.OuterSingleton;
}
template<> DIGIMON_API UClass* StaticClass<USkillComponent>()
{
	return USkillComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(USkillComponent);
USkillComponent::~USkillComponent() {}
// End Class USkillComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_user_Desktop_UnrealEngineFiles_DIGIMON_2_DIGIMON_Source_DIGIMON_Components_SkillComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USkillComponent, USkillComponent::StaticClass, TEXT("USkillComponent"), &Z_Registration_Info_UClass_USkillComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USkillComponent), 1186157989U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_user_Desktop_UnrealEngineFiles_DIGIMON_2_DIGIMON_Source_DIGIMON_Components_SkillComponent_h_3921369122(TEXT("/Script/DIGIMON"),
	Z_CompiledInDeferFile_FID_Users_user_Desktop_UnrealEngineFiles_DIGIMON_2_DIGIMON_Source_DIGIMON_Components_SkillComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_user_Desktop_UnrealEngineFiles_DIGIMON_2_DIGIMON_Source_DIGIMON_Components_SkillComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
