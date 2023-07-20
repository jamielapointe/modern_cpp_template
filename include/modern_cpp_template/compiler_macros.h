///\file compiler_macros.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief Set a bunch of macros based on compiler in use
///\version 0.1
///\date 2023-07-05
/// This is heavily "borrowed" from Eigen:
/// https://eigen.tuxfamily.org/index.php?title=Main_Page
///\copyright Copyright (c) 2023
///

#pragma once

//------------------------------------------------------------------------------------------
// Compiler identification, modern_cpp_template_COMP_*
//------------------------------------------------------------------------------------------

/// \internal modern_cpp_template_COMP_GNUC set to version (e.g., 951 for
/// GCC 9.5.1) for all compilers compatible with GCC
#ifdef __GNUC__
#  define modern_cpp_template_COMP_GNUC \
    (__GNUC__ * 100 + __GNUC_MINOR__ * 10 + __GNUC_PATCHLEVEL__)
#else
#  define modern_cpp_template_COMP_GNUC 0
#endif

/// \internal modern_cpp_template_COMP_CLANG set to version (e.g., 372 for
/// clang 3.7.2) if the compiler is clang
#if defined(__clang__)
#  define modern_cpp_template_COMP_CLANG \
    (__clang_major__ * 100 + __clang_minor__ * 10 + __clang_patchlevel__)
#else
#  define modern_cpp_template_COMP_CLANG 0
#endif

/// \internal modern_cpp_template_COMP_CLANGAPPLE set to the version number
/// (e.g. 9000000 for AppleClang 9.0) if the compiler is AppleClang
#if defined(__clang__) && defined(__apple_build_version__)
#  define modern_cpp_template_COMP_CLANGAPPLE __apple_build_version__
#else
#  define modern_cpp_template_COMP_CLANGAPPLE 0
#endif

/// \internal modern_cpp_template_COMP_CASTXML set to 1 if being preprocessed by
/// CastXML
#if defined(__castxml__)
#  define modern_cpp_template_COMP_CASTXML 1
#else
#  define modern_cpp_template_COMP_CASTXML 0
#endif

/// \internal modern_cpp_template_COMP_LLVM set to 1 if the compiler backend is
/// llvm
#if defined(__llvm__)
#  define modern_cpp_template_COMP_LLVM 1
#else
#  define modern_cpp_template_COMP_LLVM 0
#endif

/// \internal modern_cpp_template_COMP_ICC set to __INTEL_COMPILER if the
/// compiler is Intel icc compiler, 0 otherwise
#if defined(__INTEL_COMPILER)
#  define modern_cpp_template_COMP_ICC __INTEL_COMPILER
#else
#  define modern_cpp_template_COMP_ICC 0
#endif

/// \internal modern_cpp_template_COMP_CLANGICC set to __INTEL_CLANG_COMPILER if
/// the compiler is Intel icx compiler, 0 otherwise
#if defined(__INTEL_CLANG_COMPILER)
#  define modern_cpp_template_COMP_CLANGICC __INTEL_CLANG_COMPILER
#else
#  define modern_cpp_template_COMP_CLANGICC 0
#endif

/// \internal modern_cpp_template_COMP_MINGW set to 1 if the compiler is mingw
#if defined(__MINGW32__)
#  define modern_cpp_template_COMP_MINGW 1
#else
#  define modern_cpp_template_COMP_MINGW 0
#endif

/// \internal modern_cpp_template_COMP_SUNCC set to 1 if the compiler is Solaris
/// Studio
#if defined(__SUNPRO_CC)
#  define modern_cpp_template_COMP_SUNCC 1
#else
#  define modern_cpp_template_COMP_SUNCC 0
#endif

/// \internal modern_cpp_template_COMP_MSVC set to _MSC_VER if the compiler is
/// Microsoft Visual C++, 0 otherwise.
#if defined(_MSC_VER)
#  define modern_cpp_template_COMP_MSVC _MSC_VER
#else
#  define modern_cpp_template_COMP_MSVC 0
#endif

#if defined(__NVCC__)
#  if defined(__CUDACC_VER_MAJOR__) && (__CUDACC_VER_MAJOR__ >= 9)
#    define modern_cpp_template_COMP_NVCC \
      ((__CUDACC_VER_MAJOR__ * 10000) + (__CUDACC_VER_MINOR__ * 100))
#  elif defined(__CUDACC_VER__)
#    define modern_cpp_template_COMP_NVCC __CUDACC_VER__
#  else
#    error "NVCC did not define compiler version."
#  endif
#else
#  define modern_cpp_template_COMP_NVCC 0
#endif

// For the record, here is a table summarizing the possible values for
// modern_cpp_template_COMP_MSVC:
//  name        ver   MSC_VER
//  2015        14      1900
//  "15"        15      1900
//  2017-14.1   15.0    1910
//  2017-14.11  15.3    1911
//  2017-14.12  15.5    1912
//  2017-14.13  15.6    1913
//  2017-14.14  15.7    1914
//  2017        15.8    1915
//  2017        15.9    1916
//  2019 RTW    16.0    1920

/// \internal modern_cpp_template_COMP_MSVC_LANG set to _MSVC_LANG if the
/// compiler is Microsoft Visual C++, 0 otherwise.
#if defined(_MSVC_LANG)
#  define modern_cpp_template_COMP_MSVC_LANG _MSVC_LANG
#else
#  define modern_cpp_template_COMP_MSVC_LANG 0
#endif

// For the record, here is a table summarizing the possible values for
// modern_cpp_template_COMP_MSVC_LANG: MSVC option Standard MSVC_LANG /std:c++14
// (default as of VS 2019)   C++14     201402L /std:c++17 C++17     201703L
// /std:c++latest                       >C++17    >201703L

/// \internal modern_cpp_template_COMP_MSVC_STRICT set to 1 if the compiler is
/// really Microsoft Visual C++ and not ,e.g., ICC or clang-cl
#if modern_cpp_template_COMP_MSVC &&                                   \
    !(modern_cpp_template_COMP_ICC || modern_cpp_template_COMP_LLVM || \
      modern_cpp_template_COMP_CLANG)
#  define modern_cpp_template_COMP_MSVC_STRICT _MSC_VER
#else
#  define modern_cpp_template_COMP_MSVC_STRICT 0
#endif

/// \internal modern_cpp_template_COMP_IBM set to xlc version if the compiler is
/// IBM XL C++
// XLC   version
// 3.1   0x0301
// 4.5   0x0405
// 5.0   0x0500
// 12.1  0x0C01
#if defined(__IBMCPP__) || defined(__xlc__) || defined(__ibmxl__)
#  define modern_cpp_template_COMP_IBM __xlC__
#else
#  define modern_cpp_template_COMP_IBM 0
#endif

/// \internal modern_cpp_template_COMP_PGI set to PGI version if the compiler is
/// Portland Group Compiler
#if defined(__PGI)
#  define modern_cpp_template_COMP_PGI (__PGIC__ * 100 + __PGIC_MINOR__)
#else
#  define modern_cpp_template_COMP_PGI 0
#endif

/// \internal modern_cpp_template_COMP_ARM set to 1 if the compiler is ARM
/// Compiler
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#  define modern_cpp_template_COMP_ARM 1
#else
#  define modern_cpp_template_COMP_ARM 0
#endif

/// \internal modern_cpp_template_COMP_EMSCRIPTEN set to 1 if the compiler is
/// Emscripten Compiler
#if defined(__EMSCRIPTEN__)
#  define modern_cpp_template_COMP_EMSCRIPTEN 1
#else
#  define modern_cpp_template_COMP_EMSCRIPTEN 0
#endif

/// \internal modern_cpp_template_COMP_FCC set to FCC version if the compiler is
/// Fujitsu Compiler (traditional mode) \note The Fujitsu C/C++ compiler uses
/// the traditional mode based on EDG g++ 6.1 by default or if invoked with the
/// -Nnoclang flag
#if defined(__FUJITSU)
#  define modern_cpp_template_COMP_FCC \
    (__FCC_major__ * 100 + __FCC_minor__ * 10 + __FCC_patchlevel__)
#else
#  define modern_cpp_template_COMP_FCC 0
#endif

/// \internal modern_cpp_template_COMP_CLANGFCC set to FCC version if the
/// compiler is Fujitsu Compiler (Clang mode) \note The Fujitsu C/C++ compiler
/// uses the non-traditional mode based on Clang 7.1.0 if invoked with the
/// -Nclang flag
#if defined(__CLANG_FUJITSU)
#  define modern_cpp_template_COMP_CLANGFCC \
    (__FCC_major__ * 100 + __FCC_minor__ * 10 + __FCC_patchlevel__)
#else
#  define modern_cpp_template_COMP_CLANGFCC 0
#endif

/// \internal modern_cpp_template_COMP_CPE set to CPE version if the compiler is
/// HPE Cray Compiler (GCC based) \note This is the SVE-enabled C/C++ compiler
/// from the HPE Cray Programming Environment (CPE) based on Cray GCC 8.1
#if defined(_CRAYC) && !defined(__clang__)
#  define modern_cpp_template_COMP_CPE \
    (_RELEASE_MAJOR * 100 + _RELEASE_MINOR * 10 + _RELEASE_PATCHLEVEL)
#else
#  define modern_cpp_template_COMP_CPE 0
#endif

/// \internal modern_cpp_template_COMP_CLANGCPE set to CPE version if the
/// compiler is HPE Cray Compiler (Clang based) \note This is the C/C++ compiler
/// from the HPE Cray Programming Environment (CPE) based on Cray Clang 11.0
/// without SVE-support
#if defined(_CRAYC) && defined(__clang__)
#  define modern_cpp_template_COMP_CLANGCPE \
    (_RELEASE_MAJOR * 100 + _RELEASE_MINOR * 10 + _RELEASE_PATCHLEVEL)
#else
#  define modern_cpp_template_COMP_CLANGCPE 0
#endif

/// \internal modern_cpp_template_COMP_LCC set to 1 if the compiler is MCST-LCC
/// (MCST eLbrus Compiler Collection)
#if defined(__LCC__) && defined(__MCST__)
#  define modern_cpp_template_COMP_LCC (__LCC__ * 100 + __LCC_MINOR__)
#else
#  define modern_cpp_template_COMP_LCC 0
#endif

/// \internal modern_cpp_template_COMP_GNUC_STRICT set to 1 if the compiler is
/// really GCC and not a compatible compiler (e.g., ICC, clang, mingw, etc.)
#if modern_cpp_template_COMP_GNUC &&                                         \
    !(modern_cpp_template_COMP_CLANG || modern_cpp_template_COMP_ICC ||      \
      modern_cpp_template_COMP_CLANGICC || modern_cpp_template_COMP_MINGW || \
      modern_cpp_template_COMP_PGI || modern_cpp_template_COMP_IBM ||        \
      modern_cpp_template_COMP_ARM || modern_cpp_template_COMP_EMSCRIPTEN || \
      modern_cpp_template_COMP_FCC || modern_cpp_template_COMP_CLANGFCC ||   \
      modern_cpp_template_COMP_CPE || modern_cpp_template_COMP_CLANGCPE ||   \
      modern_cpp_template_COMP_LCC)
#  define modern_cpp_template_COMP_GNUC_STRICT 1
#else
#  define modern_cpp_template_COMP_GNUC_STRICT 0
#endif

// GCC, and compilers that pretend to be it, have different version schemes, so
// this only makes sense to use with the real GCC.
#if modern_cpp_template_COMP_GNUC_STRICT
#  define modern_cpp_template_GNUC_STRICT_AT_LEAST(x, y, z)     \
    ((__GNUC__ > x) || (__GNUC__ == x && __GNUC_MINOR__ > y) || \
     (__GNUC__ == x && __GNUC_MINOR__ == y && __GNUC_PATCHLEVEL__ >= z))
#  define modern_cpp_template_GNUC_STRICT_LESS_THAN(x, y, z)    \
    ((__GNUC__ < x) || (__GNUC__ == x && __GNUC_MINOR__ < y) || \
     (__GNUC__ == x && __GNUC_MINOR__ == y && __GNUC_PATCHLEVEL__ < z))
#else
#  define modern_cpp_template_GNUC_STRICT_AT_LEAST(x, y, z) 0
#  define modern_cpp_template_GNUC_STRICT_LESS_THAN(x, y, z) 0
#endif

/// \internal modern_cpp_template_COMP_CLANG_STRICT set to 1 if the compiler is
/// really Clang and not a compatible compiler (e.g., AppleClang, etc.)
#if modern_cpp_template_COMP_CLANG &&        \
    !(modern_cpp_template_COMP_CLANGAPPLE || \
      modern_cpp_template_COMP_CLANGICC ||   \
      modern_cpp_template_COMP_CLANGFCC || modern_cpp_template_COMP_CLANGCPE)
#  define modern_cpp_template_COMP_CLANG_STRICT 1
#else
#  define modern_cpp_template_COMP_CLANG_STRICT 0
#endif

// Clang, and compilers forked from it, have different version schemes, so this
// only makes sense to use with the real Clang.
#if modern_cpp_template_COMP_CLANG_STRICT
#  define modern_cpp_template_CLANG_STRICT_AT_LEAST(x, y, z)                   \
    ((__clang_major__ > x) || (__clang_major__ == x && __clang_minor__ > y) || \
     (__clang_major__ == x && __clang_minor__ == y &&                          \
      __clang_patchlevel__ >= z))
#  define modern_cpp_template_CLANG_STRICT_LESS_THAN(x, y, z)                  \
    ((__clang_major__ < x) || (__clang_major__ == x && __clang_minor__ < y) || \
     (__clang_major__ == x && __clang_minor__ == y &&                          \
      __clang_patchlevel__ < z))
#else
#  define modern_cpp_template_CLANG_STRICT_AT_LEAST(x, y, z) 0
#  define modern_cpp_template_CLANG_STRICT_LESS_THAN(x, y, z) 0
#endif

//------------------------------------------------------------------------------------------
// Architecture identification, modern_cpp_template_ARCH_*
//------------------------------------------------------------------------------------------

#if defined(__x86_64__) || (defined(_M_X64) && !defined(_M_ARM64EC)) || \
    defined(__amd64)
#  define modern_cpp_template_ARCH_x86_64 1
#else
#  define modern_cpp_template_ARCH_x86_64 0
#endif

#if defined(__i386__) || defined(_M_IX86) || defined(_X86_) || defined(__i386)
#  define modern_cpp_template_ARCH_i386 1
#else
#  define modern_cpp_template_ARCH_i386 0
#endif

#if modern_cpp_template_ARCH_x86_64 || modern_cpp_template_ARCH_i386
#  define modern_cpp_template_ARCH_i386_OR_x86_64 1
#else
#  define modern_cpp_template_ARCH_i386_OR_x86_64 0
#endif

/// \internal modern_cpp_template_ARCH_ARM set to 1 if the architecture is ARM
#if defined(__arm__)
#  define modern_cpp_template_ARCH_ARM 1
#else
#  define modern_cpp_template_ARCH_ARM 0
#endif

/// \internal modern_cpp_template_ARCH_ARM64 set to 1 if the architecture is
/// ARM64
#if defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC)
#  define modern_cpp_template_ARCH_ARM64 1
#else
#  define modern_cpp_template_ARCH_ARM64 0
#endif

/// \internal modern_cpp_template_ARCH_ARM_OR_ARM64 set to 1 if the architecture
/// is ARM or ARM64
#if modern_cpp_template_ARCH_ARM || modern_cpp_template_ARCH_ARM64
#  define modern_cpp_template_ARCH_ARM_OR_ARM64 1
#else
#  define modern_cpp_template_ARCH_ARM_OR_ARM64 0
#endif

/// \internal modern_cpp_template_ARCH_ARMV8 set to 1 if the architecture is
/// armv8 or greater.
#if modern_cpp_template_ARCH_ARM_OR_ARM64 && defined(__ARM_ARCH) && \
    __ARM_ARCH >= 8
#  define modern_cpp_template_ARCH_ARMV8 1
#else
#  define modern_cpp_template_ARCH_ARMV8 0
#endif

/// \internal modern_cpp_template_HAS_ARM64_FP16 set to 1 if the architecture
/// provides an IEEE compliant Arm fp16 type
#if modern_cpp_template_ARCH_ARM_OR_ARM64
#  ifndef modern_cpp_template_HAS_ARM64_FP16
#    if defined(__ARM_FP16_FORMAT_IEEE)
#      define modern_cpp_template_HAS_ARM64_FP16 1
#    else
#      define modern_cpp_template_HAS_ARM64_FP16 0
#    endif
#  endif
#endif

/// \internal modern_cpp_template_ARCH_MIPS set to 1 if the architecture is MIPS
#if defined(__mips__) || defined(__mips)
#  define modern_cpp_template_ARCH_MIPS 1
#else
#  define modern_cpp_template_ARCH_MIPS 0
#endif

/// \internal modern_cpp_template_ARCH_SPARC set to 1 if the architecture is
/// SPARC
#if defined(__sparc__) || defined(__sparc)
#  define modern_cpp_template_ARCH_SPARC 1
#else
#  define modern_cpp_template_ARCH_SPARC 0
#endif

/// \internal modern_cpp_template_ARCH_IA64 set to 1 if the architecture is
/// Intel Itanium
#if defined(__ia64__)
#  define modern_cpp_template_ARCH_IA64 1
#else
#  define modern_cpp_template_ARCH_IA64 0
#endif

/// \internal modern_cpp_template_ARCH_PPC set to 1 if the architecture is
/// PowerPC
#if defined(__powerpc__) || defined(__ppc__) || defined(_M_PPC) || \
    defined(__POWERPC__)
#  define modern_cpp_template_ARCH_PPC 1
#else
#  define modern_cpp_template_ARCH_PPC 0
#endif
