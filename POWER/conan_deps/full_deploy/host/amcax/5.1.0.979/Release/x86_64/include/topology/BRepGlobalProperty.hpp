/// @file      BRepGlobalProperty.hpp
/// @brief     Class of global property of BRep structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/Macros.hpp>

namespace AMCAX
{
class GlobalProperty;
class TopoShape;

/// @brief Class of global property of BRep structure
class BRepGlobalProperty
{
public:
	/// @brief Compute linear properties, i.e. edge properties
	/// @param[in] s The shape
	/// @param[out] props The property results
	/// @param[in] skipShared Is skip shared shapes
	/// @param[in] useTriangulation Does the computation use triangulation
	AMCAX_API static void LinearProperties(const TopoShape& s, GlobalProperty& props, bool skipShared = false, bool useTriangulation = false);

	/// @brief Compute surface properties, i.e. face properties
	/// @param[in] s The shape
	/// @param[out] props The property results
	/// @param[in] skipShared Is skip shared shapes
	/// @param[in] useTriangulation Does the computation use triangulation
	AMCAX_API static void SurfaceProperties(const TopoShape& s, GlobalProperty& props, bool skipShared = false, bool useTriangulation = false);

	/// @brief Compute surface properties, i.e. face properties
	/// @param[in] s The shape
	/// @param[out] props The property results
	/// @param[in] eps The tolerance used in numerical integration
	/// @param[in] skipShared Is skip shared shapes
	/// @return The estimation error of computation
	AMCAX_API static double SurfaceProperties(const TopoShape& s, GlobalProperty& props, double eps, bool skipShared = false);

	/// @brief Compute volume properties, i.e. solid properties
	/// @param[in] s The shape
	/// @param[out] props The property results
	/// @param[in] onlyClosed Is only closed solids computed
	/// @param[in] skipShared Is skip shared shapes
	/// @param[in] useTriangulation Does the computation use triangulation
	AMCAX_API static void VolumeProperties(const TopoShape& s, GlobalProperty& props, bool onlyClosed = false, bool skipShared = false, bool useTriangulation = false);

	/// @brief Compute volume properties, i.e. solid properties
	/// @param[in] s The shape
	/// @param[out] props The property results
	/// @param[in] eps The tolerance used in numerical integration
	/// @param[in] onlyClosed Is only closed solids computed
	/// @param[in] skipShared Is skip shared shapes
	/// @return The estimation error of computation
	AMCAX_API static double VolumeProperties(const TopoShape& s, GlobalProperty& props, double eps, bool onlyClosed = false, bool skipShared = false);
};
} // namespace AMCAX
