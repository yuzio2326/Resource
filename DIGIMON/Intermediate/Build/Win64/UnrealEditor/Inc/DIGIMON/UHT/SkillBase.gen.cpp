// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DIGIMON/Skills/SkillBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSkillBase() {}

// Begin Cross Module References
DIGIMON_API UClass* Z_Construct_UClass_ASkillBase();
DIGIMON_API UClass* Z_Construct_UClass_ASkillBase_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AActor();
UPackage* Z_Construct_UPackage__Script_DIGIMON();
// End Cross Module References

// Begin Class ASkillBase
void ASkillBase::StaticRegisterNativesASkillBase()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASkillBase);
UClass* Z_Construct_UClass_ASkillBase_NoRegister()
{
	return ASkillBase::StaticClass();
}
struct Z_Construct_UClass_ASkillBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Skills/SkillBase.h" },
		{ "ModuleRelativePath", "Skills/SkillBase.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASkillBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ASkillBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_DIGIMON,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASkillBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASkillBase_Statics::ClassParams = {
	&ASkillBase::StaticClass,
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
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASkillBase_Statics::Class_MetaDataParams), Z_Construct_UClass_ASkillBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASkillBase()
{
	if (!Z_Registration_Info_UClass_ASkillBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASkillBase.OuterSingleton, Z_Construct_UClass_ASkillBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASkillBase.OuterSingleton;
}
template<> DIGIMON_API UClass* StaticClass<ASkillBase>()
{
	return ASkillBase::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASkillBase);
ASkillBase::~ASkillBase() {}
// End Class ASkillBase

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_user_Desktop_UnrealEngineFiles_DIGIMON_2_DIGIMON_Source_DIGIMON_Skills_SkillBase_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASkillBase, ASkillBase::StaticClass, TEXT("ASkillBase"), &Z_Registration_Info_UClass_ASkillBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASkillBase), 2309824259U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_user_Desktop_UnrealEngineFiles_DIGIMON_2_DIGIMON_Source_DIGIMON_Skills_SkillBase_h_1226219459(TEXT("/Script/DIGIMON"),
	Z_CompiledInDeferFile_FID_Users_user_Desktop_UnrealEngineFiles_DIGIMON_2_DIGIMON_Source_DIGIMON_Skills_SkillBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_user_Desktop_UnrealEngineFiles_DIGIMON_2_DIGIMON_Source_DIGIMON_Skills_SkillBase_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
