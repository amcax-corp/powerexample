/// @file      GeomEMacros.hpp
/// @brief     Enumerations in GeomE
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX {
namespace GeomE {
/// @brief Type of edges
enum class EdgeType
{
	FreeEdge,
	ManifoldEdge,
	NonManifoldEdge,
	Undefined
};

#ifdef INTERNAL_TEST
/// @brief Extension mode for the face list during the imprint operation.
enum class FaceListExtension
{
	None,       // Do not extend the face list
	TargetOnly, // Extend the face list for the target only
	ToolOnly,   // Extend the face list for the tool only
	Both        // Extend the face list for both the target and the tool
};

/// @brief Completion mode for the imprint operation.
enum class ImprintCompletion
{
	None,        // Do not complete the imprint.
	FirstEdge,   // Complete the imprint up to the first edge encountered on the
	             // body or face.
	LaminarEdge, // Complete the imprint up to the first laminar edge
	             // encountered on the body or face.
	FaceSetBoundary // Complete the imprint up to the first edge that is either
	                // a laminar edge or a boundary edge of the supplied face
	                // set.
};
#endif
} // namespace GeomE
} // namespace AMCAX