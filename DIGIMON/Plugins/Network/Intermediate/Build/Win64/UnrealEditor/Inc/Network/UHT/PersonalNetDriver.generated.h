// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PersonalNetDriver.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef NETWORK_PersonalNetDriver_generated_h
#error "PersonalNetDriver.generated.h already included, missing '#pragma once' in PersonalNetDriver.h"
#endif
#define NETWORK_PersonalNetDriver_generated_h

#define FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_PersonalNetDriver_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPersonalNetDriver(); \
	friend struct Z_Construct_UClass_UPersonalNetDriver_Statics; \
public: \
	DECLARE_CLASS(UPersonalNetDriver, UIpNetDriver, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Network"), NO_API) \
	DECLARE_SERIALIZER(UPersonalNetDriver)


#define FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_PersonalNetDriver_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UPersonalNetDriver(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UPersonalNetDriver(UPersonalNetDriver&&); \
	UPersonalNetDriver(const UPersonalNetDriver&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPersonalNetDriver); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPersonalNetDriver); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPersonalNetDriver) \
	NO_API virtual ~UPersonalNetDriver();


#define FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_PersonalNetDriver_h_13_PROLOG
#define FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_PersonalNetDriver_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_PersonalNetDriver_h_16_INCLASS_NO_PURE_DECLS \
	FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_PersonalNetDriver_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> NETWORK_API UClass* StaticClass<class UPersonalNetDriver>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Digimon2_DIGIMON_Plugins_Network_Source_Network_Public_PersonalNetDriver_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
