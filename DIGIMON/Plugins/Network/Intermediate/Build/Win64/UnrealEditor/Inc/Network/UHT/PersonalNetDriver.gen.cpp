// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Network/Public/PersonalNetDriver.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePersonalNetDriver() {}

// Begin Cross Module References
NETWORK_API UClass* Z_Construct_UClass_UPersonalNetDriver();
NETWORK_API UClass* Z_Construct_UClass_UPersonalNetDriver_NoRegister();
ONLINESUBSYSTEMUTILS_API UClass* Z_Construct_UClass_UIpNetDriver();
UPackage* Z_Construct_UPackage__Script_Network();
// End Cross Module References

// Begin Class UPersonalNetDriver
void UPersonalNetDriver::StaticRegisterNativesUPersonalNetDriver()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UPersonalNetDriver);
UClass* Z_Construct_UClass_UPersonalNetDriver_NoRegister()
{
	return UPersonalNetDriver::StaticClass();
}
struct Z_Construct_UClass_UPersonalNetDriver_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "PersonalNetDriver.h" },
		{ "ModuleRelativePath", "Public/PersonalNetDriver.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPersonalNetDriver>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UPersonalNetDriver_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UIpNetDriver,
	(UObject* (*)())Z_Construct_UPackage__Script_Network,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPersonalNetDriver_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UPersonalNetDriver_Statics::ClassParams = {
	&UPersonalNetDriver::StaticClass,
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
	0x001000ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UPersonalNetDriver_Statics::Class_MetaDataParams), Z_Construct_UClass_UPersonalNetDriver_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UPersonalNetDriver()
{
	if (!Z_Registration_Info_UClass_UPersonalNetDriver.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPersonalNetDriver.OuterSingleton, Z_Construct_UClass_UPersonalNetDriver_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UPersonalNetDriver.OuterSingleton;
}
template<> NETWORK_API UClass* StaticClass<UPersonalNetDriver>()
{
	return UPersonalNetDriver::StaticClass();
}
UPersonalNetDriver::UPersonalNetDriver(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UPersonalNetDriver);
UPersonalNetDriver::~UPersonalNetDriver() {}
// End Class UPersonalNetDriver

// Begin Registration
struct Z_CompiledInDeferFile_FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_PersonalNetDriver_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UPersonalNetDriver, UPersonalNetDriver::StaticClass, TEXT("UPersonalNetDriver"), &Z_Registration_Info_UClass_UPersonalNetDriver, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPersonalNetDriver), 1786912974U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_PersonalNetDriver_h_4185156071(TEXT("/Script/Network"),
	Z_CompiledInDeferFile_FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_PersonalNetDriver_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_PersonalNetDriver_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
