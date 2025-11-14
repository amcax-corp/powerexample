/// @file       STEPReader.hpp
/// @brief		Reader class for translating STEP files into TopoShape objects (without style information).
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

#include <step/BReader.hpp>
#include <step/STEPProduct.hpp>

namespace AMCAX
{
namespace STEP
{
class STEPGroup;
class STEPLayer;
class ReaderImpl;

/// @brief Reader class for translating STEP files into TopoShape objects (without style information).
class AMCAX_CLASS_API STEPReader : public BReader<STEPProduct>
{
public:
	/// @brief Construct a reader from an input stream.
	/// @param is Input stream containing STEP data.
	AMCAX_API STEPReader(std::istream& is);

	/// @brief Construct a reader from a file path.
	/// @param filename Path to the STEP file.
	AMCAX_API STEPReader(std::string filename);

	/// @brief Destructor.
	AMCAX_API virtual ~STEPReader();

	/// @brief Set the base length unit for translation (default is 1.0, millimeters).
	/// @param unit The length unit to use for scaling.
	AMCAX_API void SetTargetUnit(const STEPLengthUnit unit);

	/// @brief Get the length unit specified by the STEP file.
	/// @note The value is only valid after Read() is done.
	/// @return The length unit specified by the STEP file.
	AMCAX_API STEPLengthUnit GetUnit() const;

	/// @brief Set a progress callback function for reading.
	/// @param callback The callback function to be set.
	AMCAX_API void SetProgressCallback(STEPProgressCallback callback);

	/// @brief Get the current options for the STEP reader.
	/// @return Constant reference to the STEPOptions object.
	AMCAX_API const STEPOptions& GetOptions() const;

	/// @overload
	/// @return Modifiable reference to the STEPOptions object.
	AMCAX_API STEPOptions& GetOptions();

	/// @brief Set the options for the STEP reader.
	/// @param options The STEPOptions object to configure the reader.
	AMCAX_API void SetOptions(const STEPOptions& options);

	/// @brief Read STEP entities from the file or stream.
	/// @param callback Optional callback function invoked when data is partially ready.
	/// @retval true Reading succeeded (no exception occurred).
	/// @retval false An exception occurred during reading.
	AMCAX_API bool Read(STEPDataCallback<STEPProduct> callback = nullptr);

	/// @brief Get the list of STEPProduct trees parsed from the STEP file.
	/// @note The value is only valid after Read() is done.
	/// @return Constant reference to the list of STEPProduct nodes.
	AMCAX_API const std::vector<std::shared_ptr<STEPProduct>>& GetProducts() const;

	/// @overload
	AMCAX_API std::vector<std::shared_ptr<STEPProduct>>& GetProducts();

	/// @brief Get the list of groups defined in the STEP file.
	/// @note The value is only valid after Read() is done.
	/// @return A vector of STEPGroup objects.
	AMCAX_API const std::vector<STEPGroup>& GetGroups() const;

	/// @overload
	AMCAX_API std::vector<STEPGroup>& GetGroups();

	/// @brief Get the list of layers defined in the STEP file.
	/// @note The value is only valid after Read() is done.
	/// @return A vector of STEPLayer objects.
	AMCAX_API const std::vector<STEPLayer>& GetLayers() const;

	/// @overload
	AMCAX_API std::vector<STEPLayer>& GetLayers();
};
} // namespace STEP
} // namespace AMCAX

namespace AMCAX
{
namespace STEP
{
extern template class BReader<STEPProduct>;
} // namespace STEP
} // namespace AMCAX
