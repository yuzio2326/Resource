// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Network/Public/CustomIpConnection.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCustomIpConnection() {}

// Begin Cross Module References
NETWORK_API UClass* Z_Construct_UClass_UCustomIpConnection();
NETWORK_API UClass* Z_Construct_UClass_UCustomIpConnection_NoRegister();
ONLINESUBSYSTEMUTILS_API UClass* Z_Construct_UClass_UIpConnection();
UPackage* Z_Construct_UPackage__Script_Network();
// End Cross Module References

// Begin Class UCustomIpConnection
void UCustomIpConnection::StaticRegisterNativesUCustomIpConnection()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCustomIpConnection);
UClass* Z_Construct_UClass_UCustomIpConnection_NoRegister()
{
	return UCustomIpConnection::StaticClass();
}
struct Z_Construct_UClass_UCustomIpConnection_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "CustomIpConnection.h" },
		{ "ModuleRelativePath", "Public/CustomIpConnection.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCustomIpConnection>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UCustomIpConnection_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UIpConnection,
	(UObject* (*)())Z_Construct_UPackage__Script_Network,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomIpConnection_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCustomIpConnection_Statics::ClassParams = {
	&UCustomIpConnection::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomIpConnection_Statics::Class_MetaDataParams), Z_Construct_UClass_UCustomIpConnection_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCustomIpConnection()
{
	if (!Z_Registration_Info_UClass_UCustomIpConnection.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCustomIpConnection.OuterSingleton, Z_Construct_UClass_UCustomIpConnection_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCustomIpConnection.OuterSingleton;
}
template<> NETWORK_API UClass* StaticClass<UCustomIpConnection>()
{
	return UCustomIpConnection::StaticClass();
}
UCustomIpConnection::UCustomIpConnection(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCustomIpConnection);
UCustomIpConnection::~UCustomIpConnection() {}
// End Class UCustomIpConnection

// Begin Registration
struct Z_CompiledInDeferFile_FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_CustomIpConnection_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCustomIpConnection, UCustomIpConnection::StaticClass, TEXT("UCustomIpConnection"), &Z_Registration_Info_UClass_UCustomIpConnection, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCustomIpConnection), 1234251505U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_CustomIpConnection_h_1403417889(TEXT("/Script/Network"),
	Z_CompiledInDeferFile_FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_CustomIpConnection_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_CustomIpConnection_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
