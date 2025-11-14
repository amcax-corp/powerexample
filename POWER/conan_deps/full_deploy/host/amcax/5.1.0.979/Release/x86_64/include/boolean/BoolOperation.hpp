/// @file      BoolOperation.hpp
/// @brief     The base class of boolean operation
/// @details   The base class of boolean operation, containing type of boolean operation and tool shapes.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <boolean/BoolBuilder.hpp>

namespace AMCAX
{
/// @brief The base class of boolean operation
/// @details In the boolean operation, some of the input shapes are divided into objects and tools.
class AMCAX_CLASS_API BoolOperation : public BoolBuilder
{
public:
	/// @brief Default constructor
	/// @details Do nothing
	AMCAX_API BoolOperation();

	/// @brief Destructor
	AMCAX_API ~BoolOperation() noexcept;

	/// @brief Set the tool shapes
	/// @param tlist The list of tool shapes
	AMCAX_API void SetTools(const std::list<TopoShape>& tlist);

	/// @brief Get the tool shapes
	/// @return The list of tool shapes
	AMCAX_API const std::list<TopoShape>& Tools() const noexcept;

	/// @brief Set the type of boolean operation
	/// @param bop The operation type
	AMCAX_API void SetOperation(const BOAlgoOperation& bop) noexcept;

	/// @brief Get the type of boolean operation
	/// @return The operation type
	AMCAX_API BOAlgoOperation GetOperation() const noexcept;

	/// @brief Perform the boolean operation
	AMCAX_API void Build() override;

protected:
#ifndef DOXYGEN_SKIP

	void Build2D();

	explicit BoolOperation(const std::shared_ptr<BOAlgoPaveFiller>& PF);
	BoolOperation(const TopoShape& S1, const TopoShape& S2, const BOAlgoOperation& operation);
	BoolOperation(const TopoShape& S1, const TopoShape& S2, const std::shared_ptr<BOAlgoPaveFiller>& PF, const BOAlgoOperation& operation);

	std::list<TopoShape> tools;
	BOAlgoOperation mOperation = BOAlgoOperation::Unknown;

#endif
};
} // namespace AMCAX
