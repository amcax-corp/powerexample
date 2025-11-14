/// @file      BoolBRepCut.hpp
/// @brief     The class of cut operation
/// @details   This class computes the result shape of one shape cut by another shape, i.e. the boolean difference shape of two shapes.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <boolean/BoolOperation.hpp>

namespace AMCAX
{
/// @brief The class of cut operation
/// @details This class computes the result shape of one shape cut by another shape, i.e. the boolean difference shape of two shapes.
/// 		This operation requires that the minimal dimension of the tool shape shoud not be less than the maximal dimension of the argument shape
class AMCAX_CLASS_API BoolBRepCut : public BoolOperation
{
public:
	/// @brief Default constructor
	/// @details Only set the type of boolean operation to cut, and you need to execute Build() to perform the Boolean operation.
	AMCAX_API BoolBRepCut();

	/// @brief Compute the cut operation of two shapes
	/// @details The Build() function is executed internally
	/// @param s1 The argument shape
	/// @param s2 The tool shape
	/// @param isForward Cut s1 by s2 if true, and cut s2 by s1 if false
	AMCAX_API BoolBRepCut(const TopoShape& s1, const TopoShape& s2, bool isForward = true);

#ifndef DOXYGEN_SKIP

	explicit BoolBRepCut(const std::shared_ptr<BOAlgoPaveFiller>& PF);

	BoolBRepCut(const TopoShape& S1, const TopoShape& S2, const std::shared_ptr<BOAlgoPaveFiller>& PF, bool isFWD = true);

#endif

	/// @brief Destructor
	AMCAX_API ~BoolBRepCut();
};
} // namespace AMCAX
