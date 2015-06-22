#
# Source with only minor changes:
# https://github.com/assimp/assimp/blob/master/workspaces/Android-NDK/jni/Android.mk
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := assimp_static
ASSIMP_SRC_DIR = code

FILE_LIST := $(wildcard $(LOCAL_PATH)/$(ASSIMP_SRC_DIR)/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/contrib/openddlparser/code/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/contrib/unzip/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/contrib/poly2tri/poly2tri/*/*.cc)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES += contrib/clipper/clipper.cpp \
	contrib/ConvertUTF/ConvertUTF.c \
	contrib/irrXML/irrXML.cpp

# enables -frtti and -fexceptions
LOCAL_CPP_FEATURES := exceptions
# identifier 'nullptr' will become a keyword in C++0x [-Wc++0x-compat]
# but next breaks blender and other importer
# LOCAL_CFLAGS += -std=c++11

# cant be disabled? rudamentary function?
#       -DASSIMP_BUILD_NO_FLIPWINDING_PROCESS  \
#
DontBuildProcess = \
	-DASSIMP_BUILD_NO_FLIPUVS_PROCESS  \
	-DASSIMP_BUILD_NO_MAKELEFTHANDED_PROCESS \
	-DASSIMP_BUILD_NO_CALCTANGENTS_PROCESS \
	-DASSIMP_BUILD_NO_DEBONE_PROCESS \
	-DASSIMP_BUILD_NO_FINDDEGENERATES_PROCESS \
	-DASSIMP_BUILD_NO_FINDINSTANCES_PROCESS \
	-DASSIMP_BUILD_NO_FINDINVALIDDATA_PROCESS \
	-DASSIMP_BUILD_NO_FIXINFACINGNORMALS_PROCESS \
	-DASSIMP_BUILD_NO_GENFACENORMALS_PROCESS \
	-DASSIMP_BUILD_NO_GENUVCOORDS_PROCESS \
	-DASSIMP_BUILD_NO_GENVERTEXNORMALS_PROCESS \
	-DASSIMP_BUILD_NO_IMPROVECACHELOCALITY_PROCESS \
	-DASSIMP_BUILD_NO_JOINVERTICES_PROCESS \
	-DASSIMP_BUILD_NO_LIMITBONEWEIGHTS_PROCESS \
	-DASSIMP_BUILD_NO_OPTIMIZEGRAPH_PROCESS \
	-DASSIMP_BUILD_NO_OPTIMIZEMESHES_PROCESS \
	-DASSIMP_BUILD_NO_PRETRANSFORMVERTICES_PROCESS \
	-DASSIMP_BUILD_NO_REMOVEVC_PROCESS \
	-DASSIMP_BUILD_NO_REMOVE_REDUNDANTMATERIALS_PROCESS \
	-DASSIMP_BUILD_NO_SORTBYPTYPE_PROCESS \
	-DASSIMP_BUILD_NO_SPLITBYBONECOUNT_PROCESS \
	-DASSIMP_BUILD_NO_SPLITLARGEMESHES_PROCESS \
	-DASSIMP_BUILD_NO_TRANSFORMTEXCOORDS_PROCESS \
	-DASSIMP_BUILD_NO_TRIANGULATE_PROCESS \
	-DASSIMP_BUILD_NO_VALIDATEDS_PROCESS

DontBuildImporters = \
	-DASSIMP_BUILD_NO_X_IMPORTER \
	-DASSIMP_BUILD_NO_3DS_IMPORTER \
	-DASSIMP_BUILD_NO_MD3_IMPORTER \
	-DASSIMP_BUILD_NO_MDL_IMPORTER \
	-DASSIMP_BUILD_NO_MD2_IMPORTER \
	-DASSIMP_BUILD_NO_PLY_IMPORTER \
	-DASSIMP_BUILD_NO_ASE_IMPORTER \
	-DASSIMP_BUILD_NO_HMP_IMPORTER \
	-DASSIMP_BUILD_NO_SMD_IMPORTER \
	-DASSIMP_BUILD_NO_MDC_IMPORTER \
	-DASSIMP_BUILD_NO_MD5_IMPORTER \
	-DASSIMP_BUILD_NO_STL_IMPORTER \
	-DASSIMP_BUILD_NO_LWO_IMPORTER \
	-DASSIMP_BUILD_NO_DXF_IMPORTER \
	-DASSIMP_BUILD_NO_NFF_IMPORTER \
	-DASSIMP_BUILD_NO_RAW_IMPORTER \
	-DASSIMP_BUILD_NO_OFF_IMPORTER \
	-DASSIMP_BUILD_NO_AC_IMPORTER \
	-DASSIMP_BUILD_NO_BVH_IMPORTER \
	-DASSIMP_BUILD_NO_IRRMESH_IMPORTER \
	-DASSIMP_BUILD_NO_IRR_IMPORTER \
	-DASSIMP_BUILD_NO_Q3D_IMPORTER \
	-DASSIMP_BUILD_NO_B3D_IMPORTER \
	-DASSIMP_BUILD_NO_COLLADA_IMPORTER \
	-DASSIMP_BUILD_NO_TERRAGEN_IMPORTER \
	-DASSIMP_BUILD_NO_CSM_IMPORTER \
	-DASSIMP_BUILD_NO_3D_IMPORTER \
	-DASSIMP_BUILD_NO_LWS_IMPORTER \
	-DASSIMP_BUILD_NO_OGRE_IMPORTER \
	-DASSIMP_BUILD_NO_MS3D_IMPORTER \
	-DASSIMP_BUILD_NO_COB_IMPORTER \
	-DASSIMP_BUILD_NO_Q3BSP_IMPORTER \
	-DASSIMP_BUILD_NO_NDO_IMPORTER \
	-DASSIMP_BUILD_NO_IFC_IMPORTER \
	-DASSIMP_BUILD_NO_XGL_IMPORTER \
	-DASSIMP_BUILD_NO_FBX_IMPORTER \
	-DASSIMP_BUILD_NO_C4D_IMPORTER \
	-DASSIMP_BUILD_NO_OPENGEX_IMPORTER \
	-DASSIMP_BUILD_NO_ASSBIN_IMPORTER
#	-DASSIMP_BUILD_NO_BLEND_IMPORTER \
#	-DASSIMP_BUILD_NO_GEO_IMPORTER \
#	-DASSIMP_BUILD_NO_OBJ_IMPORTER \
#
DontBuildImporters := -DASSIMP_BUILD_NO_IFC_IMPORTER -DASSIMP_BUILD_NO_IRRMESH_IMPORTER  -DASSIMP_BUILD_NO_IRR_IMPORTER -DASSIMP_BUILD_NO_C4D_IMPORTER

ASSIMP_FLAGS_3_0 = -DASSIMP_BUILD_DLL_EXPORT -DASSIMP_BUILD_NO_OWN_ZLIB -DASSIMP_BUILD_BOOST_WORKAROUND -Dassimp_EXPORTS -fPIC -fvisibility=hidden -Wall
ASSIMP_FLAGS_3_1 = $(ASSIMP_FLAGS_3_0) # -DASSIMP_BUILD_BLENDER_DEBUG

LOCAL_CFLAGS += $(ASSIMP_FLAGS_3_1) -DASSIMP_BUILD_NO_EXPORT -DOPENDDL_NO_USE_CPP11 $(DontBuildImporters)  # $(DontBuildProcess) 

LOCAL_C_INCLUDES += $(LOCAL_PATH)/include $(LOCAL_PATH)/$(ASSIMP_SRC_DIR)/BoostWorkaround $(LOCAL_PATH)/contrib/openddlparser/include ./ 
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/$(ASSIMP_SRC_DIR)/BoostWorkaround

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := assimp

LOCAL_CFLAGS += -UASSIMP_BUILD_DLL_EXPORT
LOCAL_WHOLE_STATIC_LIBRARIES = assimp_static

LOCAL_LDLIBS := -lz

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/$(ASSIMP_SRC_DIR)/BoostWorkaround
include $(BUILD_SHARED_LIBRARY)