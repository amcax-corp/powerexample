/**
 * @file Macros.hpp
 * @brief Define macros used by AMCAXMeshing library.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

// NOTE When you add new macros to this file,
//      make sure the new macros are put into right region.

#ifdef AMCAXMeshing_HAS_IMPL
  /// Some our macros rely on boost's defined macors.
	#include <boost/config.hpp>
	#include <boost/predef.h>

  /*********************************************************/
  /* Macros about multithreads *****************************/
  /*********************************************************/
	#pragma region Macros_about_multithreads

	#if !defined(AMCAXMeshing_MultiThreads)
		#if defined(BOOST_HAS_THREADS) || defined(_OPENMP)
			#define AMCAXMeshing_MultiThreads
		#endif
	#endif

	#pragma endregion Macros_about_multithreads

  /*********************************************************/
  /* Macros about platform *****************************/
  /*********************************************************/
	#pragma region Macros_about_platform

	#if !defined(AMCAXMeshing_EndianLittleByte) && \
	  !defined(AMCAXMeshing_EndianBigByte)
		#if BOOST_ENDIAN_BIG_BYTE
			#define AMCAXMeshing_EndianBigByte
		#elif BOOST_ENDIAN_LITTLE_BYTE
			#define AMCAXMeshing_EndianLittleByte
		#endif
	#endif

	#pragma endregion Macros_about_platform
#endif

/*********************************************************/
/* Macros that operate on macros *************************/
/*********************************************************/
#pragma region Macros_that_operate_on_macros

#ifndef AMCAXMeshing_CONCATE
	#define _AMCAXMeshing_CONCATE_(A, B) A##B
	#define AMCAXMeshing_CONCATE(A, B) _AMCAXMeshing_CONCATE_(A, B)
#endif

#pragma endregion Macros_that_operate_on_macros

/*********************************************************/
/* Macros that abbreviate others *************************/
/*********************************************************/
#pragma region Macros_that_abbreviate_others

#ifndef AMCAXMeshing_UNUSED
	#if __cplusplus >= 201703L 
		#define AMCAXMeshing_UNUSED [[maybe_unused]]
	#else
		#if defined(__GNUC__) || defined(__clang__)
				#define AMCAXMeshing_UNUSED __attribute__((unused))
		#elif defined(_MSC_VER)
			#define AMCAXMeshing_UNUSED [[maybe_unused]]
		#else
				#define AMCAXMeshing_UNUSED 
		#endif
	#endif
#endif


#ifndef AMCAXMeshing_NODISCARD
	#define AMCAXMeshing_NODISCARD [[nodiscard]]
#endif

#ifndef AMCAXMeshing_DEPRECATED
	#define AMCAXMeshing_DEPRECATED [[deprecated]]
#endif

#ifndef AMCAXMeshing_FALLTHROUGH
	#define AMCAXMeshing_FALLTHROUGH [[fallthrough]]
#endif

#pragma endregion Macros_that_abbreviate_others

/*********************************************************/
/* Macros about vectorization    *************************/
/*********************************************************/
#pragma region Macros_about_vectorization

// In MSVC:
//  ----------------------------------------------------------------
// 	  _M_IX86_FP  |  compile options
//       0        |    /arch:IA32
//       1        |    /arch:SSE
//       2        |    /arch:SSE2,/arch:AVX,/arch:AVX2,/arch:AVX512
//  -----------------------------------------------------------------

#if !defined(AMCAXMeshing_SSE2) && !defined(AMCAXMeshing_Disable_SSE2)
// __SSE2__ is a general and explicit macro to define SSE2.
	#if defined(__SSE2__) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2) || \
	  defined(_M_X64)
		#define AMCAXMeshing_SSE2
	#endif
#endif

#if !defined(AMCAXMeshing_AVX) && !defined(AMCAXMeshing_Disable_AVX)
	#if defined(__AVX__)
		#define AMCAXMeshing_AVX
	#endif
#endif

#pragma endregion Macros_about_vectorization

/*********************************************************/
/* Macros that control Debug and Exception ***************/
/*********************************************************/
#pragma region Macros_that_control_Debug_and_Exception

// Enable exception by default
#if !defined(AMCAXMeshing_Enable_Exception) && \
  !defined(AMCAXMeshing_Disable_Exception)
	#define AMCAXMeshing_Enable_Exception
#endif

// Enable assert by default
#if !defined(AMCAXMeshing_Enable_Assert) && \
  !defined(AMCAXMeshing_Disable_Assert)
	#define AMCAXMeshing_Disable_Assert
#endif

// Disable expensive assert by default
#if !defined(AMCAXMeshing_Enable_ExpensiveAssert) && \
  !defined(AMCAXMeshing_Disable_ExpensiveAssert)
	#define AMCAXMeshing_Disable_ExpensiveAssert
#endif

#pragma endregion Macros_that_control_Debug_and_Exception

/*********************************************************/
/* Macros that control AMCAXMeshing features *************/
/*********************************************************/
#pragma region Macros_that_control_AMCAXMeshing_features

// Disable spdlog and fmt by default
#if !defined(AMCAXMeshing_Enable_spdlog) && \
  !defined(AMCAXMeshing_Disable_spdlog)
	#define AMCAXMeshing_Disable_spdlog
#endif

#if !defined(AMCAXMeshing_Enable_fmt) && !defined(AMCAXMeshing_Disable_fmt)
	#define AMCAXMeshing_Disable_fmt
#endif

// Enable Eigen traits by default
#if !defined(AMCAXMeshing_Enable_EigenTraits) && \
  !defined(AMCAXMeshing_Disable_EigenTraits)
	#define AMCAXMeshing_Enable_EigenTraits
#endif

// Enable standard traits by default
#if !defined(AMCAXMeshing_Enable_StandardTraits) && \
  !defined(AMCAXMeshing_Disable_StandardTraits)
	#define AMCAXMeshing_Enable_StandardTraits
#endif

// Enable standard traits by default
#if !defined(AMCAXMeshing_Enable_CommonTraits) && \
  !defined(AMCAXMeshing_Disable_CommonTraits)
	#define AMCAXMeshing_Enable_CommonTraits
#endif

#pragma endregion Macros_that_control_AMCAXMeshing_features

/*********************************************************/
/* Macros that export symbols ****************************/
/*********************************************************/
#pragma region Macros_that_export_symbols

#ifndef AMCAXMeshing_API
	#if defined(__EMSCRIPTEN__) && defined(__GNUG__)
		#include <emscripten.h>
		#define AMCAXMeshing_API EMSCRIPTEN_KEEPALIVE
	#elif defined(BUILD_SHARED)
		#ifdef _MSC_VER
			#define AMCAXMeshing_API __declspec(dllexport)
		#else
			#define AMCAXMeshing_API __attribute__((visibility("default")))
		#endif
	#else
		#define AMCAXMeshing_API
	#endif
#endif

#ifndef AMCAXMeshing_CLASS_API
	#ifdef BUILD_SHARED
		#ifdef _MSC_VER
			#define AMCAXMeshing_CLASS_API 
		#else
			#define AMCAXMeshing_CLASS_API __attribute__((visibility("default")))
		#endif
	#else
		#define AMCAXMeshing_CLASS_API
	#endif
#endif

#pragma endregion Macros_that_export_symbols

/*********************************************************/
/* Macros that output a warning **************************/
/*********************************************************/
#pragma region Macros_that_output_a_warning

template <bool condition>
struct warn_if
{
};

template <>
struct [[deprecated]] warn_if<false>
{
	constexpr warn_if() = default;
};

#define static_warn_if(x, ...) ((void)warn_if<x>())

#pragma endregion Macros_that_output_a_warning

/*********************************************************/
/* Macros that convert a number to string ****************/
/*********************************************************/

#define AMCAXMeshing_VAL(x) #x
#define AMCAXMeshing_STR(x) AMCAXMeshing_VAL(x)