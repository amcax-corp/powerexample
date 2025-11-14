/// @file      BoundingRange.hpp
/// @brief     Class of 1D bounding range
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>

#include <common/Macros.hpp>

namespace AMCAX
{
/// @brief Class of 1D bounding range
class BoundingRange
{
public:
	/// @brief Default constructor
	BoundingRange() noexcept = default;

	/// @brief Construct from minimal and maximal values
	/// @details If minimal value is greater than the maximal value, throw a construction error
	/// @param minv The minimal value
	/// @param maxv The maximal value
	AMCAX_API BoundingRange(double minv, double maxv);

	/// @brief Compute the common range with the other bounding range
	/// @param other The other bounding range
	AMCAX_API void Common(const BoundingRange& other) & noexcept;

	/// @brief Compute the union range with the other bounding range
	/// @param other The other bounding range
	/// @return True if two ranges are not void and have common part
	AMCAX_API bool Union(const BoundingRange& other) noexcept;

	/// @brief Split the range by a value with a period
	/// @details If period != 0.0 then at least one boundary of new ranges will be equal to value + k * period
	/// @param[in] value The split value
	/// @param[out] rangeList The resulting bounding ranges
	/// @param[in] period The period of value to split
	AMCAX_API void Split(double value, std::list<BoundingRange>& rangeList, double period = 0.0) const;

	/// @brief Is the value intersected with the bounding range
	/// @details Checks if the bounding range intersects values like value + k * period, where k is an integer number.
	/// @param value The test value
	/// @param period The period to be added to the value
	/// @return 0 - if the bounding range does not intersect the value + k * period.
	///         1 - if the bounding range intersects value + k * period.
	///         2 - if the first or/and last are equal to value + k * period.
	[[nodiscard]] AMCAX_API int IsIntersected(double value, double period = 0.0) const noexcept;

	/// @brief Extend the range by adding a value to the range
	/// @param parameter The parameter value
	AMCAX_API void Add(double parameter) & noexcept;

	/// @brief Extend the range by adding another bounding range
	/// @param other The other bounding range
	AMCAX_API void Add(const BoundingRange& other) & noexcept;

	/// @brief Get the minimal value of the bounding range
	/// @param[out] par The minimal value
	/// @return True if the bounding range is not void
	[[nodiscard]] AMCAX_API bool GetMin(double& par) const noexcept;

	/// @brief Get the maximal value of the bounding range
	/// @param[out] par The maximal value
	/// @return True if the bounding range is not void
	[[nodiscard]] AMCAX_API bool GetMax(double& par) const noexcept;

	/// @brief Get the bound values of the bounding range
	/// @param[out] first The minimal value
	/// @param[out] last The maximal value
	/// @return True if the bounding range is not void
	AMCAX_API bool GetBounds(double& first, double& last) const noexcept;

	/// @brief Get the intermediate point of the bounding range
	/// @param[in] lambda A relative length of the intermediate point, in [0, 1]
	/// @param[out] parameter The result intermediate value
	/// @return True if the bounding range is not void
	AMCAX_API bool GetIntermediatePoint(double lambda, double& parameter) const noexcept;

	/// @brief Get the length of the bounding range range
	/// @return The length of bounding range
	[[nodiscard]] AMCAX_API double Delta() const noexcept;

	/// @brief Is the bounding range void
	/// @return True if the bounding range is void
	[[nodiscard]] AMCAX_API bool IsVoid() const noexcept;

	/// @brief Set the bounding range to be void
	AMCAX_API void SetVoid() & noexcept;

	/// @brief Enlarge the bounding range by a given value
	/// @param delta The offset value
	AMCAX_API void Enlarge(double delta) & noexcept;

	/// @brief Get the shifted bounding range by a given value
	/// @param value The shift value
	/// @return The shifted bounding range
	[[nodiscard]] AMCAX_API BoundingRange Shifted(double value) const noexcept;

	/// @brief Shift the bounding range by a given value
	/// @param value The shift value
	AMCAX_API void Shift(double value) & noexcept;

	/// @brief Trim the bounding range by a new lower bound
	/// @param valueLower The lower bound
	AMCAX_API void TrimFrom(double valueLower) & noexcept;

	/// @brief Trim the bounding range by a new upper bound
	/// @param valueUpper The upper bound
	AMCAX_API void TrimTo(double valueUpper) & noexcept;

	/// @brief Is the value is out of the bounding range
	/// @param value The test value
	/// @return True if the value is out of the bounding range
	[[nodiscard]] AMCAX_API bool IsOut(double value) const noexcept;

	/// @brief Is another bounding range is out of the bounding range
	/// @param other The other bounding range
	/// @return True if the input bounding range is out of the bounding range
	[[nodiscard]] AMCAX_API bool IsOut(const BoundingRange& other) const noexcept;

	/// @brief Are two bounding ranges equal
	/// @param other The other bounding range
	/// @return True if the two bounding ranges are equal
	[[nodiscard]] AMCAX_API bool operator==(const BoundingRange& other) const noexcept;

private:
	double first = 0.0;
	double last = -1.0;
};
} // namespace AMCAX
