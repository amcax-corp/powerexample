/// @file       STEPMeshReader.hpp
/// @brief		Reader for translating STEP files into mesh-based product trees.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <step/STEPOptions.hpp>
#include <step/STEPReader.hpp>

#include <step/mesh/STEPMesh.hpp>
#include <step/mesh/STEPMeshProduct.hpp>
#include <step/mesh/STEPMeshProgress.hpp>

#include <mesh/TriSoup.hpp>

namespace AMCAX::STEP
{
class STEPGroup;
class STEPLayer;

class ReaderImpl;

/// @brief Reader for translating STEP files into mesh-based product trees.
/// @details
/// This reader parses STEP files into TopoShapes, then optionally converts
/// solid shapes into mesh data according to the given meshing deflections.
template<typename T>
class STEPMeshReader : public BReader<STEPMeshProduct<T>>
{
public:
	/// @brief Construct a reader from an input stream.
	/// @param is Input stream containing STEP data.
	AMCAX_API STEPMeshReader(std::istream& is);

	/// @brief Construct a reader from a file path.
	/// @param filename Path to the STEP file.
	AMCAX_API STEPMeshReader(std::string filename);

	/// @brief Destructor.
	AMCAX_API virtual ~STEPMeshReader();

	/// @brief Specify the style level used by the reader.
	/// @param level The style level.
	/// @note If NONE, the reader behaves similarly to the basic STEPReader.
	AMCAX_API void SetStyleLevel(const ShapeStyleLevel& level);

	/// @brief Get the length unit specified by the STEP file.
	/// @note The value is only valid after Read() is done.
	/// @return The length unit.
	AMCAX_API STEPLengthUnit GetUnit() const;

	/// @brief Set the base length unit for scaling (default = millimetres).
	/// @param unit The length unit to use.
	AMCAX_API void SetTargetUnit(const STEPLengthUnit unit);

	/// @brief Set a progress callback for reading and meshing.
	/// @param callback Callback function to report progress.
	AMCAX_API void SetProgressCallback(STEPMeshProgressCallback callback);

	/// @brief Get current options.
	/// @return Constant reference to STEPOptions.
	AMCAX_API const STEPOptions& GetOptions() const;

	/// @overload
	/// @return Modifiable reference to STEPOptions.
	AMCAX_API STEPOptions& GetOptions();

	/// @brief Set reader options.
	/// @param options New options to apply.
	AMCAX_API void SetOptions(const STEPOptions& options);

	/// @brief Read and parse STEP entities.
	/// @param callback Optional callback invoked when partial data is ready.
	/// @retval true Reading succeeded.
	/// @retval false Exception occurred during reading.
	AMCAX_API bool Read(STEPDataCallback<STEPMeshProduct<T>> callback = nullptr);

	/// @brief Convert TopoShapes to meshes.
	/// @param linDeflection Linear deflection for meshing.
	/// @param isRelative True if deflection is relative to shape size.
	/// @retval true If at least one TopoShell was successfully meshed.
	/// @retval false Otherwise.
	AMCAX_API bool ToMesh(double linDeflection = 1e-2,
		bool isRelative = true);

	/// @brief Convert TopoShapes to meshes.
	/// @param linDeflection Linear deflection for meshing.
	/// @param isRelative True if deflection is relative to shape size.
	/// @param angDeflection Angular deflection for meshing.
	/// @retval true If at least one TopoShell was successfully meshed.
	/// @retval false Otherwise.
	AMCAX_API bool ToMesh(double linDeflection,
		bool isRelative, double angDeflection);

	/// @brief Get the parsed STEPMeshProduct nodes.
	/// @note Only valid after Read().
	/// @return Const reference to product list.
	AMCAX_API const std::vector<std::shared_ptr<STEPMeshProduct<T>>>& GetProducts() const;

	/// @overload
	AMCAX_API std::vector<std::shared_ptr<STEPMeshProduct<T>>>& GetProducts();

	/// @brief Get groups defined in the STEP file.
	/// @note Only valid after Read().
	/// @return Const reference to group list.
	AMCAX_API const std::vector<STEPGroup>& GetGroups() const;

	/// @overload
	AMCAX_API std::vector<STEPGroup>& GetGroups();

	/// @brief Get layers defined in the STEP file.
	/// @note Only valid after Read().
	/// @return Const reference to layer list.
	AMCAX_API const std::vector<STEPLayer>& GetLayers() const;

	/// @overload
	AMCAX_API std::vector<STEPLayer>& GetLayers();

private:
	STEPMeshProgressCallback mesh_progress; ///< Meshing progress callback.
};

#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAX_CLASS_API STEPMeshReader<AMCAX::Meshing::Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAX_CLASS_API STEPMeshReader<AMCAX::Meshing::Mesh::TriSoupTraits_Coord>;
#endif
} // namespace AMCAX::STEP
