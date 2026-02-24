/*
 * compiler_pragma.h
 *
 *  Created on: Oct 28, 2025
 *      Author: aurelienp
 *
 *  \brief  Cross-compiler abstraction layer for section placement,
 *          alignment and inlining.
 *
 *  Compatible with:
 *          - ARM GCC / STM32CubeIDE
 *          - IAR / Keil
 *          - PC builds (MSVC, MinGW, clang)
 */

#ifndef ATRALTECH_TOOLS_COMPILER_PRAGMA_H_
#define ATRALTECH_TOOLS_COMPILER_PRAGMA_H_

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Platform / compiler detection
//------------------------------------------------------------------------------
#if defined(__GNUC__) || defined(__clang__)
    #define COMPILER_GCC   1
#elif defined(__ICCARM__)
    #define COMPILER_IAR   1
#elif defined(__ARMCC_VERSION)
    #define COMPILER_KEIL  1
#elif defined(_MSC_VER)
    #define COMPILER_MSVC  1
#else
    #define COMPILER_UNKNOWN 1
#endif

//------------------------------------------------------------------------------
// Alignment helpers
//------------------------------------------------------------------------------
#if defined(COMPILER_MSVC)
    #define ALIGN(n)           __declspec(align(n))
#else
    #define ALIGN(n)           __attribute__((aligned(n)))
#endif

//------------------------------------------------------------------------------
// Section helpers (no-op on PC builds)
//------------------------------------------------------------------------------
#if defined(COMPILER_GCC) || defined(COMPILER_KEIL)
    #define SECTION(name)      __attribute__((section(name)))
#elif defined(COMPILER_IAR)
    #define SECTION(name)      _Pragma(#name)
#else
    #define SECTION(name)
#endif

//------------------------------------------------------------------------------
// Inline helpers
//------------------------------------------------------------------------------
#if defined(COMPILER_GCC) || defined(COMPILER_CLANG)
    #define FORCE_INLINE       __attribute__((always_inline)) inline
#elif defined(COMPILER_MSVC)
    #define FORCE_INLINE       __forceinline
#else
    #define FORCE_INLINE       inline
#endif

//------------------------------------------------------------------------------
// Common memory placement macros
//------------------------------------------------------------------------------
#define DTCMRAM        SECTION(".DTCMRAM")
#define ITCMRAM        SECTION(".ITCMRAM")
#define RAM_D1         SECTION(".RAM_D1")
#define RAM_D2         SECTION(".RAM_D2")
#define NOINIT         SECTION(".noinit")

//------------------------------------------------------------------------------
// Project-specific sections
//------------------------------------------------------------------------------
#define EXTFLASH_SECTION      SECTION("ExtFlashVideoSection")
#define EXTFLASH_SECTION_32   SECTION("ExtFlashVideoSection") ALIGN(32)
#define EXTFLASH_SECTION_256  SECTION("ExtFlashVideoSection") ALIGN(256)  /* <-- new macro */

//------------------------------------------------------------------------------
// Deprecated / diagnostic helpers
//------------------------------------------------------------------------------
#if defined(COMPILER_GCC)
    #define DEPRECATED(msg)    __attribute__((deprecated(msg)))
#elif defined(COMPILER_MSVC)
    #define DEPRECATED(msg)    __declspec(deprecated(msg))
#else
    #define DEPRECATED(msg)
#endif

#ifdef __cplusplus
}
#endif


#endif /* ATRALTECH_TOOLS_COMPILER_PRAGMA_H_ */
