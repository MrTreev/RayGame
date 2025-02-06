#pragma once

//! @ingroup macros_machine
//! @defgroup macros_machine_os Operating System
//! @{
#if defined(RAYGAME_DOXYGEN_INVOKED)
#    define RAYGAME_OS_ANDROID
#    define RAYGAME_OS_BSD
#    define RAYGAME_OS_HURD
#    define RAYGAME_OS_LINUX
#    define RAYGAME_OS_MAC
#    define RAYGAME_OS_QNX
#    define RAYGAME_OS_TEMPLEOS
#    define RAYGAME_OS_WIN32
#    define RAYGAME_OS_WIN64
#endif
//! @}

#if (__STDC_HOSTED__ == 1)
#    if defined(__ANDROID__)
#        define RAYGAME_OS_ANDROID
#    elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)  \
        || defined(__bsdi__)
#        define RAYGAME_OS_BSD
#    elif defined(__GNU__) || defined(__gnu_hurd__)
#        define RAYGAME_OS_HURD
#        warning "Imagine using hurd, who are you? Richard Stallman?"
#    elif defined(__gnu_linux__) || defined(__linux__)
#        define RAYGAME_OS_LINUX
#    elif defined(macintosh) || defined(Macintosh)                             \
        || (defined(__APPLE__) && defined(__MACH__))
#        define RAYGAME_OS_MAC
#    elif defined(__QNX__) || defined(__QNXNTO__)
#        define RAYGAME_OS_QNX
#        warning "Why? Just why?"
#        warning "What possessed you to try running games on QNX?"
#    elif defined(_WIN64)
#        define RAYGAME_OS_WIN64
#        warning "Imagine using a niche videogame operating system..."
#        warning "Couldn't be me"
#    elif defined(_WIN32)
#        define RAYGAME_OS_WIN32
#        warning "Imagine using a niche videogame operating system..."
#        warning                                                               \
            "Couldn't be me, but at least the 32-bit versions"                 \
            " generally didn't have as much spyware"
#    else
static_assert(false, "Unknown Operating System");
#    endif
#else
static_assert(false, "Cannot run without an OS");
#endif

#if (__STDC_HOSTED__ != 1)
static_assert(false, "Cannot run without an OS");
#elif defined(RAYGAME_OS_ANDROID)
static_assert(false, "Not tested on Android yet");
#elif defined(RAYGAME_OS_BSD)
static_assert(false, "Not tested on BSD yet");
#elif defined(RAYGAME_OS_HURD)
static_assert(false, "Not tested on HURD");
#elif defined(RAYGAME_OS_LINUX)
static_assert(true);
#elif defined(RAYGAME_OS_MAC)
static_assert(false, "Not tested on Apple Macintosh");
#elif defined(RAYGAME_OS_QNX)
static_assert(false, "Not tested on QNX");
#elif defined(RAYGAME_OS_TEMPLEOS)
#elif defined(RAYGAME_OS_WIN32)
static_assert(false, "Not tested on Windows 32-bit yet");
#elif defined(RAYGAME_OS_WIN64)
static_assert(false, "Not tested on Windows 64-bit yet");
#else
static_assert(false, "Unknown Operating System");
#endif
