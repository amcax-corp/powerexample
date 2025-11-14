/// @file      MakeRevol.hpp
/// @brief     Class of making a revolved shape
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/AxisT.hpp>
#include <modeling/MakeSweep.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeRevolImpl;
class TopoToolHistory;
#endif

/// @brief Class of making a revolved shape
/// @details If the edges of the input shape intersect at a non-endpoint but not coincide with the rotation axis, a construction error will be thrown.
/// Note: This class may generate physically invalid solids.
class AMCAX_CLASS_API MakeRevol : public MakeSweep
{
public:
	/// @brief Construct from a base shape, a rotation axis and a rotation angle
	/// @param s The base shape
	/// @param a The rotation axis
	/// @param d The rotation angle
	/// @param copy Whether copy the base shape
	AMCAX_API MakeRevol(const TopoShape& s, const Axis3& a, double d, bool copy = false);

	/// @brief Construct from a base shape and a rotation axis
	/// @param s The base shape
	/// @param a The rotation axis
	/// @param copy Whether copy the base shape
	AMCAX_API MakeRevol(const TopoShape& s, const Axis3& a, bool copy = false);

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] const MakeRevolImpl& Revol() const noexcept;

#endif

	AMCAX_API void Build() override;
	[[nodiscard]] AMCAX_API TopoShape FirstShape() override;
	[[nodiscard]] AMCAX_API TopoShape LastShape() override;
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s) override;
	[[nodiscard]] AMCAX_API bool IsDeleted(const TopoShape& s) override;

	/// @brief Get the first shape of a sub-shape of the generating shape
	/// @param shape The sub-shape
	/// @return The first shape
	[[nodiscard]] AMCAX_API TopoShape FirstShape(const TopoShape& shape);

	/// @brief Get the last shape of a sub-shape of the generating shape
	/// @param shape The sub-shape
	/// @return The last shape
	[[nodiscard]] AMCAX_API TopoShape LastShape(const TopoShape& shape);

	/// @brief Is there any degenerated edge in the result
	/// @return True if there is some degenerated edge
	[[nodiscard]] AMCAX_API bool HasDegenerated() const noexcept;

	/// @brief Get the list of degenerated edges
	/// @return The list of degenerated edges
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Degenerated() const noexcept;

protected:
	/// @brief Check the validity of a shape with the rotation axis
	/// @param shape The shape
	/// @param a The rotation axis
	/// @return True if the input is valid
	[[nodiscard]] bool CheckValidity(const TopoShape& shape, const Axis3& a);

private:
	std::shared_ptr<MakeRevolImpl> revol;
	std::list<TopoShape> degenerated;
	std::shared_ptr<TopoToolHistory> history;
	bool isBuild = false;
};
} // namespace AMCAX
