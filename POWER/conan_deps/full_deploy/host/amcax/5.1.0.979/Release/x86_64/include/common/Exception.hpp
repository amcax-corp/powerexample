#ifndef DOXYGEN_SKIP

/// @file      Exception.hpp
/// @brief     Define exception handling
/// @details   Define various exception classes and convenient macro interfaces
///            Typical exceptions include construction error,
///            domain error, negative value error, no such object error,
///            not done error, null object error, null value error,
///            out of range error, and not implemented error
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <stdexcept>
#include <string>
#include <system_error>

#include <common/Macros.hpp>

#if defined(INTERNAL_TEST) && defined(_MSC_VER)

namespace AMCAX
{
#define DEFINE_ERROR_TYPE(err, base)             \
	class err : public base                      \
	{                                            \
	public:                                      \
		explicit err(const std::string& message) \
			: base(message)                      \
		{                                        \
		}                                        \
	};

DEFINE_ERROR_TYPE(_LogicError, std::logic_error)
DEFINE_ERROR_TYPE(_DomainError, std::domain_error)
DEFINE_ERROR_TYPE(_RuntimeError, std::runtime_error)
DEFINE_ERROR_TYPE(_UnderflowError, std::underflow_error)
DEFINE_ERROR_TYPE(_OverflowError, std::overflow_error)
DEFINE_ERROR_TYPE(_OutOfRange, std::out_of_range)
#define DEFINE_DOMAIN_ERROR_TYPE(err) DEFINE_ERROR_TYPE(err, _DomainError)
DEFINE_DOMAIN_ERROR_TYPE(_ConstructionError)
DEFINE_DOMAIN_ERROR_TYPE(_DimensionError)
DEFINE_DOMAIN_ERROR_TYPE(_DimensionMismatch)
DEFINE_DOMAIN_ERROR_TYPE(_ImmutableObject)
DEFINE_DOMAIN_ERROR_TYPE(_MultiplyDefined)
DEFINE_DOMAIN_ERROR_TYPE(_NoMoreObject)
DEFINE_DOMAIN_ERROR_TYPE(_NoSuchObject)
DEFINE_DOMAIN_ERROR_TYPE(_NullObject)
DEFINE_DOMAIN_ERROR_TYPE(_NegativeValue)
DEFINE_DOMAIN_ERROR_TYPE(_NullValue)
DEFINE_DOMAIN_ERROR_TYPE(_TypeMismatch)
#undef DEFINE_DOMAIN_ERROR_TYPE
DEFINE_ERROR_TYPE(_DividedByZero, _RuntimeError)
DEFINE_ERROR_TYPE(_ProgramError, _RuntimeError)
DEFINE_ERROR_TYPE(_NotDoneError, _RuntimeError)
DEFINE_ERROR_TYPE(_InfiniteSolutions, _RuntimeError)
DEFINE_ERROR_TYPE(_OutOfMemory, _ProgramError)
DEFINE_ERROR_TYPE(_NotImplemented, _ProgramError)
#undef DEFINE_ERROR_TYPE
} // namespace AMCAX

#define METAINFO(err) std::string("[").append(#err) + "] " + __FILE__ + "(" + std::to_string(__LINE__) + "), in " + __FUNCTION__ + "(). "
#define DEFINE_EXCEPTION(err, message) _##err(METAINFO(err) + message)
#define DEFINE_EXCEPTION_IF(err, cond, message) \
	if (cond)                                   \
	throw AMCAX::_##err(METAINFO(err) + message)

#define LogicError(message) DEFINE_EXCEPTION(LogicError, message)
#define DomainError(message) DEFINE_EXCEPTION(DomainError, message)
#define RuntimeError(message) DEFINE_EXCEPTION(RuntimeError, message)
#define UnderflowError(message) DEFINE_EXCEPTION(UnderflowError, message)
#define OverflowError(message) DEFINE_EXCEPTION(OverflowError, message)
#define OutOfRange(message) DEFINE_EXCEPTION(OutOfRange, message)
#define ConstructionError(message) DEFINE_EXCEPTION(ConstructionError, message)
#define DimensionError(message) DEFINE_EXCEPTION(DimensionError, message)
#define DimensionMismatch(message) DEFINE_EXCEPTION(DimensionMismatch, message)
#define ImmutableObject(message) DEFINE_EXCEPTION(ImmutableObject, message)
#define MultiplyDefined(message) DEFINE_EXCEPTION(MultiplyDefined, message)
#define NoMoreObject(message) DEFINE_EXCEPTION(NoMoreObject, message)
#define NoSuchObject(message) DEFINE_EXCEPTION(NoSuchObject, message)
#define NullObject(message) DEFINE_EXCEPTION(NullObject, message)
#define NegativeValue(message) DEFINE_EXCEPTION(NegativeValue, message)
#define NullValue(message) DEFINE_EXCEPTION(NullValue, message)
#define TypeMismatch(message) DEFINE_EXCEPTION(TypeMismatch, message)
#define DividedByZero(message) DEFINE_EXCEPTION(DividedByZero, message)
#define ProgramError(message) DEFINE_EXCEPTION(ProgramError, message)
#define NotDoneError(message) DEFINE_EXCEPTION(NotDoneError, message)
#define InfiniteSolutions(message) DEFINE_EXCEPTION(InfiniteSolutions, message)
#define OutOfMemory(message) DEFINE_EXCEPTION(OutOfMemory, message)
#define NotImplemented(message) DEFINE_EXCEPTION(NotImplemented, message)

#ifndef NOEXCEPTION

#define Throw_Construction_Error_if(cond, message) DEFINE_EXCEPTION_IF(ConstructionError, cond, message)
#define Throw_Dimension_Error_if(cond, message) DEFINE_EXCEPTION_IF(DimensionError, cond, message)
#define Throw_Dimension_Mismatch_if(cond, message) DEFINE_EXCEPTION_IF(DimensionMismatch, cond, message)
#define Throw_Divided_by_Zero_if(cond, message) DEFINE_EXCEPTION_IF(DividedByZero, cond, message)
#define Throw_Domain_Error_if(cond, message) DEFINE_EXCEPTION_IF(DomainError, cond, message)
#define Throw_Infinite_Solutions_if(cond, message) DEFINE_EXCEPTION_IF(InfiniteSolutions, cond, message)
#define Throw_Negative_Value_if(cond, message) DEFINE_EXCEPTION_IF(NegativeValue, cond, message)
#define Throw_No_Such_Object_if(cond, message) DEFINE_EXCEPTION_IF(NoSuchObject, cond, message)
#define Throw_Not_Done_Error_if(cond, message) DEFINE_EXCEPTION_IF(NotDoneError, cond, message)
#define Throw_Null_Object_if(cond, message) DEFINE_EXCEPTION_IF(NullObject, cond, message)
#define Throw_Null_Value_if(cond, message) DEFINE_EXCEPTION_IF(NullValue, cond, message)
#define Throw_Out_of_Range_if(cond, message) DEFINE_EXCEPTION_IF(OutOfRange, cond, message)
#define Throw_Type_Mismatch_if(cond, message) DEFINE_EXCEPTION_IF(TypeMismatch, cond, message)
#else
#define Throw_Construction_Error_if(cond, message)
#define Throw_Dimension_Error_if(cond, message)
#define Throw_Dimension_Mismatch_if(cond, message)
#define Throw_Divided_by_Zero_if(cond, message)
#define Throw_Domain_Error_if(cond, message)
#define Throw_Infinite_Solutions_if(cond, message)
#define Throw_Negative_Value_if(cond, message)
#define Throw_No_Such_Object_if(cond, message)
#define Throw_Not_Done_Error_if(cond, message)
#define Throw_Null_Object_if(cond, message)
#define Throw_Null_Value_if(cond, message)
#define Throw_Out_of_Range_if(cond, message)
#define Throw_Type_Mismatch_if(cond, message)
#endif

#define Throw_Not_Implemented() throw AMCAX::NotImplemented("");
#define Throw_Not_Implemented_Checked() throw AMCAX::NotImplemented("");

#else

namespace AMCAX
{
#define DEFINE_ERROR_TYPE(err, base)             \
	class err : public base                      \
	{                                            \
	public:                                      \
		explicit err(const std::string& message) \
			: base(message)                      \
		{                                        \
		}                                        \
	};

DEFINE_ERROR_TYPE(_LogicError, std::logic_error)
DEFINE_ERROR_TYPE(_DomainError, std::domain_error)
DEFINE_ERROR_TYPE(_RuntimeError, std::runtime_error)
DEFINE_ERROR_TYPE(_UnderflowError, std::underflow_error)
DEFINE_ERROR_TYPE(_OverflowError, std::overflow_error)
DEFINE_ERROR_TYPE(_OutOfRange, std::out_of_range)
#define DEFINE_DOMAIN_ERROR_TYPE(err) DEFINE_ERROR_TYPE(err, _DomainError)
DEFINE_DOMAIN_ERROR_TYPE(_ConstructionError)
DEFINE_DOMAIN_ERROR_TYPE(_DimensionError)
DEFINE_DOMAIN_ERROR_TYPE(_DimensionMismatch)
DEFINE_DOMAIN_ERROR_TYPE(_ImmutableObject)
DEFINE_DOMAIN_ERROR_TYPE(_MultiplyDefined)
DEFINE_DOMAIN_ERROR_TYPE(_NoMoreObject)
DEFINE_DOMAIN_ERROR_TYPE(_NoSuchObject)
DEFINE_DOMAIN_ERROR_TYPE(_NullObject)
DEFINE_DOMAIN_ERROR_TYPE(_NegativeValue)
DEFINE_DOMAIN_ERROR_TYPE(_NullValue)
DEFINE_DOMAIN_ERROR_TYPE(_TypeMismatch)
#undef DEFINE_DOMAIN_ERROR_TYPE
DEFINE_ERROR_TYPE(_DividedByZero, _RuntimeError)
DEFINE_ERROR_TYPE(_ProgramError, _RuntimeError)
DEFINE_ERROR_TYPE(_NotDoneError, _RuntimeError)
DEFINE_ERROR_TYPE(_InfiniteSolutions, _RuntimeError)
DEFINE_ERROR_TYPE(_OutOfMemory, _ProgramError)
DEFINE_ERROR_TYPE(_NotImplemented, _ProgramError)
#undef DEFINE_ERROR_TYPE

#define METAINFO(err) std::string("[").append(#err) + "]"
#define DEFINE_EXCEPTION_IF(err, cond, message) \
	if (cond)                                   \
	throw AMCAX::_##err(METAINFO(err))
#ifdef BUILD_SHARED
#define DEFINE_EXCEPTION(err) _##err(METAINFO(err))
#define LogicError(message) DEFINE_EXCEPTION(LogicError)
#define DomainError(message) DEFINE_EXCEPTION(DomainError)
#define RuntimeError(message) DEFINE_EXCEPTION(RuntimeError)
#define UnderflowError(message) DEFINE_EXCEPTION(UnderflowError)
#define OverflowError(message) DEFINE_EXCEPTION(OverflowError)
#define OutOfRange(message) DEFINE_EXCEPTION(OutOfRange)
#define ConstructionError(message) DEFINE_EXCEPTION(ConstructionError)
#define DimensionError(message) DEFINE_EXCEPTION(DimensionError)
#define DimensionMismatch(message) DEFINE_EXCEPTION(DimensionMismatch)
#define ImmutableObject(message) DEFINE_EXCEPTION(ImmutableObject)
#define MultiplyDefined(message) DEFINE_EXCEPTION(MultiplyDefined)
#define NoMoreObject(message) DEFINE_EXCEPTION(NoMoreObject)
#define NoSuchObject(message) DEFINE_EXCEPTION(NoSuchObject)
#define NullObject(message) DEFINE_EXCEPTION(NullObject)
#define NegativeValue(message) DEFINE_EXCEPTION(NegativeValue)
#define NullValue(message) DEFINE_EXCEPTION(NullValue)
#define TypeMismatch(message) DEFINE_EXCEPTION(TypeMismatch)
#define DividedByZero(message) DEFINE_EXCEPTION(DividedByZero)
#define ProgramError(message) DEFINE_EXCEPTION(ProgramError)
#define NotDoneError(message) DEFINE_EXCEPTION(NotDoneError)
#define InfiniteSolutions(message) DEFINE_EXCEPTION(InfiniteSolutions)
#define OutOfMemory(message) DEFINE_EXCEPTION(OutOfMemory)
#define NotImplemented(message) DEFINE_EXCEPTION(NotImplemented)
#else
#define DEFINE_EXCEPTION(err)         \
	template<typename... T>           \
	inline _##err(err)(T...)          \
	{                                 \
		return _##err(METAINFO(err)); \
	}
DEFINE_EXCEPTION(LogicError)
DEFINE_EXCEPTION(DomainError)
DEFINE_EXCEPTION(RuntimeError)
DEFINE_EXCEPTION(UnderflowError)
DEFINE_EXCEPTION(OverflowError)
DEFINE_EXCEPTION(OutOfRange)
DEFINE_EXCEPTION(ConstructionError)
DEFINE_EXCEPTION(DimensionError)
DEFINE_EXCEPTION(DimensionMismatch)
DEFINE_EXCEPTION(ImmutableObject)
DEFINE_EXCEPTION(MultiplyDefined)
DEFINE_EXCEPTION(NoMoreObject)
DEFINE_EXCEPTION(NoSuchObject)
DEFINE_EXCEPTION(NullObject)
DEFINE_EXCEPTION(NegativeValue)
DEFINE_EXCEPTION(NullValue)
DEFINE_EXCEPTION(TypeMismatch)
DEFINE_EXCEPTION(DividedByZero)
DEFINE_EXCEPTION(ProgramError)
DEFINE_EXCEPTION(NotDoneError)
DEFINE_EXCEPTION(InfiniteSolutions)
DEFINE_EXCEPTION(OutOfMemory)
DEFINE_EXCEPTION(NotImplemented)
#undef DEFINE_EXCEPTION
#endif
} // namespace AMCAX

#ifndef NOEXCEPTION

#define Throw_Construction_Error_if(cond, message) DEFINE_EXCEPTION_IF(ConstructionError, cond, message)
#define Throw_Dimension_Error_if(cond, message) DEFINE_EXCEPTION_IF(DimensionError, cond, message)
#define Throw_Dimension_Mismatch_if(cond, message) DEFINE_EXCEPTION_IF(DimensionMismatch, cond, message)
#define Throw_Divided_by_Zero_if(cond, message) DEFINE_EXCEPTION_IF(DividedByZero, cond, message)
#define Throw_Domain_Error_if(cond, message) DEFINE_EXCEPTION_IF(DomainError, cond, message)
#define Throw_Infinite_Solutions_if(cond, message) DEFINE_EXCEPTION_IF(InfiniteSolutions, cond, message)
#define Throw_Negative_Value_if(cond, message) DEFINE_EXCEPTION_IF(NegativeValue, cond, message)
#define Throw_No_Such_Object_if(cond, message) DEFINE_EXCEPTION_IF(NoSuchObject, cond, message)
#define Throw_Not_Done_Error_if(cond, message) DEFINE_EXCEPTION_IF(NotDoneError, cond, message)
#define Throw_Null_Object_if(cond, message) DEFINE_EXCEPTION_IF(NullObject, cond, message)
#define Throw_Null_Value_if(cond, message) DEFINE_EXCEPTION_IF(NullValue, cond, message)
#define Throw_Out_of_Range_if(cond, message) DEFINE_EXCEPTION_IF(OutOfRange, cond, message)
#define Throw_Type_Mismatch_if(cond, message) DEFINE_EXCEPTION_IF(TypeMismatch, cond, message)
#else
#define Throw_Construction_Error_if(cond, message)
#define Throw_Dimension_Error_if(cond, message)
#define Throw_Dimension_Mismatch_if(cond, message)
#define Throw_Divided_by_Zero_if(cond, message)
#define Throw_Domain_Error_if(cond, message)
#define Throw_Infinite_Solutions_if(cond, message)
#define Throw_Negative_Value_if(cond, message)
#define Throw_No_Such_Object_if(cond, message)
#define Throw_Not_Done_Error_if(cond, message)
#define Throw_Null_Object_if(cond, message)
#define Throw_Null_Value_if(cond, message)
#define Throw_Out_of_Range_if(cond, message)
#define Throw_Type_Mismatch_if(cond, message)
#endif

#define Throw_Not_Implemented() throw AMCAX::NotImplemented("");
#define Throw_Not_Implemented_Checked() throw AMCAX::NotImplemented("");

#endif

#endif

namespace AMCAX
{
/// @brief Error code for common use
enum class CommonError
{
	UnknownError = 0x10000000,
	InvalidArgument = 0x10000001,
	TypeMismatch = 0x10000002
};

/// @brief Construct error code from enumeration
/// @param ec Enumeration of error code
/// @return Error code
[[nodiscard]] AMCAX_API std::error_code MakeErrorCode(CommonError ec) noexcept;

/// @brief Class of kernel error along with error code
class KernelError : public std::system_error
{
	KernelError() = delete;

public:
	/// @brief Construct from error code
	/// @param ec Error code
	AMCAX_API KernelError(std::error_code ec);

	/// @brief Construct from error code and extra message
	/// @param ec Error code
	/// @param message Extra message
	AMCAX_API KernelError(std::error_code ec, const std::string& message);
};
} // namespace AMCAX

/// @def Throw_Kernel_Error
/// @brief The macro for throw exception with error code

#if defined(INTERNAL_TEST) && defined(_MSC_VER)

#ifndef DOXYGEN_SKIP
#define METAINFO2 std::string(__FILE__) + "(" + std::to_string(__LINE__) + ")[" + __FUNCTION__ + "]"
#endif

#define Throw_Kernel_Error(ec, message)                    \
	{                                                      \
		auto _c = AMCAX::MakeErrorCode(ec);                \
		throw AMCAX::KernelError(_c, METAINFO2 + message); \
	}

#else

#define Throw_Kernel_Error(ec, message)        \
	{                                          \
		auto _c = AMCAX::MakeErrorCode(ec);    \
		throw AMCAX::KernelError(_c, message); \
	}

#endif

/// @def Throw_Kernel_Error_if
/// @brief The macro for throw exception with error code under a specific condition

#define Throw_Kernel_Error_if(cond, ec, message) \
	if (cond)                                    \
	Throw_Kernel_Error(ec, message)
