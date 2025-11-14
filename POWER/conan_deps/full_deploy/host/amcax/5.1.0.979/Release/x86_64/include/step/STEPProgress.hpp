/// @file       STEPProgress.hpp
/// @brief      Class used for carrying data the progress of the STEP process.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

#include <common/Macros.hpp>

namespace AMCAX::STEP
{
/// @brief Message object used to report progress values in the STEP process.
struct STEPProgressMessage
{
	union Payload
	{
		uint64_t u64;
		int64_t i64;
		double f64;
	} payload{UINT64_C(0)};

	/// @brief Type of the payload currently stored in the message.
	enum PayloadType
	{
		NONE_TYPE = -1, ///< No payload.
		U64_TYPE = 0,	///< Payload contains uint64_t.
		I64_TYPE = 1,	///< Payload contains int64_t.
		F64_TYPE = 2,	///< Payload contains double.
	} type{NONE_TYPE};

	/// @brief Default constructor. Creates an empty message.
	AMCAX_API STEPProgressMessage();

	/// @brief Construct from a uint64_t value.
	/// @param u64 Unsigned integer payload.
	AMCAX_API STEPProgressMessage(const uint64_t u64);

	/// @brief Construct from an int64_t value.
	/// @param i64 Signed integer payload.
	AMCAX_API STEPProgressMessage(const int64_t i64);

	/// @brief Construct from a double value.
	/// @param d64 Floating-point payload.
	AMCAX_API STEPProgressMessage(const double d64);

	/// @brief Destructor.
	AMCAX_API ~STEPProgressMessage();
};

/// @brief Encapsulates a specific state value in the STEP process (reader or writer).
class AMCAX_CLASS_API STEPProgressState
{
public:
	// Error states
	/// @brief Error state: reader failed (no parameters).
	static constexpr int ReaderFailed = 0x00 - 1; // -1
	/// @brief Error state: writer failed (no parameters).
	static constexpr int WriterFailed = ReaderFailed - 1; // -2

	// Normal states - Reader
	/// @brief Reader: start state (no parameters).
	static constexpr int ReaderStart = 0x00 + 0; // 0
	/// @brief Reader: lexing started (no parameters).
	static constexpr int ReaderLexingStart = ReaderStart + 1; // 1
	/// @brief Reader: lexing completed (no parameters).
	static constexpr int ReaderLexingComplete = ReaderLexingStart + 1; // 2
	/// @brief Reader: initialization phase started (no parameters).
	static constexpr int ReaderGeneratingInitStart = ReaderLexingComplete + 1; // 3
	/// @brief Reader: initialization phase completed (no parameters).
	static constexpr int ReaderGeneratingInitComplete = ReaderGeneratingInitStart + 1; // 4
	/// @brief Reader: shape generation started. Second payload = total number of shapes.
	static constexpr int ReaderGeneratingStart = ReaderGeneratingInitComplete + 1; // 5
	/// @brief Reader: shape generation in progress. First payload = number of shapes generated,
	/// second payload = total number of shapes to generate.
	static constexpr int ReaderGeneratingInProgress = ReaderGeneratingStart + 1; // 6
	/// @brief Reader: shape generation completed. First payload = number of shapes generated,
	/// second payload = total number of shapes.
	static constexpr int ReaderGeneratingComplete = ReaderGeneratingInProgress + 1; // 7

	/// @brief Reader: shape fixing started. Second payload = number of shapes to fix.
	static constexpr int ReaderFixingStart = 0x10 + 0; // 16
	/// @brief Reader: shape fixing in progress. First payload = number of shapes fixed,
	/// second payload = number of shapes to fix.
	static constexpr int ReaderFixingInProgress = ReaderFixingStart + 1; // 17
	/// @brief Reader: shape fixing completed. First payload = number of shapes fixed,
	/// second payload = number of shapes to fix.
	static constexpr int ReaderFixingComplete = ReaderFixingInProgress + 1; // 18

	/// @brief Reader: finishing phase started (no parameters).
	static constexpr int ReaderFinishingUpStart = ReaderGeneratingComplete + 1; // 8
	/// @brief Reader: finishing phase completed (no parameters).
	static constexpr int ReaderFinishingUpComplete = ReaderFinishingUpStart + 1; // 9
	/// @brief Reader: completed successfully (no parameters).
	static constexpr int ReaderComplete = ReaderFinishingUpComplete + 1; // 10

	// Normal states - Writer
	/// @brief Writer: start state (no parameters).
	static constexpr int WriterStart = 0x100 + 0; // 256
	/// @brief Writer: writing in progress. First payload = number of shapes written so far.
	static constexpr int WriterInProgress = WriterStart + 1; // 257
	/// @brief Writer: writing completed. First payload = total number of shapes written.
	static constexpr int WriterComplete = WriterInProgress + 1; // 258

	/// @brief Implicit conversion to integer state code.
	operator int() const
	{
		return state;
	}

	/// @brief Construct from a state code.
	/// @param s The state code.
	STEPProgressState(const int s)
		: state(s)
	{
	}

	/// @brief Destructor.
	virtual ~STEPProgressState() = default;

protected:
	int state{0};
};

/// @brief Callback type for reporting progress.
/// @param state The progress state.
/// @param payload1 The first payload value.
/// @param payload2 The second payload value.
using STEPProgressCallback = std::function<void(
	const STEPProgressState state,
	const STEPProgressMessage payload1,
	const STEPProgressMessage payload2)>;

/// @brief Event type for STEP data reading progress.
enum class STEPDataEvent
{
	/// @brief Default unspecified event.
	Unspecified,

	/// @brief The STEPProduct tree is fully constructed.
	/// All data except PrivateShapes, properties, and labels are ready.
	/// Access via Reader::GetShapes(). Undefined behavior if accessing data not yet ready.
	ProductReady,

	/// @brief Indicates one shape is ready.
	/// First argument = pointer to STEPProduct object.
	/// Second argument = index of the ready shape.
	/// Access shape and its properties via STEPProduct::PrivateShapeAt(index) and STEPProduct::PropertyAt(index).
	ShapeReady,

	/// @brief Indicates one label is ready.
	/// First argument = pointer to STEPProduct object.
	/// Second argument = index of the ready label (correlated with ShapeReady index).
	/// Access via STEPProduct::LabelAt(index).
	LabelReady,

	/// @brief Indicates all data is ready.
	DataCompleted,

	/// @brief Indicates the reader entered an error state.
	Error = -1,
};

/// @brief Callback type invoked when data events occur.
/// The callback may be executed in concurrent threads. This may change in future releases.
/// @tparam T Type of STEPProduct node.
/// @param event The data event.
/// @param product The product node related to the event (may be null depending on event).
/// @param index Index associated with the event (e.g. shape or label index).
template<typename T>
using STEPDataCallback = std::function<void(STEPDataEvent event, std::shared_ptr<T> product, size_t index)>;

} // namespace AMCAX::STEP
