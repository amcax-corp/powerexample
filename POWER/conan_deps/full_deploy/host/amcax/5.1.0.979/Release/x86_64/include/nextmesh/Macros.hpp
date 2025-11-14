/// @file      Macros.hpp
/// @brief     Enumerations in NextMesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/CoordT.hpp>
#include <cstddef>
#include <cstdint>
#include <string>
#include <topology/TopoShape.hpp>
#include <vector>

namespace AMCAX {
namespace NextMesh {

using NMMeshElem = void *;
using NMMeshNode = void *;
using NMEntity   = void *;

using Indext = uint32_t;
using EntTag = uint32_t;

/// @brief Type of point/vector
using NMPoint3  = AMCAX::Coord3d;
using NMVector3 = NMPoint3;

/// @brief Shape
using NMShape = AMCAX::TopoShape;

/// @brief Shape with tag
struct TaggedShape
{
	EntTag  tag;
	NMShape shape;
};

/// @brief Input geometry with tags
struct ShapeData
{
	std::vector<TaggedShape> vertices, edges, faces, solids;
};

/// @brief Type of callback function
typedef void(PBCallBackFunc)(int, const std::string &);

/// @brief Type of orientation
enum class Orientation
{
	Forward,
	Reversed,
	Internal,
	External
};

struct NMPolyLine
{
	std::vector<NMPoint3> points; // If the polyline is closed, then the front and
	                              // back of the points are same.
};

/// @brief only support tri or quad mesh
struct NMPolyMesh
{
	std::vector<NMPoint3>            mpoints;
	std::vector<std::vector<Indext>> mfaces; // idx in mpoints
};

/// @brief Type of dimension
enum class DimType
{
	DAll = -1,
	D0   = 0,
	D1   = 1,
	D2   = 2,
	D3   = 3
};

/// @brief Type of mesh element
enum class ElemType
{
	// linear
	Node_1     = 1,
	Line_2     = 2,
	Tri_3      = 3,
	Tet_4      = 4,
	Quad_4     = 5,
	Hex_8      = 6,
	Pyramid_5  = 7,
	Prism_6    = 8,
	// quad-order
	Line_3     = 9,
	Tri_6      = 10,
	Tet_10     = 11,
	////
	Quad_8     = 12,
	Hex_20     = 13,
	Prism_15   = 14,
	Pyramid_13 = 15,
	////
	Quad_9     = 16,
	Hex_27     = 17,
	Prism_18   = 18,
	Pyramid_14 = 19,

};

/// @brief Type of output file
enum class OutFileType
{
	AUTO,
	OBJ,
	VTK,
	FLUENT_MSH
};

/// @brief Control parameters for exporting file
struct OutParams
{
	double    scaleFactor = 1.0;          // scale factor
	NMVector3 move        = {0., 0., 0.}; // translation
	int       precision   = 7;            // significant digits
};

/// @brief Type of commercial software
enum class CommercialSoftware
{
	HyperMesh,
	ANSYS,
	Fluent,
	Nastran,
	UnSet // default
};

/// @brief Type of mesh quality
enum class QualityType
{
	MinLength,
	MaxLength,
	MinHeight,
	MinNormalizedHeight,
	CharacteristicLength,
	ElementQuality,
	SkewnessByVolume,
	SkewnessByEquiangular,
	MaxAngle2d,
	MinAngle2d,
	AspectRatio,
	JacobianRatioByCorner,
	JacobianRatioByGauss,
	Collapse,
	ChordalDeviation,
	WarpingAngle,
	WarpingFactor,
	ParallelDeviation,
	Taper,
	Gamma,
	Eta,
	MaxDihedraAngle,
	MinDihedraAngle,
};

} // namespace NextMesh
} // namespace AMCAX
