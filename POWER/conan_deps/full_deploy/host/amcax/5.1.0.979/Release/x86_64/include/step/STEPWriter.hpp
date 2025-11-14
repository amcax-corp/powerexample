/// @file       STEPWriter.hpp
/// @brief		Class for exporting TopoShape objects and related data to STEP files.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <cstdint>
#include <fstream>
#include <memory>
#include <ostream>
#include <variant>
#include <vector>

#include <common/Macros.hpp>

#include <step/STEPLabelProduct.hpp>
#include <step/STEPLengthUnit.hpp>
#include <step/STEPOptions.hpp>
#include <step/STEPProduct.hpp>
#include <step/STEPProgress.hpp>
#include <step/STEPStyledProduct.hpp>
#include <step/mesh/STEPMeshProduct.hpp>

#include <af/label/Label.hpp>

namespace AMCAX::STEP
{
class STEPGroup;
class STEPLayer;
class WriterImpl;

/// @brief Class for exporting TopoShape objects and related data to STEP files.
class STEPWriter
{
public:
	/// @brief Construct a STEPWriter with an output stream.
	/// @param os The output stream. The caller manages the stream's lifetime.
	AMCAX_API explicit STEPWriter(std::ostream& os);

	/// @brief Construct a STEPWriter with the given output file path.
	/// @param file The output file path (absolute or relative).
	AMCAX_API explicit STEPWriter(const std::string& file);

	/// @brief Destructor.
	AMCAX_API ~STEPWriter();

	/// @brief Set the length unit of the STEP file.
	/// @param unit The length unit to use for export.
	AMCAX_API void SetOutputUnit(const STEPLengthUnit unit);

	/// @brief Initialize the writer and write the STEP file header.
	///
	/// Must be called before any WriteShape(s) or Done.
	AMCAX_API void Init();

	/// @brief Add a list of STEPProduct trees to the export list.
	/// @param products List of STEPProduct objects (each may include Label and related data).
	/// @retval true If at least one shape is exported successfully.
	/// @retval false If no shapes are exported.
	AMCAX_API bool WriteShapes(const std::vector<std::shared_ptr<STEPProduct>>& products);

	/// @overload
	AMCAX_API bool WriteShapes(const std::vector<std::shared_ptr<STEPStyledProduct>>& products);

	/// @overload
	AMCAX_API bool WriteShapes(const std::vector<std::shared_ptr<STEPLabelProduct>>& products);

#ifdef AMCAXMeshing_Enable_EigenTraits
	/// @overload
	AMCAX_API bool WriteShapes(const std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>>& products);
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
	/// @overload
	AMCAX_API bool WriteShapes(const std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>>& products);
#endif

	/// @brief Add a list of TopoShape objects to the export list.
	/// @param shapes List of TopoShape objects to export.
	/// @retval true If at least one shape is exported successfully.
	/// @retval false If no shapes are exported.
	AMCAX_API bool WriteShapes(const std::vector<TopoShape>& shapes);

	/// @brief Add a STEPProduct tree to the export list.
	/// @param product STEPProduct object to export.
	/// @retval true If the shape is exported successfully.
	/// @retval false Otherwise.
	AMCAX_API bool WriteShape(const std::shared_ptr<STEPProduct>& product);

	/// @overload
	AMCAX_API bool WriteShape(const std::shared_ptr<STEPStyledProduct>& product);

	/// @overload
	AMCAX_API bool WriteShape(const std::shared_ptr<STEPLabelProduct>& product);

#ifdef AMCAXMeshing_Enable_EigenTraits
	/// @overload
	AMCAX_API bool WriteShape(const std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>& product);
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
	/// @overload
	AMCAX_API bool WriteShape(const std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>& product);
#endif

	/// @brief Add a TopoShape object to the export list.
	/// @param shape TopoShape object to export.
	/// @retval true If the shape is exported successfully.
	/// @retval false Otherwise.
	AMCAX_API bool WriteShape(const TopoShape& shape);

	/// @brief Add a stateful TopoShape to the export list by its root label.
	/// @param root Root Label of the shape to be exported.
	/// @retval true If the shape is valid.
	/// @retval false Otherwise.
	AMCAX_API bool WriteShape(Label& root);

	/// @brief Add a list of Label objects to the export list.
	/// @param roots List of Label objects to export.
	/// @retval true If at least one shape is exported successfully.
	/// @retval false If no shapes are exported.
	AMCAX_API bool WriteShapes(const std::vector<Label>& roots);

	/// @brief Write the end section of the STEP file and close the output.
	/// @retval true If the end section is written successfully.
	/// @retval false Otherwise.
	AMCAX_API bool Done();

	/// @brief Set the progress callback function.
	/// @param callback The callback to be invoked to report progress.
	AMCAX_API void SetProgressCallback(const STEPProgressCallback& callback);

	/// @brief Set the STEP writer options.
	/// @param options The STEP export options.
	AMCAX_API void SetOptions(const STEPOptions& options);

	/// @brief Get the current STEP writer options.
	/// @return STEP writer options.
	AMCAX_API const STEPOptions GetOptions() const;

	/// @brief Add a STEPGroup to the STEP file.
	/// @note If none of the group's members match any TopoShape written via WriteShape or WriteShapes, the group will not appear in the output.
	/// @param group The group to add.
	AMCAX_API void AddGroup(const STEPGroup& group);

	/// @brief Add a STEPLayer to the STEP file.
	/// @param layer The layer to add.
	AMCAX_API void AddLayer(const STEPLayer& layer);

private:
	std::unique_ptr<WriterImpl> imp;

	std::ostream* osany{nullptr};
	std::unique_ptr<std::ofstream> osfile;
	std::string filename;

	STEPProgressCallback _callback;
	size_t shapecounter{UINT64_C(0)};

	STEPOptions options;

	bool initialized{false};
	bool isdone{false};
};
} // namespace AMCAX::STEP
