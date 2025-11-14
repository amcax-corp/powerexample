/// @file      MeshFillHole.hpp
/// @brief     Class of PolyMesh API for fill hole
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for fill hole
class MeshFillHole
{
public:
	/// @brief fill hole whit input edge by use a singel polygon face
	/// @param mesh the PolyMesh
	/// @param edge input edge
	/// @return true if the process successful
	AMCAX_API static bool FillSingleHole(PolyMesh* mesh, int edge);

	/// @brief fill all holes in PolyMesh by use a singel polygon face
	/// @param mesh the PolyMesh
	/// @return true if the process successful
	AMCAX_API static bool FillAllHole(PolyMesh* mesh);
};

} // namespace SubD
} // namespace AMCAX
