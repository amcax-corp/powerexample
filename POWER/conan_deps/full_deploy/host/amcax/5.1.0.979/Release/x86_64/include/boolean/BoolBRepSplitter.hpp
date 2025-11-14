/// @file      BoolBRepSplitter.hpp
/// @brief     The class of splitter operation
/// @details   This class splits a group of shapes by the other group of shapes.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <boolean/BoolBuilder.hpp>

namespace AMCAX
{
/// @brief The class of splitter operation
/// @details This class splitting a group of arbitrary shapes by the other group of arbitrary shapes.
///          The shapes can be split by the other shapes from the same group.
///          The tool shapes can be empty, then the result will be the same as general fuse operation.
class AMCAX_CLASS_API BoolBRepSplitter : public BoolBuilder
{
public:
	/// @brief Default constructor
	/// @details Do nothing
	AMCAX_API BoolBRepSplitter();

#ifndef DOXYGEN_SKIP

	explicit BoolBRepSplitter(const std::shared_ptr<BOAlgoPaveFiller>& PF);

#endif

	/// @brief Destructor
	AMCAX_API ~BoolBRepSplitter();

	/// @brief Set the tool shapes
	/// @param ls The tool shapes
	AMCAX_API void SetTools(const std::list<TopoShape>& ls);

	/// @brief Get the tool shapes
	/// @return The tool shapes
	AMCAX_API const std::list<TopoShape> Tools() const;

	/// @brief Perform the algorithm
	AMCAX_API void Build() override;

private:
	std::list<TopoShape> mTools;
};
} // namespace AMCAX
