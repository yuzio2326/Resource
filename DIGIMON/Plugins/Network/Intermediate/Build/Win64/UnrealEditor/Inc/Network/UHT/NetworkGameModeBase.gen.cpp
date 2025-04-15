// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Network/Public/NetworkGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNetworkGameModeBase() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
NETWORK_API UClass* Z_Construct_UClass_ANetworkGameModeBase();
NETWORK_API UClass* Z_Construct_UClass_ANetworkGameModeBase_NoRegister();
NETWORK_API UClass* Z_Construct_UClass_UPersonalNetDriver_NoRegister();
UPackage* Z_Construct_UPackage__Script_Network();
// End Cross Module References

// Begin Class ANetworkGameModeBase
void ANetworkGameModeBase::StaticRegisterNativesANetworkGameModeBase()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ANetworkGameModeBase);
UClass* Z_Construct_UClass_ANetworkGameModeBase_NoRegister()
{
	return ANetworkGameModeBase::StaticClass();
}
struct Z_Construct_UClass_ANetworkGameModeBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "NetworkGameModeBase.h" },
		{ "ModuleRelativePath", "Public/NetworkGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NetDriver_MetaData[] = {
		{ "ModuleRelativePath", "Public/NetworkGameModeBase.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NetDriver;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANetworkGameModeBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ANetworkGameModeBase_Statics::NewProp_NetDriver = { "NetDriver", nullptr, (EPropertyFlags)0x0020080000002000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANetworkGameModeBase, NetDriver), Z_Construct_UClass_UPersonalNetDriver_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NetDriver_MetaData), NewProp_NetDriver_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ANetworkGameModeBase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANetworkGameModeBase_Statics::NewProp_NetDriver,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkGameModeBase_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ANetworkGameModeBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Network,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkGameModeBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ANetworkGameModeBase_Statics::ClassParams = {
	&ANetworkGameModeBase::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ANetworkGameModeBase_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkGameModeBase_Statics::PropPointers),
	0,
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkGameModeBase_Statics::Class_MetaDataParams), Z_Construct_UClass_ANetworkGameModeBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ANetworkGameModeBase()
{
	if (!Z_Registration_Info_UClass_ANetworkGameModeBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANetworkGameModeBase.OuterSingleton, Z_Construct_UClass_ANetworkGameModeBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ANetworkGameModeBase.OuterSingleton;
}
template<> NETWORK_API UClass* StaticClass<ANetworkGameModeBase>()
{
	return ANetworkGameModeBase::StaticClass();
}
ANetworkGameModeBase::ANetworkGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ANetworkGameModeBase);
ANetworkGameModeBase::~ANetworkGameModeBase() {}
// End Class ANetworkGameModeBase

// Begin Registration
struct Z_CompiledInDeferFile_FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_NetworkGameModeBase_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ANetworkGameModeBase, ANetworkGameModeBase::StaticClass, TEXT("ANetworkGameModeBase"), &Z_Registration_Info_UClass_ANetworkGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANetworkGameModeBase), 941866373U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_NetworkGameModeBase_h_2804211369(TEXT("/Script/Network"),
	Z_CompiledInDeferFile_FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_NetworkGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_NetworkGameModeBase_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
