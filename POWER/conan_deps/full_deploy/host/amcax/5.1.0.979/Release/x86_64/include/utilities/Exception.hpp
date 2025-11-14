/**
 * @file Exception.hpp
 * @brief Exception handling in AMCAX Meshing lib.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */
#pragma once

#include <utilities/Logger.hpp>
#if defined(AMCAXMeshing_Enable_fmt)
	#include <fmt/format.h>
#endif

#if defined(AMCAXMeshing_Enable_AMCAXCommonError)
	#include <common/Exception.hpp>
#endif

#include <cassert>
#include <iostream>
#include <stdexcept>

namespace AMCAX {
namespace Meshing {

/*************************************************************************/
/*             Define Meshing Error Types                                */
/*************************************************************************/

enum class MeshingError
{
	UnknownError    = 0x10000000,
	InvalidArgument = 0x10000001,
	TypeMismatch    = 0x10000002,
	LogicError,
	ConstructionError,
	DomainError,
	NonManifoldMesh,
	SelfInterMesh,
	NonManifoldOrSelfInterMesh,
	OutOfRange,
	NullObject,
	NoSuchObject,
	RuntimeError,
	NumericError
};
}; // namespace Meshing

/// @brief Construct error code from enumeration
/// @param ec Enumeration of error code
/// @return Error code

#if defined(AMCAXMeshing_Enable_AMCAXCommonError)
[[nodiscard]] AMCAX_API std::error_code
                        MakeErrorCode(Meshing::MeshingError ec) noexcept;
#else
[[nodiscard]] AMCAXMeshing_API std::error_code
                               MakeErrorCode(Meshing::MeshingError ec) noexcept;

/// @brief Class of kernel error along with error code
class KernelError : public std::system_error
{
	KernelError() = delete;

public:
	/// @brief Construct from error code
	/// @param ec Error code
	AMCAXMeshing_API KernelError(std::error_code ec)
	  : std::system_error(ec){};

	/// @brief Construct from error code and extra message
	/// @param ec Error code
	/// @param message Extra message
	AMCAXMeshing_API KernelError(std::error_code ec, const std::string &message)
	  : std::system_error(ec, message){};
};

/// @def Throw_Kernel_Error
/// @brief The macro for throw exception with error code
#define Throw_Kernel_Error(ec, message)    \
		{                                        \
			auto _c = AMCAX::MakeErrorCode(ec);    \
			throw AMCAX::KernelError(_c, message); \
		}

/// @def Throw_Kernel_Error_if
/// @brief The macro for throw exception with error code under a specific
/// condition
#define Throw_Kernel_Error_if(cond, ec, message) \
		if (cond)                                \
		Throw_Kernel_Error(ec, message)

#endif
}; // namespace AMCAX

namespace AMCAX {
namespace Meshing {

#define DEFINE_ERROR_TYPE(err, base)         \
	class err : public base                    \
	{                                          \
	public:                                    \
		explicit err(const std::string &message) \
		  : base(message)                        \
		{                                        \
		}                                        \
	};
DEFINE_ERROR_TYPE(MeshNotImplemented, std::runtime_error)                                                                 

/*************************************************************************/
/*                      Throw Error Types                                */
/*************************************************************************/

#if defined(AMCAXMeshing_Enable_Exception)
	#if defined(AMCAXMeshing_Enable_fmt) && defined(INTERNAL_TEST)
		#define AMCAXMeshing_Throw(ec, message, ...)                       \
			{                                                                 \
				std::string fmt_msg =                                            \
				  fmt::format("[FILE {}][LINE {}][DATE {}][TIME {}]: " message,     \
				              __FILE__, __LINE__, __DATE__, __TIME__, ##__VA_ARGS__); \
				AMCAX::Meshing::Logger::critical(fmt_msg);                              \
                Throw_Kernel_Error(ec, fmt_msg);
			}
	#else
		#define AMCAXMeshing_Throw(ec, message, ...) \
			{                                            \
				AMCAX::Meshing::Logger::critical(message);   \
                Throw_Kernel_Error(ec, message);                \
			}
	#endif
	#define AMCAXMeshing_Throw_if(condition, ec, message, ...) \
		if (condition)                                           \
		AMCAXMeshing_Throw(ec, message, ##__VA_ARGS__)
#else
	#define AMCAXMeshing_Throw(exception, message, ...)
#endif

  /* Unconditonal Throw */
#define AMCAXMeshing_Throw_Logic_Error(message, ...) \
	AMCAXMeshing_Throw(MeshingError::LogicError, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Construction_Error(message, ...) \
	AMCAXMeshing_Throw(MeshingError::ConstructionError, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Dimension_Mismatch(message, ...) \
	AMCAXMeshing_Throw(MeshingError::TypeMismatch, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_No_Such_Object(message, ...) \
	AMCAXMeshing_Throw(MeshingError::NoSuchObject, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Null_Object(message, ...) \
	AMCAXMeshing_Throw(MeshingError::NullObject, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Out_of_Range(message, ...) \
	AMCAXMeshing_Throw(MeshingError::OutOfRange, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Type_Mismatch(message, ...) \
	AMCAXMeshing_Throw(MeshingError::TypeMismatch, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Invalid_Argument(message, ...) \
	AMCAXMeshing_Throw(MeshingError::InvalidArgument, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_NonManifold_Mesh(message, ...) \
	AMCAXMeshing_Throw(MeshingError::NonManifoldMesh, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_SelfInter_Mesh(message, ...) \
	AMCAXMeshing_Throw(MeshingError::SelfInterMesh, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_NonManifoldOrSelfInter_Mesh(message, ...) \
	AMCAXMeshing_Throw(MeshingError::NonManifoldOrSelfInterMesh, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Runtime_Error(message, ...)    \
	AMCAXMeshing_Throw(MeshingError::RuntimeError, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Numeric_Error(message, ...) \
	AMCAXMeshing_Throw(MeshingError::NumericError, message, ##__VA_ARGS__)

/* Conditonal Throw */
#define AMCAXMeshing_Throw_Logic_Error_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::LogicError, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Construction_Error_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::ConstructionError, message, \
	                      ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Dimension_Mismatch_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::TypeMismatch, message,   \
	                      ##__VA_ARGS__)
#define AMCAXMeshing_Throw_No_Such_Object_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::NoSuchObject, message, \
	                      ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Null_Object_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::NullObject, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Out_of_Range_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::OutOfRange, message, ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Type_Mismatch_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::TypeMismatch, message, \
	                      ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Invalid_Argument_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::InvalidArgument, message, \
	                      ##__VA_ARGS__)
#define AMCAXMeshing_Throw_NonManifold_Mesh_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::NonManifoldMesh, message, \
	                      ##__VA_ARGS__)
#define AMCAXMeshing_Throw_SelfInter_Mesh_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::SelfInterMesh, message, \
	                      ##__VA_ARGS__)
#define AMCAXMeshing_Throw_NonManifoldOrSelfInter_Mesh_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::NonManifoldOrSelfInterMesh,       \
	                      message, \
	                   ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Runtime_Error_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::RuntimeError, message, \
	                      ##__VA_ARGS__)
#define AMCAXMeshing_Throw_Numeric_Error_if(cond, message, ...) \
	AMCAXMeshing_Throw_if(cond, MeshingError::NumericError, message, \
	                      ##__VA_ARGS__)

#define AMCAXMeshing_Throw_Not_Implemented() \
    throw AMCAX::Meshing::MeshNotImplemented(   \
	  std::string("[NMNotImplemented] in ") + __FUNCTION__ + "()");
#define AMCAXMeshing_Throw_Not_Implemented_Checked() \
	 throw AMCAX::Meshing::MeshNotImplemented(         \
	  std::string("[NMNotImplemented] in ") + __FUNCTION__ + "()");

}; // namespace Meshing
}; // namespace AMCAX

namespace AMCAX {
namespace Meshing {
/*************************************************************************/
/*                     Define Debug Assertion                            */
/*************************************************************************/

/// behavior when Assertion fails: exit program of throw exception.
#if defined(AMCAXMeshing_AssertExit)
	#define AssertFail std::exit(1)
#elif defined(AMCAXMeshing_AssertThrow)
	#define AssertFail                        \
		AMCAXMeshing_Throw_Runtime_Error("assert fail")
#endif

#if defined(AMCAXMeshing_Enable_Assert)
	#define AMCAXMeshing_AssertAuxCodes(code) code

  /// Exit program
	#if defined(AMCAXMeshing_Enable_fmt)
		#ifdef INTERNAL_TEST
			#define AMCAXMeshing_Exit(message, ...)                               \
				{                                                                   \
					AMCAX::Meshing::Logger::critical(                                 \
					  fmt::format("[FILE {}][LINE {}]: " message, __FILE__, __LINE__, \
					              ##__VA_ARGS__));                                    \
					std::exit(1);                                                     \
				}
		#else
			#define AMCAXMeshing_Exit(message, ...)     \
				{                                         \
					AMCAX::Meshing::Logger::critical(       \
					  fmt::format(message, ##__VA_ARGS__)); \
					std::exit(1);                           \
				}
		#endif //  INTERNAL_TEST
	#else
		#ifdef INTERNAL_TEST
			#define AMCAXMeshing_Exit(message, ...)                          \
				{                                                              \
					AMCAX::Meshing::Logger::critical(                            \
					  "[" __FILE__ "][" AMCAXMeshing_STR(__LINE__) "]" message); \
					std::exit(1);                                                \
				}
		#else
			#define AMCAXMeshing_Exit(message, ...)        \
				{                                            \
					AMCAX::Meshing::Logger::critical(message); \
					std::exit(1);                              \
				}
		#endif //  INTERNAL_TEST
	#endif

  /// Assert
	#if defined(AMCAXMeshing_Enable_fmt)
		#ifdef INTERNAL_TEST
			#define AMCAXMeshing_Assert(condition, message, ...)              \
				if (!(condition))                                               \
				{                                                               \
					AMCAX::Meshing::Logger::critical(                             \
					  fmt::format("[FILE {}][LINE {}]: " #condition ". " message, \
					              __FILE__, __LINE__, ##__VA_ARGS__));            \
					AssertFail;                                                   \
				}
		#else
			#define AMCAXMeshing_Assert(condition, message, ...)        \
				if (!(condition))                                         \
				{                                                         \
					AMCAX::Meshing::Logger::critical(                       \
					  fmt::format(#condition ". " message, ##__VA_ARGS__)); \
					AssertFail;                                             \
				}
		#endif //  INTERNAL_TEST
	#else
		#ifdef INTERNAL_TEST
			#define AMCAXMeshing_Assert(condition, message, ...)                     \
				if (!(condition))                                                      \
				{                                                                      \
					AMCAX::Meshing::Logger::critical("[" __FILE__ "][" AMCAXMeshing_STR( \
					  __LINE__) "]" #condition message);                                 \
					AssertFail;                                                          \
				}
		#else
			#define AMCAXMeshing_Assert(condition, message, ...)      \
				if (!(condition))                                       \
				{                                                       \
					AMCAX::Meshing::Logger::critical(#condition message); \
					AssertFail;                                           \
				}
		#endif //  INTERNAL_TEST
	#endif
#else
	#define AMCAXMeshing_AssertAuxCodes(code)
	#define AMCAXMeshing_Exit(message, ...)
	#define AMCAXMeshing_Assert(condition, message, ...)
#endif

#ifdef AMCAXMeshing_Enable_ExpensiveAssert

	#define AMCAXMeshing_ExpensiveAssertAuxCodes(code) code

	#ifdef INTERNAL_TEST
		#if defined(AMCAXMeshing_Enable_fmt)
			#define AMCAXMeshing_ExpensiveAssert(condition, message, ...)     \
				if (!(condition))                                               \
				{                                                               \
					AMCAX::Meshing::Logger::critical(                             \
					  fmt::format("[FILE {}][LINE {}]: " #condition ". " message, \
					              __FILE__, __LINE__, ##__VA_ARGS__));            \
					AssertFail;                                                   \
				}
		#else
			#define AMCAXMeshing_ExpensiveAssert(condition, message, ...)    \
				if (!(condition))                                              \
				{                                                              \
					AMCAX::Meshing::Logger::critical(                            \
					  "[" __FILE__ "][" AMCAXMeshing_STR(__LINE__) "]" message); \
					AssertFail;                                                  \
				}
		#endif
	#else
		#if defined(AMCAXMeshing_Enable_fmt)
			#define AMCAXMeshing_ExpensiveAssert(condition, message, ...) \
				if (!(condition))                                           \
				{                                                           \
					AMCAX::Meshing::Logger::critical(                         \
					  fmt::format(#condition ". " message, ##__VA_ARGS__));   \
					AssertFail;                                               \
				}
		#else
			#define AMCAXMeshing_ExpensiveAssert(condition, message, ...) \
				if (!(condition))                                           \
				{                                                           \
					AMCAX::Meshing::Logger::critical(message);                \
					AssertFail;                                               \
				}
		#endif
	#endif //  INTERNAL_TEST
#else
	#define AMCAXMeshing_ExpensiveAssertAuxCodes(code)
	#define AMCAXMeshing_ExpensiveAssert(condition, message, ...)
#endif

} // namespace Meshing
} // namespace AMCAX