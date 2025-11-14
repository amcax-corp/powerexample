/// @file      PolyMeshIO.hpp
/// @brief     Class of PolyMesh API for load and write a polymesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for load and write a polymesh
class PolyMeshIO
{
public:
	


	/// @brief load a PolyMesh from a file
	/// @param filename file name whit suffix is ".obj" or ".off"
	/// @param mesh the PolyMesh
	/// @return true if the load process is succeed
	AMCAX_API static bool LoadMesh(const std::string& filename, PolyMesh*& mesh);

	/// @brief write a PolyMesh to a file
	/// @param filename file name whit suffix is ".obj" or ".off"
	/// @param mesh the PolyMesh
	/// @return true if the write process is succeed
	AMCAX_API static bool WriteMesh(const std::string& filename, PolyMesh* mesh);

	AMCAX_API static bool LoadMeshStreamOBJ(std::istream& in, PolyMesh* mesh);

	AMCAX_API static bool LoadMeshStreamOFF(std::istream& in, PolyMesh* mesh);

	/// @brief Write the polymesh to the stream in obj format
	/// @param out the output strema
	/// @param mesh the PolyMesh
	/// @param precision the significant digits for write
	/// @return true if the write process is succeed
	AMCAX_API static bool WriteMeshStreamOBJ(std::ostream& out, PolyMesh* mesh, std::streamsize precision = 6);

	/// @brief Write the polymesh to the stream in off format
	/// @param out the output strema
	/// @param mesh the PolyMesh
	/// @param precision the significant digits for write
	/// @return true if the write process is succeed
	AMCAX_API static bool WriteMeshStreamOFF(std::ostream& out, PolyMesh* mesh, std::streamsize precision = 6);

	/// @brief write a PolyMesh to a TMSpline file format
	/// @param filename file name whit suffix is ".tms"
	/// @param mesh the PolyMesh
	/// @return true if the write process is succeed
	AMCAX_API static bool WriteToTMSpline(const std::string& filename, PolyMesh* mesh);
};

} // namespace SubD
} // namespace AMCAX
