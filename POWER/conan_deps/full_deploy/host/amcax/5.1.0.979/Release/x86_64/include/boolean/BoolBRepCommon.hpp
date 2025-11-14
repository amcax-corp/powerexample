/// @file      BoolBRepCommon.hpp
/// @brief     The class of common operation
/// @details   This class computes the common shape of two shapes, i.e. the boolean intersection shape of two shapes.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <boolean/BoolOperation.hpp>

namespace AMCAX
{
/// @brief The class of common operation
/// @details This class computes the common shape of two shapes, i.e. the boolean intersection shape of two shapes.
class AMCAX_CLASS_API BoolBRepCommon : public BoolOperation
{
public:
	/// @brief Default constructor
	/// @details Only setting the operation type to common, and you need to execute Build() to perform the Boolean operation.
	AMCAX_API BoolBRepCommon();

	/// @brief Compute the common shape of two shapes
	/// @details The Build() function is executed internally
	/// @param s1 The argument shape
	/// @param s2 The tool shape
	AMCAX_API BoolBRepCommon(const TopoShape& s1, const TopoShape& s2);

#ifndef DOXYGEN_SKIP

	explicit BoolBRepCommon(const std::shared_ptr<BOAlgoPaveFiller>& PF);

	BoolBRepCommon(const TopoShape& S1, const TopoShape& S2, const std::shared_ptr<BOAlgoPaveFiller>& PF);

#endif

	/// @brief Destructor
	AMCAX_API ~BoolBRepCommon();
};
} // namespace AMCAX
