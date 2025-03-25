// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DIGIMON/DIGIMONGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDIGIMONGameMode() {}

// Begin Cross Module References
DIGIMON_API UClass* Z_Construct_UClass_ADIGIMONGameMode();
DIGIMON_API UClass* Z_Construct_UClass_ADIGIMONGameMode_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_DIGIMON();
// End Cross Module References

// Begin Class ADIGIMONGameMode
void ADIGIMONGameMode::StaticRegisterNativesADIGIMONGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ADIGIMONGameMode);
UClass* Z_Construct_UClass_ADIGIMONGameMode_NoRegister()
{
	return ADIGIMONGameMode::StaticClass();
}
struct Z_Construct_UClass_ADIGIMONGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "DIGIMONGameMode.h" },
		{ "ModuleRelativePath", "DIGIMONGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADIGIMONGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ADIGIMONGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_DIGIMON,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADIGIMONGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ADIGIMONGameMode_Statics::ClassParams = {
	&ADIGIMONGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADIGIMONGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ADIGIMONGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ADIGIMONGameMode()
{
	if (!Z_Registration_Info_UClass_ADIGIMONGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADIGIMONGameMode.OuterSingleton, Z_Construct_UClass_ADIGIMONGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ADIGIMONGameMode.OuterSingleton;
}
template<> DIGIMON_API UClass* StaticClass<ADIGIMONGameMode>()
{
	return ADIGIMONGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ADIGIMONGameMode);
ADIGIMONGameMode::~ADIGIMONGameMode() {}
// End Class ADIGIMONGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_user_Desktop_UnrealEngineFiles_DIGIMON_2_DIGIMON_Source_DIGIMON_DIGIMONGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADIGIMONGameMode, ADIGIMONGameMode::StaticClass, TEXT("ADIGIMONGameMode"), &Z_Registration_Info_UClass_ADIGIMONGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADIGIMONGameMode), 3774519997U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_user_Desktop_UnrealEngineFiles_DIGIMON_2_DIGIMON_Source_DIGIMON_DIGIMONGameMode_h_2533192622(TEXT("/Script/DIGIMON"),
	Z_CompiledInDeferFile_FID_Users_user_Desktop_UnrealEngineFiles_DIGIMON_2_DIGIMON_Source_DIGIMON_DIGIMONGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_user_Desktop_UnrealEngineFiles_DIGIMON_2_DIGIMON_Source_DIGIMON_DIGIMONGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
