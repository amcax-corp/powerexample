/// @file      MakePrism.hpp
/// @brief     Class of making a prism
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/DirectionT.hpp>
#include <common/VectorT.hpp>
#include <modeling/MakeSweep.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeSweepPrismImpl;
#endif

/// @brief Class of making a prism or an extrusion shape
class AMCAX_CLASS_API MakePrism : public MakeSweep
{
public:
	/// @brief Construct from a base shape and an extrusion vector
	/// @param s The base shape
	/// @param v The extrusion vector
	/// @param copy Whether copy a base shape
	/// @param canonize Whether canonized to elementary surfaces
	AMCAX_API MakePrism(const TopoShape& s, const Vector3& v, bool copy = false, bool canonize = true);

	/// @brief Construct from a base shape and an extrusion direction
	/// @param s The base shape
	/// @param d The extrusion direction
	/// @param inf If true, the shape is infinite; otherwise, the shape is semi-infinite in the direction
	/// @param copy Whether copy a base shape
	/// @param canonize Whether canonized to elementary surfaces
	AMCAX_API MakePrism(const TopoShape& s, const Direction3& d, bool inf = true, bool copy = false, bool canonize = true);

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] const MakeSweepPrismImpl& Prism() const noexcept;

#endif

	AMCAX_API void Build() override;
	[[nodiscard]] AMCAX_API TopoShape FirstShape() override;
	[[nodiscard]] AMCAX_API TopoShape LastShape() override;
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s) override;
	[[nodiscard]] AMCAX_API bool IsDeleted(const TopoShape& s) override;

	/// @brief Get the bottom shape of a sub-shape of generating shape
	/// @param s The sub-shape
	/// @return The bottom shape
	[[nodiscard]] AMCAX_API TopoShape FirstShape(const TopoShape& s);

	/// @brief Get the top shape of a sub-shape of generating shape
	/// @param s The sub-shape
	/// @return The top shape
	[[nodiscard]] AMCAX_API TopoShape LastShape(const TopoShape& s);

private:
	[[nodiscard]] static const TopoShape& Check(const TopoShape& s);
	std::shared_ptr<MakeSweepPrismImpl> prism;
};
} // namespace AMCAX
