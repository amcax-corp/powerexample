/// @file      HLRBRepAlgorithm.hpp
/// @brief     Class of HLR algo
/// @details   Provide methods to HLR. After setting the projection camera,
///            the class can calculate the visible parts and hidden parts (lines) of shapes on a projection plane.
///            The main steps are generating outlined shapes, self hidding and hiding with each other.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <hlr/HLRBRepInternalAlgorithm.hpp>

namespace AMCAX
{
/// @brief Class of HLR algo
class HLRBRepAlgorithm : public HLRBRepInternalAlgorithm
{
public:
	/// @brief Create an empty algo
	AMCAX_API HLRBRepAlgorithm();

	/// @brief Insert the shape
	/// @param S Shape
	/// @param nBRepIsoparameters The number of isoparameters
	AMCAX_API void Add(const TopoShape& S, int nBRepIsoparameters);

#ifndef DOXYGEN_SKIP

	/// @brief Query the id of the shape in algo
	/// @param S Shape
	/// @return ID in algo
	[[nodiscard]] int Index(const TopoShape& S);

	/// @brief Clear outlined shape
	void OutLinedShapeNullify();

#endif
};
} // namespace AMCAX
