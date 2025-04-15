// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNetwork_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Network;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Network()
	{
		if (!Z_Registration_Info_UPackage__Script_Network.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Network",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x14E6FF61,
				0x5A2758D5,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Network.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Network.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Network(Z_Construct_UPackage__Script_Network, TEXT("/Script/Network"), Z_Registration_Info_UPackage__Script_Network, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x14E6FF61, 0x5A2758D5));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
