/// @file       BReader.hpp
/// @brief		CRTP base class for STEP file readers.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <fstream>
#include <functional>
#include <istream>
#include <memory>
#include <optional>
#include <vector>

#include <common/Macros.hpp>

#include <step/STEPLengthUnit.hpp>
#include <step/STEPOptions.hpp>
#include <step/STEPProgress.hpp>
#include <step/ShapeStyleLevel.hpp>

namespace AMCAX::STEP
{
class STEPGroup;
class STEPLayer;
class ReaderImpl;

/// @brief CRTP base class for STEP file readers.
/// @details
/// Provides common logic for managing input streams, options, progress
/// and data callbacks, as well as parsed groups and layers.
///
/// Used as a base class by concrete readers (`STEPReader`,
/// `STEPStyledReader`, `STEPLabelReader`).
/// Not intended for direct use.
///
/// To avoid exposing internal helper methods in Doxygen output,
/// most members are wrapped with `#ifndef DOXYGEN_SKIP`.
template<typename T>
class BReader
{
#ifndef DOXYGEN_SKIP
private:
	// Non-copyable.
	BReader& operator=(const BReader&) = delete;
	BReader(const BReader&) = delete;

	// Input management.
	std::istream* m_p_is{nullptr};		 ///< Pointer to input stream (not owned).
	std::optional<std::ifstream> m_file; ///< File stream if reading from file.

	// Parsed product trees.
	std::vector<std::shared_ptr<T>> m_prods; ///< List of product trees (parsed results).

	// Reader configuration.
	STEPOptions m_opts;	   ///< Current reader options.
	STEPLengthUnit m_unit; ///< Unit specified in the STEP file.

	// Parsed metadata.
	std::vector<STEPGroup> m_groups;					  ///< Groups defined in the file.
	std::vector<STEPLayer> m_layers;					  ///< Layers defined in the file.
	ShapeStyleLevel m_style_level{ShapeStyleLevel::FACE}; ///< Style level requested.

	// Reader implementation.
	std::unique_ptr<ReaderImpl> m_p_impl;

protected:
	// Callbacks.
	STEPProgressCallback m_progress;	 ///< Progress callback.
	STEPDataCallback<T> m_data_callback; ///< Data (entity) callback.

protected:
	/// @brief Virtual destructor.
	virtual ~BReader();

	/// @brief Construct from an input stream.
	/// @param is Input stream containing STEP content.
	BReader(std::istream& is);

	/// @brief Construct from a file path.
	/// @param filename Input STEP file path.
	BReader(std::string filename);

	/// @brief Set the internal progress callback.
	void PrivateSetProgressCallback(STEPProgressCallback callback);

	/// @brief Perform the actual read operation.
	/// @param callback Data callback function.
	/// @return true if parsing succeeded, false otherwise.
	bool PrivateRead(STEPDataCallback<T> callback);

	/// @brief Get the file-specified length unit.
	STEPLengthUnit PrivateGetUnit() const;

	/// @brief Set the target length unit for scaling.
	void PrivateSetTargetUnit(const STEPLengthUnit unit);

	/// @brief Set the style level.
	void PrivateSetStyleLevel(const ShapeStyleLevel& style_level);

	/// @brief Access parsed product trees.
	const std::vector<std::shared_ptr<T>>& PrivateGetProducts() const;
	/// @overload
	std::vector<std::shared_ptr<T>>& PrivateGetProducts();

	/// @brief Access reader options.
	const STEPOptions& PrivateGetOptions() const;
	/// @overload
	STEPOptions& PrivateGetOptions();
	void PrivateSetOptions(const STEPOptions& options);

	/// @brief Access parsed groups.
	const std::vector<STEPGroup>& PrivateGetGroups() const;
	/// @overload
	std::vector<STEPGroup>& PrivateGetGroups();

	/// @brief Access parsed layers.
	const std::vector<STEPLayer>& PrivateGetLayers() const;
	/// @overload
	std::vector<STEPLayer>& PrivateGetLayers();

#endif // !DOXYGEN_SKIP
};
} // namespace AMCAX::STEP
