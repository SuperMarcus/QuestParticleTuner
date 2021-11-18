LOCAL_PATH := $(call my-dir)
TARGET_ARCH_ABI := $(APP_ABI)

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Creating prebuilt for dependency: beatsaber-hook
include $(CLEAR_VARS)
LOCAL_MODULE := beatsaber-hook_$(BSHOOK)
LOCAL_EXPORT_C_INCLUDES := extern/beatsaber-hook
LOCAL_SRC_FILES := extern/libbeatsaber-hook_$(BSHOOK).so
LOCAL_CPP_FEATURES += exceptions
include $(PREBUILT_SHARED_LIBRARY)

# Creating prebuilt for dependency: modloader
include $(CLEAR_VARS)
LOCAL_MODULE := modloader
LOCAL_EXPORT_C_INCLUDES := extern/modloader
LOCAL_SRC_FILES := extern/libmodloader.so
LOCAL_CPP_FEATURES += exceptions
include $(PREBUILT_SHARED_LIBRARY)

# Creating prebuilt for dependency: custom-types
include $(CLEAR_VARS)
LOCAL_MODULE := custom-types
LOCAL_EXPORT_C_INCLUDES := extern/custom-types
LOCAL_SRC_FILES := extern/libcustom-types.so
LOCAL_CPP_FEATURES += exceptions
include $(PREBUILT_SHARED_LIBRARY)

# Creating prebuilt for dependency: codegen
include $(CLEAR_VARS)
LOCAL_MODULE := codegen
LOCAL_EXPORT_C_INCLUDES := extern/codegen
LOCAL_SRC_FILES := extern/libcodegen.so
LOCAL_CPP_FEATURES += exceptions
include $(PREBUILT_SHARED_LIBRARY)

# Creating prebuilt for dependency: questui
include $(CLEAR_VARS)
LOCAL_MODULE := questui
LOCAL_EXPORT_C_INCLUDES := extern/questui
LOCAL_SRC_FILES := extern/libquestui.so
LOCAL_CPP_FEATURES += exceptions
include $(PREBUILT_SHARED_LIBRARY)

# Creating main build
include $(CLEAR_VARS)
LOCAL_MODULE := "$(LIBNAME)"
LOCAL_SRC_FILES += $(call rwildcard,src/,*.cpp)
LOCAL_SRC_FILES += $(call rwildcard,extern/beatsaber-hook/src/inline-hook/,*.cpp)
LOCAL_SRC_FILES += $(call rwildcard,extern/beatsaber-hook/src/inline-hook/,*.c)
LOCAL_CFLAGS += -DVERSION='"$(VERSION)"'
LOCAL_CFLAGS += -DID='"$(MODID)"'
LOCAL_CFLAGS +=  -isystem 'extern/libil2cpp/il2cpp/libil2cpp'
LOCAL_CPPFLAGS += -std=c++2a -frtti
LOCAL_CPP_FEATURES += exceptions
LOCAL_LDLIBS += -llog
LOCAL_SHARED_LIBRARIES += beatsaber-hook_$(BSHOOK)
LOCAL_SHARED_LIBRARIES += modloader
LOCAL_SHARED_LIBRARIES += custom-types
LOCAL_SHARED_LIBRARIES += questui
LOCAL_SHARED_LIBRARIES += codegen
LOCAL_C_INCLUDES += ./include ./src ./shared ./extern
LOCAL_C_INCLUDES += ./extern/codegen/shared ./extern/codegen/include
LOCAL_C_INCLUDES += ./extern/beatsaber-hook/shared ./extern/beatsaber-hook/include 
LOCAL_C_INCLUDES += ./extern/modloader/shared ./extern/modloader/include
LOCAL_C_INCLUDES += ./extern/questui/shared ./extern/questui/include
LOCAL_C_INCLUDES += ./extern/custom-types/shared ./extern/custom-types/include
include $(BUILD_SHARED_LIBRARY)
