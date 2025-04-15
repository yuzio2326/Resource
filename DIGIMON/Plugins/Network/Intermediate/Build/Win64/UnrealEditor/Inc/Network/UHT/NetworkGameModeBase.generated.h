// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "NetworkGameModeBase.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef NETWORK_NetworkGameModeBase_generated_h
#error "NetworkGameModeBase.generated.h already included, missing '#pragma once' in NetworkGameModeBase.h"
#endif
#define NETWORK_NetworkGameModeBase_generated_h

#define FID_Users_user_Desktop_UnrealEngineFiles_Resource_DIGIMON_Plugins_Network_Source_Network_Public_NetworkGameModeBase_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesANetworkGameModeBase(); \
	friend struct Z_Construct_UClass_ANetworkGameModeBase_Statics; \
public: \
	DECLARE_CLASS(ANetworkGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Network"), NO_API) \
	DECLARE_SERIALIZER(ANetworkGameModeBase)


#define FID_Users_user_Desktop_UnrealEngineFiles_Resource_DIGIMON_Plugins_Network_Source_Network_Public_NetworkGameModeBase_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ANetworkGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ANetworkGameModeBase(ANetworkGameModeBase&&); \
	ANetworkGameModeBase(const ANetworkGameModeBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANetworkGameModeBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANetworkGameModeBase); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ANetworkGameModeBase) \
	NO_API virtual ~ANetworkGameModeBase();


#define FID_Users_user_Desktop_UnrealEngineFiles_Resource_DIGIMON_Plugins_Network_Source_Network_Public_NetworkGameModeBase_h_13_PROLOG
#define FID_Users_user_Desktop_UnrealEngineFiles_Resource_DIGIMON_Plugins_Network_Source_Network_Public_NetworkGameModeBase_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_user_Desktop_UnrealEngineFiles_Resource_DIGIMON_Plugins_Network_Source_Network_Public_NetworkGameModeBase_h_16_INCLASS_NO_PURE_DECLS \
	FID_Users_user_Desktop_UnrealEngineFiles_Resource_DIGIMON_Plugins_Network_Source_Network_Public_NetworkGameModeBase_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> NETWORK_API UClass* StaticClass<class ANetworkGameModeBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_user_Desktop_UnrealEngineFiles_Resource_DIGIMON_Plugins_Network_Source_Network_Public_NetworkGameModeBase_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
