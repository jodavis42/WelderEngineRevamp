///////////////////////////////////////////////////////////////////////////////
///
/// \file Platform.hpp
/// 
/// Authors: Trevor Sundberg
/// Copyright 2014, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

//-----------------------------------------------------------------------------Platform
// Detect 32 or 64 bit
// If this is a windows platform...
#if defined(_WIN32) || defined(_WIN64)
  #if defined(_WIN64) || defined(_M_X64) || defined(_M_IA64)
    #define PLATFORM_64 1
    #define PLATFORM_BITS "64"
  #else
    #define PLATFORM_32 1
    #define PLATFORM_BITS "32"
  #endif
#else
  // If this is a gcc or clang platforms...
  #if defined(__x86_64__) || defined(__ppc64__)
    #define PLATFORM_64 1
    #define PLATFORM_BITS "64"
  #else
    #define PLATFORM_32 1
    #define PLATFORM_BITS "32"
  #endif
#endif

// Detect the Windows platform
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
  #define PLATFORM_WINDOWS 1
  #define PLATFORM_HARDWARE 1
  #define PLATFORM_NAME "Win"
// Detect all Apple platforms
#elif defined(__APPLE__)
  // This header Contains defines that tell us the current platform
  #include <TargetConditionals.h>
  #if TARGET_IPHONE_SIMULATOR
    #define PLATFORM_IPHONE 1
    #define PLATFORM_VIRTUAL 1
    #define PLATFORM_NAME "iPhoneSimulator"
  #elif TARGET_OS_IPHONE
    #define PLATFORM_IPHONE 1
#define PLATFORM_HARDWARE 1
#define PLATFORM_NAME "iPhone"
  #elif TARGET_OS_MAC
    #define PLATFORM_MAC 1
    #define PLATFORM_POSIX 1
    #define PLATFORM_HARDWARE 1
    #define PLATFORM_NAME "MacOs"
  #else
    #error "Unsupported platform"
  #endif

#elif defined(EMSCRIPTEN)
  #define PLATFORM_EMSCRIPTEN 1
  #define PLATFORM_HARDWARE 1
  #define PLATFORM_NAME "Emscripten"

// Linux, which is a POSIX platform
#elif defined(__linux) || defined(__linux__)
  #define PLATFORM_LINUX 1
  #define PLATFORM_POSIX 1
  #define PLATFORM_HARDWARE 1
  #define PLATFORM_NAME "Linux"

// Unix, which is a POSIX platform
#elif defined(__unix) || defined(__unix__)
  #define PLATFORM_UNIX 1
  #define PLATFORM_POSIX 1
  #define PLATFORM_HARDWARE 1
  #define PLATFORM_NAME "Unix"

// Catch all for other POSIX compatible platforms
#elif defined(__posix)
  #define PLATFORM_POSIX 1
  #define PLATFORM_HARDWARE 1
  #define PLATFORM_NAME "Posix"
#endif

// Detect compilers
#if defined(_MSC_VER)
  #define COMPILER_MICROSOFT 1
#elif defined(__clang__)
  #define COMPILER_CLANG 1
#elif defined(__GNUC__)
  #define COMPILER_GCC 1
#elif defined(__llvm__)
  #define COMPILER_LLVM 1
#endif


//-----------------------------------------------------------------------------Debug
// Detect debug or release settings.
#ifdef NDEBUG
#define ZeroRelease 1
#else
#define ZeroDebug 1
#endif


//-----------------------------------------------------------------------------Main
// Main is different depending on the OS
#ifdef COMPILER_MICROSOFT
#define ZeroConsoleMain(argc, argv)       int main(int argc, char** argv)
#define ZeroGuiMain()                     int __stdcall WinMain(void*, void*, char*, int)
#define ZeroSharedLibraryMain()           int __stdcall DllMain(void*, unsigned long, void*)
#else
#define ZeroConsoleMain(argc, argv)       int main(int argc, char** argv)
#define ZeroGuiMain()                     int main(int, char**)
#define ZeroSharedLibraryMain(argc, argv) int main(int, char**)
#endif

//-----------------------------------------------------------------------------Warnings
#ifdef COMPILER_MICROSOFT

#ifndef ZeroDebug
#define _SECURE_SCL 0
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#define _NO_CVCONST_H

// Enable these warnings by setting them to level 3
// Enable warning function does not override any base class virtual member function
// this is useful to catch renaming virtual functions
#pragma warning(3: 4263)

// Enable warning level 3 Conversion of an Enum to a integral type
#pragma warning(3: 4239)

// Dbghelp has warnings in VS2015 (unnamed typedef)
#pragma warning(disable : 4091)

// Ignore the warning about unusual use of type bool
#pragma warning(disable: 4804)

// Ignore the warning about forcing value to bool
#pragma warning(disable: 4800)

// We don't care about 'behavior change - pod constructors'
#pragma warning(disable: 4345)

// Ignore the warning about placement-new for POD data
#pragma warning(disable: 4345)

// Constants in 'if' and 'while' are used for debug macros
#pragma warning(disable: 4127)

// Disable the warning 'this' in base initializer
#pragma warning(disable: 4355)

// We use the nameless struct/union extension and it is legal
// on other compilers
#pragma warning(disable: 4201)

// Disable deprecation warnings
#pragma warning(disable: 4996)

// Disable ZeroShared warnings
#pragma warning(disable: 4251)

// Disable a warning for noexcept when exception handling is off
#pragma warning(disable: 4577)

// We don't consider unreferenced parameters to be an error
#pragma warning(disable : 4100)

// Unfortunately, local variable initialized but not referenced is actually a very
// useful warning, however there are cases where we only initialize variables to be
// used in debug checks, which this will complain / error in release
// There are also other cases where we explicitly invoke destructors for class binding
// and if the destructor is trivial, it complains that the self parameter is not used
#pragma warning(disable : 4189)

// We get a warning about an outer structure being padded due to inner members having alignment specifications
// An example of this is using jmp_buf anywhere (such as in PerFrameData) especially with 64-bit computability warnings
#pragma warning(disable : 4324)

// We really don't care about C++ initializing POD types to zero
#pragma warning(disable : 4345)

// Disable the 'this' in base initializer, since we use it to track owners
#pragma warning(disable : 4355)

// Ignore the warning about a non-standard extension for 'override'
// It really is way too useful (both for documentation and error checking)
#pragma warning(disable : 4481)

// This is a warning about unused functions being removed, but there is a serious issue with VS2010
// where it can end up removing a virtual [thunk] function and then it warns you about it
// (seems to be when combined with SFINAE testing for the virtual member)
#pragma warning(disable : 4505)

// Disable the exception handling warning. We don't use exceptions in Zilch
// because many console and embedded systems do not support them)
#pragma warning(disable : 4530)

// For virtual function binding we need to ignore warnings about no constructors
// being generated, as well as warnings about a class not being able to be instantiated
#pragma warning(disable : 4510)
#pragma warning(disable : 4610)

// Disable "Interaction between '_setjmp' and C++ object destruction is non-portable"
// We use setjmp / longjmp for exception handling, and we make sure to properly handle
// destruction of objects
#pragma warning(disable : 4611)

// Disable warnings about deprecated function calls
// It's nice to know these are deprecated, but we'll deal with them when they become actual errors
#pragma warning(disable : 4996)

// Static analysis complains about passing a 'char' into isspace and similar functions
// For some weird reason it requires casting the char to an 'unsigned char', even though isspace is defined to take an int
// This is well formed C and C++ code, static analysis is complaining about it
#pragma warning(disable : 6330)

// Static analysis also complains about the use of alloca, which has a well defined meaning
// It recommends the usage of _malloca, a completely non-standard MSVC only function which functions EXACTLY the same in Release mode
#pragma warning(disable : 6255)

// Disabling the local declaration hiding, for now (this one is the most valid, but we have valid cases for it)
#pragma warning(disable : 6246)

// Static analysis also complains about 'Dereferencing NULL pointer' for every single instance we use in-place new, which is simply not correct
#pragma warning(disable : 6011)

// Comparing a constant to another constant (not caught by the W4 via templates) is considered bad by static analysis, even though
// it completely makes sense and will be optimized out if it is in fact a constant
#pragma warning(disable : 6326)

// This particular warning complains about the dereferencing a null pointer because it implied
// that a variable could be null (assigned to another variable, check that variable)
// The entire warning is fundamentally flawed:
//  Player* foundPlayer = nullptr;
//  if (SomeCondition)
//  {
//    Player* globalPlayer = GrabGlobalPlayer();
//    if (globalPlayer->IsAlive()) <--- Here it complains that 'globalPlayer' could be null, simply because of the below line
//      foundPlayer = globalPlayer;
//  }
//  if (foundPlayer != nullptr) <--- It sees that 'foundPlayer' is being checked for null, and because foundPlayer
//    ...                            is assigned from nearestPlayer, then it thinks 'globalPlayer' could be null
#pragma warning(disable : 28182)

// Standard examples (such as setting thread name) from Microsoft's own documentation cause the static analysis to complain
// about __try and __catch (about continuing from the exception possibly causing an infinite loop, which it does not)
#pragma warning(disable : 6312)
#pragma warning(disable : 6322)

// Disable a warning about doing well defined operations on bools
#pragma warning(disable : 6323)

// We should probably examine again if these are needed.
#pragma warning(disable : 6201)
#pragma warning(disable : 6031)

// These static analysis warnings are literally happening inside Microsoft's own 'wspiapi.h'
#pragma warning(disable : 6101)
#pragma warning(disable : 6102)
#pragma warning(disable : 6387)
#pragma warning(disable : 6386)
#pragma warning(disable : 28196)

// We don't care about using deprecated Windows code, we'll change it later if we care
#pragma warning(disable : 28159)

#ifdef PLATFORM_64
// Temporary 64-bit support (ignore size_t conversion warnings)
#pragma warning(disable: 4244)
#pragma warning(disable: 4267)
#pragma warning(disable: 4309)
#endif

#endif

#if defined(COMPILER_CLANG) || defined(COMPILER_GCC)

#if defined(COMPILER_CLANG)
// Ignore unknown pragma warnings...
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#else
// Ignore unknown pragma warnings...
#pragma GCC diagnostic ignored "-Wpragmas"
#endif

// We have many valid switch statements that don't handle all values
#pragma GCC diagnostic ignored "-Wswitch"

// We use offsetof, which is technically compiler specific and undefined, but works on all supported platforms
#pragma GCC diagnostic ignored "-Winvalid-offsetof"

// This should be investigated for a better method (generally it's for shoving values into void* user data)
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"

// When we force inline some functions, gcc has a very complicated way of determining if a function can be inlined or not
// If it decides the function does not get inlined, and the function was actually implemented in the cpp (not the header, link time code-gen)
// then it complains about the function being unused (which it's absolutely not, seems like a gcc bug)
#pragma GCC diagnostic ignored "-Wunused-function"

// We declare typedefs that may be useful for people using Zilch, but we don't use them ourselves
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#endif

//-----------------------------------------------------------------------------Built-Ins

// ZeroForceInline forces a function to be inlined for optimization purposes
// ZeroNoInline forces a function to not be inlined (only used to debug, and unfortunately to fix true linker bugs)

// Helper macros
#define ZeroStringDeref(text) #text
#define ZeroStringize(text) ZeroStringDeref(text)

#ifdef COMPILER_MICROSOFT
#define ZeroThreadLocal __declspec(thread)
#define ZeroImport __declspec(dllimport)
#define ZeroExport __declspec(dllexport)
#define ZeroExportC extern "C" __declspec(dllexport)
#define ZERO_DEBUG_BREAK __debugbreak()
//#define ZeroTodo(text) __pragma(message(__FILE__ "(" ZeroStringize(__LINE__) ") : Todo: " text))
#define ZeroTodo(text)
#define ZeroForceInline inline __forceinline
#define ZeroNoInline __declspec(noinline)
#endif

#ifndef COMPILER_MICROSOFT
#define ZeroThreadLocal __thread
#define ZeroImport
#define ZeroExport
#define ZeroExportC extern "C" __attribute__((visibility("default")))
#define ZeroShared __attribute__((visibility("default")))
#define ZERO_DEBUG_BREAK
#define ZeroTodo(text)
// There seems to be issues with __attribute__((always_inline)) wit GCC linking
#define ZeroForceInline inline
#define ZeroNoInline
#endif

#define ZeroNoImportExport

#if defined(ZeroImportDll)
#define ZeroShared ZeroImport
#define ZeroSharedTemplate
#elif defined(ZeroExportDll)
#define ZeroShared ZeroExport
#define ZeroSharedTemplate
#else
#define ZeroShared
#define ZeroSharedTemplate
#endif

//-----------------------------------------------------------------------------Includes
#ifndef PLATFORM_WINDOWS
#include <alloca.h>
#endif