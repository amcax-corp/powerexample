/// @file      BoolBRepFuse.hpp
/// @brief     The class of fuse operation
/// @details   This class computes the fuse shape of two shapes, i.e. the boolean union shape of two shapes.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <boolean/BoolOperation.hpp>

namespace AMCAX
{
/// @brief The class of fuse operation
/// @details This class computes the fuse shape of two shapes, i.e. the boolean union shape of two shapes.
///			This operation requires that all input arguments should have the equal dimensions
class AMCAX_CLASS_API BoolBRepFuse : public BoolOperation
{
public:
	/// @brief Default constructor
	/// @details Only set the type of boolean operation to fuse, and you need to execute Build() to perform the Boolean operation.
	AMCAX_API BoolBRepFuse();

	/// @brief Compute the fuse of two shapes
	/// @details The Build() function is executed internally
	/// @param s1 The argument shape
	/// @param s2 The tool shape
	AMCAX_API BoolBRepFuse(const TopoShape& s1, const TopoShape& s2);

#ifndef DOXYGEN_SKIP

	explicit BoolBRepFuse(const std::shared_ptr<BOAlgoPaveFiller>& PF);

	BoolBRepFuse(const TopoShape& S1, const TopoShape& S2, const std::shared_ptr<BOAlgoPaveFiller>& PF);

#endif

	/// @brief Destructor
	AMCAX_API ~BoolBRepFuse();
};
} // namespace AMCAX
