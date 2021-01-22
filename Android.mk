LOCAL_PATH := $(call my-dir)
TARGET_ARCH_ABI := $(APP_ABI)

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Creating prebuilt for dependency: beatsaber-hook - version: 1.0.9
include $(CLEAR_VARS)
LOCAL_MODULE := beatsaber-hook_1_0_9
LOCAL_EXPORT_C_INCLUDES := extern/beatsaber-hook
LOCAL_SRC_FILES := extern/libbeatsaber-hook_1_0_9.so
LOCAL_CPP_FEATURES += exceptions
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: modloader - version: 1.0.4
include $(CLEAR_VARS)
LOCAL_MODULE := modloader
LOCAL_EXPORT_C_INCLUDES := extern/modloader
LOCAL_SRC_FILES := extern/libmodloader.so
LOCAL_CPP_FEATURES += exceptions
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: custom-types - version: 0.4.2
include $(CLEAR_VARS)
LOCAL_MODULE := custom-types
LOCAL_EXPORT_C_INCLUDES := extern/custom-types
LOCAL_SRC_FILES := extern/libcustom-types.so
LOCAL_CPP_FEATURES += exceptions
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: codegen - version: 0.6.0
include $(CLEAR_VARS)
LOCAL_MODULE := codegen_0_6_0
LOCAL_EXPORT_C_INCLUDES := extern/codegen
LOCAL_SRC_FILES := extern/libcodegen_0_6_0.so
LOCAL_CPP_FEATURES += exceptions
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: questui - version: 0.4.0
include $(CLEAR_VARS)
LOCAL_MODULE := questui
LOCAL_EXPORT_C_INCLUDES := extern/questui
LOCAL_SRC_FILES := extern/libquestui.so
LOCAL_CPP_FEATURES += exceptions
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := particletuner_1_1_0
LOCAL_SRC_FILES += $(call rwildcard,src/,*.cpp)
LOCAL_SRC_FILES += $(call rwildcard,extern/beatsaber-hook/src/inline-hook/,*.cpp)
LOCAL_SRC_FILES += $(call rwildcard,extern/beatsaber-hook/src/inline-hook/,*.c)
LOCAL_SHARED_LIBRARIES += beatsaber-hook_1_0_9
LOCAL_SHARED_LIBRARIES += modloader
LOCAL_SHARED_LIBRARIES += custom-types
LOCAL_SHARED_LIBRARIES += questui
LOCAL_SHARED_LIBRARIES += codegen_0_6_0
LOCAL_LDLIBS += -llog
LOCAL_CFLAGS += -DVERSION='"1.1.0"' -DID='"particletuner"' -isystem 'extern/libil2cpp/il2cpp/libil2cpp'
LOCAL_CPPFLAGS += -std=c++2a -frtti
LOCAL_C_INCLUDES += ./include ./src ./shared ./extern ./extern/beatsaber-hook/shared ./extern/modloader/shared ./extern/questui/shared ./extern/custom-types/shared ./extern/codegen/include
LOCAL_CPP_FEATURES += exceptions
include $(BUILD_SHARED_LIBRARY)
