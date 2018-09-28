#ifndef __NIEEL_OS_HPP__
#define __NIEEL_OS_HPP__

#include "nieel/util/hash.hpp"

namespace nieel::os
{
    #if   defined(_WIN32)
        #define PLATFORM_NAME "windows" // Windows
    #elif defined(_WIN64)
        #define PLATFORM_NAME "windows" // Windows
    #elif defined(__CYGWIN__) && !defined(_WIN32)
        #define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
    #elif defined(__ANDROID__)
        #define PLATFORM_NAME "android" // Android (implies Linux, so it must come first)
    #elif defined(__linux__)
        #define PLATFORM_NAME "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
    #elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
        #include <sys/param.h>
        #if defined(BSD)
            #define PLATFORM_NAME "bsd" // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
        #endif
    #elif defined(__hpux)
        #define PLATFORM_NAME "hp-ux" // HP-UX
    #elif defined(_AIX)
        #define PLATFORM_NAME "aix" // IBM AIX
    #elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
        #include <TargetConditionals.h>
        #if TARGET_IPHONE_SIMULATOR == 1
            #define PLATFORM_NAME "ios" // Apple iOS
        #elif TARGET_OS_IPHONE == 1
            #define PLATFORM_NAME "ios" // Apple iOS
        #elif TARGET_OS_MAC == 1
            #define PLATFORM_NAME "osx" // Apple OSX
        #endif
    #elif defined(__sun) && defined(__SVR4)
        #define PLATFORM_NAME "solaris" // Oracle Solaris, Open Indiana
    #else
        #define PLATFORM_NAME NULL
    #endif
        
    constexpr const char* what() { return (PLATFORM_NAME == NULL) ? "" : PLATFORM_NAME; }
    
    constexpr const char* prefix() {
        switch(hash(what()))
        {
        case "linux"_h:
        case "osx"_h:
            return "/usr/local/";
        case "windows"_h:
            return "C:/users/";
        }
    }
    
}

namespace nieel::compiler
{
    #if   defined(_MSC_VER)
         #define COMPILER_NAME "msvc"  // visual studio  
    #elif defined(__GNUC__)
	 #define COMPILER_NAME "gcc"   // gcc
    #elif defined(__clang__)
	 #define COMPILER_NAME "clang" // clang
    #elif defined(__EMSCRIPTEN__)
	 #define COMPILER_NAME "wsm"   // web assembly
    #elif defined(__MINGW32__) "mingw"  
	 #define COMPILER_NAME "mingw" // mingw 32bit mingw-w64 32bit
    #elif defined(__MINGW64__) "mingw" 
	 #define COMPILER_NAME "mingw" // mingw-w64 64bit
    #else
	 #define COMPILER_NAME NULL    // can't find 
    #endif

    constexpr const char* what() { return (COMPILER_NAME == NULL) ? "" : COMPILER_NAME; }
}

#endif __NIEEL_OS_HPP__
