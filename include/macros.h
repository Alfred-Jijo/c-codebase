#ifndef _CONTEXT_MACROS_H
#define _CONTEXT_MACROS_H

// Platform Detection Macros
#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS 1
    #define PLATFORM_LINUX   0
    #define PLATFORM_MACOS   0
    #define PLATFORM_NAME "Windows"

    // Windows-specific headers
    #include <windows.h>

#elif defined(__linux__)
    #define PLATFORM_WINDOWS 0
    #define PLATFORM_LINUX   1
    #define PLATFORM_MACOS   0
    #define PLATFORM_NAME "Linux"

    // Linux-specific headers
    #include <unistd.h>
    #include <sys/syscall.h>

#elif defined(__APPLE__) && defined(__MACH__)
    #define PLATFORM_WINDOWS 0
    #define PLATFORM_LINUX   0
    #define PLATFORM_MACOS   1
    #define PLATFORM_NAME "macOS"

    // macOS-specific headers
    #include <TargetConditionals.h>
    #include <unistd.h>

#else
    #error "Unsupported platform"
#endif

// Architecture Detection Macros
#if defined(__x86_64__) || defined(_M_X64)
    #define ARCH_64_BIT 1
    #define ARCH_32_BIT 0
    #define ARCH_NAME "x86_64"
#elif defined(__i386__) || defined(_M_IX86)
    #define ARCH_64_BIT 0
    #define ARCH_32_BIT 1
    #define ARCH_NAME "x86"
#elif defined(__arm64__) || defined(__aarch64__)
    #define ARCH_64_BIT 1
    #define ARCH_32_BIT 0
    #define ARCH_NAME "ARM64"
#elif defined(__arm__) || defined(_M_ARM)
    #define ARCH_64_BIT 0
    #define ARCH_32_BIT 1
    #define ARCH_NAME "ARM32"
#else
    #error "Unsupported architecture"
#endif

// Compiler Detection Macros
#if defined(_MSC_VER)
    #define COMPILER_MSVC 1
    #define COMPILER_GCC  0
    #define COMPILER_CLANG 0
    #define COMPILER_NAME "MSVC"
#elif defined(__GNUC__)
    #define COMPILER_MSVC 0
    #define COMPILER_GCC  1
    #define COMPILER_CLANG 0
    #define COMPILER_NAME "GCC"
#elif defined(__clang__)
    #define COMPILER_MSVC 0
    #define COMPILER_GCC  0
    #define COMPILER_CLANG 1
    #define COMPILER_NAME "Clang"
#else
    #error "Unsupported compiler"
#endif

// Platform-Specific Macro for Dynamic Library Loading
#if PLATFORM_WINDOWS
    #define LOAD_LIBRARY(lib) LoadLibraryA(lib)
    #define GET_PROC_ADDRESS(handle, func) GetProcAddress(handle, func)
    #define CLOSE_LIBRARY(handle) FreeLibrary(handle)
#else
    #define LOAD_LIBRARY(lib) dlopen(lib, RTLD_LAZY)
    #define GET_PROC_ADDRESS(handle, func) dlsym(handle, func)
    #define CLOSE_LIBRARY(handle) dlclose(handle)
#endif

// Inline and Export Macros for Consistent Cross-Platform Usage
#ifdef _MSC_VER
    #define INLINE __inline
    #define EXPORT __declspec(dllexport)
#else
    #define INLINE inline
    #define EXPORT __attribute__((visibility("default")))
#endif

#endif // _CONTEXT_MACROS_H