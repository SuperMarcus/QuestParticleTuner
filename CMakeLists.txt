cmake_minimum_required(VERSION 3.6.0)

set(ANDROID_ABI arm64-v8a)
set(ANDROID_NATIVE_API_LEVEL 24)
set(CMAKE_TOOLCHAIN_FILE $ENV{ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake)
#set(CMAKE_TOOLCHAIN_FILE "")

set(CMAKE_C_COMPILER_TARGET aarch64-none-linux-android24)
set(CMAKE_C_COMPILER $ENV{ANDROID_NDK_HOME}/toolchains/llvm/prebuilt/darwin-x86_64/bin/clang)
set(CMAKE_CXX_COMPILER_TARGET aarch64-none-linux-android24)
set(CMAKE_CXX_COMPILER $ENV{ANDROID_NDK_HOME}/toolchains/llvm/prebuilt/darwin-x86_64/bin/clang++)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_OSX_SYSROOT $ENV{ANDROID_NDK_HOME}/toolchains/llvm/prebuilt/darwin-x86_64/sysroot)
set(CMAKE_OSX_DEPLOYMENT_TARGET "")

project(particletuner)

add_compile_definitions(VERSION='"dummy_version"' ID='"particletuner"')

include_directories(include)
include_directories(extern)
include_directories(shared)
include_directories(extern/libil2cpp/il2cpp/libil2cpp)
include_directories(extern/codegen/include)
include_directories(extern/beatsaber-hook/shared)
include_directories(extern/questui/shared)
include_directories(extern/modloader/shared)
include_directories(.)
#include_directories($ENV{ANDROID_NDK_HOME}/sources/cxx-stl/llvm-libc++/include)
#include_directories($ENV{ANDROID_NDK_HOME}/sysroot/usr/include)
#include_directories($ENV{ANDROID_NDK_HOME}/sources/cxx-stl/llvm-libc++abi/include)
#include_directories($ENV{ANDROID_NDK_HOME}/sysroot/usr/include/arm-linux-androideabi)

file(GLOB SRC src/*.cpp)
add_library(particletuner SHARED ${SRC})
