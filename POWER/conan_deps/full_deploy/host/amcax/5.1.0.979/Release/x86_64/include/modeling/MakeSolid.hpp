/// @file      MakeSolid.hpp
/// @brief     Class of making a solid
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <modeling/MakeShape.hpp>
#include <topology/TopoSolid.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeSolidImpl;
class TopoCompSolid;
class TopoShell;
#endif

/// @brief Class of making a solid
class AMCAX_CLASS_API MakeSolid : public MakeShape
{
public:
	/// @brief Default constructor
	AMCAX_API MakeSolid();

	/// @brief Construct from a composite solid
	/// @param s The composite solid
	AMCAX_API explicit MakeSolid(const TopoCompSolid& s);

	/// @brief Construct from a shell
	/// @param s The shell
	AMCAX_API explicit MakeSolid(const TopoShell& s);

	/// @brief Construct from two shells
	/// @param s1 The first shell
	/// @param s2 The second shell
	AMCAX_API MakeSolid(const TopoShell& s1, const TopoShell& s2);

	/// @brief Construct from three shells
	/// @param s1 The first shell
	/// @param s2 The second shell
	/// @param s3 The third shell
	AMCAX_API MakeSolid(const TopoShell& s1, const TopoShell& s2, const TopoShell& s3);

	/// @brief Construct from a solid
	/// @param s The solid
	AMCAX_API explicit MakeSolid(const TopoSolid& s);

	/// @brief Construct from a solid and a shell, the shell will be added to the solid
	/// @param solid The solid
	/// @param shell The shell
	AMCAX_API MakeSolid(const TopoSolid& solid, const TopoShell& shell);

	/// @brief Add a shell to the solid
	/// @param s The shell
	AMCAX_API void Add(const TopoShell& s);

	[[nodiscard]] AMCAX_API bool IsDone() const noexcept override;

	/// @brief Get the constructed solid
	/// @return The constructed solid
	[[nodiscard]] AMCAX_API const TopoSolid& Solid();

	/// @brief Get the constructed solid
	/// @return The constructed solid
	[[nodiscard]] AMCAX_API operator TopoSolid();

	[[nodiscard]] AMCAX_API bool IsDeleted(const TopoShape& s) noexcept override;

private:
	std::shared_ptr<MakeSolidImpl> makeSolid;
};
} // namespace AMCAX
