/// @file      Sewing.hpp
/// @brief     Class of sewing shape
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class SewingImpl;
class TopoToolHistory;
#endif

/// @brief Class of sewing shape
class AMCAX_CLASS_API Sewing : public MakeShape
{
public:
	/// @brief Construct from a tolerance value for sewing shapes
	/// @param tol Tolerance
	AMCAX_API explicit Sewing(double tol = 1e-6);

	/// @brief Add a shape to be sewed
	/// @param s The shape to be sewed
	AMCAX_API void Add(const TopoShape& s);

	AMCAX_API void Build() override;
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s) override;
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s) override;
	[[nodiscard]] AMCAX_API bool IsDeleted(const TopoShape& s) override;

private:
	std::shared_ptr<SewingImpl> sewing;
	std::shared_ptr<TopoToolHistory> history;
};
} // namespace AMCAX
