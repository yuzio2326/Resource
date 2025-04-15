// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CustomIpConnection.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef NETWORK_CustomIpConnection_generated_h
#error "CustomIpConnection.generated.h already included, missing '#pragma once' in CustomIpConnection.h"
#endif
#define NETWORK_CustomIpConnection_generated_h

#define FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_CustomIpConnection_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCustomIpConnection(); \
	friend struct Z_Construct_UClass_UCustomIpConnection_Statics; \
public: \
	DECLARE_CLASS(UCustomIpConnection, UIpConnection, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Network"), NO_API) \
	DECLARE_SERIALIZER(UCustomIpConnection)


#define FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_CustomIpConnection_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCustomIpConnection(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UCustomIpConnection(UCustomIpConnection&&); \
	UCustomIpConnection(const UCustomIpConnection&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCustomIpConnection); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCustomIpConnection); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCustomIpConnection) \
	NO_API virtual ~UCustomIpConnection();


#define FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_CustomIpConnection_h_12_PROLOG
#define FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_CustomIpConnection_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_CustomIpConnection_h_15_INCLASS_NO_PURE_DECLS \
	FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_CustomIpConnection_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> NETWORK_API UClass* StaticClass<class UCustomIpConnection>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_CustomIpConnection_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
