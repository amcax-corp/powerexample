/// @file      Options.hpp
/// @brief     Defines data structures for configuration options across various
/// functionalities
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <array>
#include <list>
#include <shapeEdit/GeomEMacros.hpp>
#include <topology/TopoFace.hpp>
#include <vector>

namespace AMCAX {
namespace GeomE {
/// @brief Boolean matching region with specified tolerance
struct BooleanMatchRegion
{
	std::array<TopoShape, 2> regions;
	double                   tolerance = 0.0;

	/// @brief Default construction of boolean matching region
	/// @return The boolean matching region
	AMCAX_API BooleanMatchRegion() = default;

	/// @brief Construct a boolean matching region with a pair of specified
	/// matching areas and a tolerance
	/// @param region1 The first matching area
	/// @param region2 The second matching area
	/// @param tol The tolerance
	/// @return The boolean matching region
	AMCAX_API BooleanMatchRegion(const TopoShape &region1,
	                             const TopoShape &region2, double tol);

	/// @brief Is the boolean matching region equal to the other boolean matching
	/// region
	/// @param other The other boolean matching region
	/// @return True if two boolean matching regions are equal
	[[nodiscard]] AMCAX_API bool
	operator==(const BooleanMatchRegion &other) const;
};

/// @brief Parameter options for the geometric imprinting operation
struct ImprintOptions
{
	bool                            mergeResult = false;
	double                          tolerance   = 0.0;
	std::vector<BooleanMatchRegion> matchRegions;

#ifdef INTERNAL_TEST
	FaceListExtension faceListExtension = FaceListExtension::None;
	ImprintCompletion targetCompletion  = ImprintCompletion::None;
	ImprintCompletion toolCompletion    = ImprintCompletion::None;
#endif
	/// @brief Default construction of imprinting options
	/// @return The imprinting options
	AMCAX_API ImprintOptions() = default;

	/// @brief Add a boolean matching region
	/// @param region The boolean matching region
	AMCAX_API void AddMatchRegion(const BooleanMatchRegion &region);
};

/// @brief Track shape's modified, generated, and deleted states
struct Trace
{
	std::list<TopoShape> modified, generated;
	bool                 isdeleted = false;
};

/// @brief Configuration options for the face extension operation. The variables
/// modify, mergeResult, and removeRedundantVertex currently only support
/// default values
struct ExtendOptions
{
	/// @brief Whether to extend the source faces directly without creating new
	/// faces
	bool modify = false;

	/// @brief Whether to merge with the target faces
	bool mergeResult = true;

	/// @brief Extension distance
	double extensionDistance = 0.0;

	/// @brief Target face set
	std::vector<TopoFace> target;

	/// @brief Whether to remove redundant vertices
	bool removeRedundantVertex = true;
};

} // namespace GeomE
} // namespace AMCAX