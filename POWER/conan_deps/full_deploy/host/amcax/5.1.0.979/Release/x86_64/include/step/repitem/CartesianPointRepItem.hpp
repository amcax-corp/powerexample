/// @file       CartesianPointRepItem.hpp
/// @brief      Class for representing a Cartesian Point Representation Items.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>
#include <common/PointT.hpp>

#include <variant>

#include <step/repitem/AbstractRepItem.hpp>

namespace AMCAX::STEP
{
/// @brief Class for representing a Cartesian Point Representation Items.
class CartesianPointRepItem : public AbstractRepItem
{
public:
	/// @brief Default constructor.
	AMCAX_API CartesianPointRepItem();

	/// @brief Copy constructor.
	/// @param other The other CartesianPointRepItem to copy from.
	AMCAX_API CartesianPointRepItem(const CartesianPointRepItem& other);

	/// @brief Constructor.
	/// @param name The name of the cartesian point representation item.
	/// @param point The value of the cartesian point representation item.
	AMCAX_API CartesianPointRepItem(const std::string& name, const AMCAX::Point3& point);

	/// @brief Move constructor.
	/// @param other The other CartesianPointRepItem to move from.
	AMCAX_API CartesianPointRepItem(CartesianPointRepItem&& other) noexcept;

	/// @brief Copy assignment operator.
	/// @param other The other CartesianPointRepItem to copy from.
	/// @return The CartesianPointRepItem object.
	AMCAX_API CartesianPointRepItem& operator=(const CartesianPointRepItem& other);

	/// @brief Move assignment operator.
	/// @param other The other CartesianPointRepItem to move from.
	///	@return The CartesianPointRepItem object.
	AMCAX_API CartesianPointRepItem& operator=(CartesianPointRepItem&& other) noexcept;

	/// @brief Destructor.
	AMCAX_API ~CartesianPointRepItem() override;

	/// @brief Set the name of the cartesian point representation item.
	/// @param name The name of the cartesian point representation item.
	/// @return The CartesianPointRepItem object.
	AMCAX_API CartesianPointRepItem& SetName(const std::string& name);

	/// @brief Get an immutable reference to the point of the cartesian point representation item.
	/// @return An immutable reference to the point of the cartesian point representation item.
	AMCAX_API const AMCAX::Point3& GetPoint() const;

	/// @brief Set the value of the cartesian point representation item.
	/// @param point The value of the cartesian point representation item.
	/// @return The CartesianPointRepItem object.
	AMCAX_API CartesianPointRepItem& SetPoint(const AMCAX::Point3& point);

	/// @brief If the CartesicanPointRepitem same as the other CartesicanPointRepitem.
	/// @param other The other CartesicanPointRepitem to compare with.
	/// @return True if the CartesicanPointRepitem is the same as the other CartesicanPointRepitem, otherwise false.
	AMCAX_API bool operator==(const CartesianPointRepItem& other) const;

	/// @brief If the CartesicanPointRepitem different from the other CartesicanPointRepitem.
	/// @param other The other CartesicanPointRepitem to compare with.
	/// @return True if the CartesicanPointRepitem is different from the other CartesicanPointRepitem, otherwise false.
	AMCAX_API bool operator!=(const CartesianPointRepItem& other) const;

	/// @brief If the CartesicanPointRepitem less than the other CartesicanPointRepitem.
	/// @param other The other CartesicanPointRepitem to compare with.
	/// @return True if the CartesicanPointRepitem is less than the other CartesicanPointRepitem, otherwise false.
	AMCAX_API bool operator<(const CartesianPointRepItem& other) const;

	/// @brief If the CartesicanPointRepitem greater than the other CartesicanPointRepitem.
	/// @param other The other CartesicanPointRepitem to compare with.
	/// @return True if the CartesicanPointRepitem is greater than the other CartesicanPointRepitem, otherwise false.
	AMCAX_API bool operator>(const CartesianPointRepItem& other) const;

	/// @brief If the CartesicanPointRepitem less than or equal to the other CartesicanPointRepitem.
	/// @param other The other CartesicanPointRepitem to compare with.
	/// @return True if the CartesicanPointRepitem is less than or equal to the other CartesicanPointRepitem, otherwise false.
	AMCAX_API bool operator<=(const CartesianPointRepItem& other) const;

	/// @brief If the CartesicanPointRepitem greater than or equal to the other CartesicanPointRepitem.
	/// @param other The other CartesicanPointRepitem to compare with.
	/// @return True if the CartesicanPointRepitem is greater than or equal to the other CartesicanPointRepitem, otherwise false.
	AMCAX_API bool operator>=(const CartesianPointRepItem& other) const;

	/// @brief Deep Copy.
	/// @return The pointer of the duplicated object.
	virtual AMCAX_API std::shared_ptr<AbstractRepItem> Copy() const override;

private:
	AMCAX::Point3 _Point;
};
} // namespace AMCAX::STEP
