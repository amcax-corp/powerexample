/// @file      TMSplineMeshingIO.hpp
/// @brief     Class of export TMSpline triangle mesh to STL or OBJ format
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
struct TMSTriangleMesh;

/// @brief Class of export TMSpline triangle mesh to STL or OBJ format
class TMSplineMeshingIO
{
public:
	/// @brief set the significant digits in export
	AMCAX_API void SetPrecision(int prec);

	/// @brief export a TMSpline triangle mesh to a stl file
	/// @param filename file name with suffix is ".stl"
	/// @param tmsMesh The a triangle creat by a TMSpline
	/// @return true if the export process is succeed
	AMCAX_API bool ExportToSTL(const std::string& filename, const TMSTriangleMesh* tmsMesh) const;

	/// @brief export a TMSpline triangle mesh to a obj file
	/// @param filename file name with suffix is ".obj"
	/// @param tmsMesh The a triangle creat by a TMSpline
	/// @return true if the export process is succeed
	AMCAX_API bool ExportToOBJ(const std::string& filename, const TMSTriangleMesh* tmsMesh) const;

	/// @brief export a TMSpline control net as a polygon mesh to a obj file
	/// @param filename file name with suffix is ".obj"
	/// @param tmsp The TMSpline
	/// @return true if the export process is succeed
	AMCAX_API bool ExportControlToOBJ(const std::string& filename, TMSpline* tmsp) const;

private:
	bool ExportControlToOBJ(std::ostream& _out, TMSpline* tsp) const;

	bool ExportToSTL(std::ostream& _out, const TMSTriangleMesh* tmsMesh) const;

	bool ExportToOBJ(std::ostream& _out, const TMSTriangleMesh* tmsMesh) const;

private:
	bool ExportTMeshToOBJ(const std::string& filename, TMSpline* tmsp) const;

	bool ExportTMeshToOBJ(std::ostream& _out, TMSpline* tsp) const;

private:
	int precision = 6;
};
} // namespace TMS
} // namespace AMCAX
