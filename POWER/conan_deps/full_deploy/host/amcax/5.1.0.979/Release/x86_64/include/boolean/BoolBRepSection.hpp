/// @file      BoolBRepSection.hpp
/// @brief     The class of section operation
/// @details   This class computes the section shape of two shapes, i.e. the intersection edges and vertices of two shapes.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <boolean/BoolOperation.hpp>

namespace AMCAX
{
class Plane;
class Geom3Surface;

/// @brief The class of section operation
/// @details This class computes the section shape of two shapes, i.e. the intersection edges and vertices of two shapes.
class AMCAX_CLASS_API BoolBRepSection : public BoolOperation
{
public:
	/// @brief Default constructor
	/// @details Only set the type of boolean operation to section, and you need to execute Build() to perform the Boolean operation.
	AMCAX_API BoolBRepSection();

	/// @brief Compute the section of two shapes
	/// @param s1 The argument shape
	/// @param s2 The tool shape
	/// @param perfomNow If true, the operation is performed immediately; if false, the Build() function has to be called manually
	AMCAX_API BoolBRepSection(const TopoShape& s1, const TopoShape& s2, bool perfomNow = true);

#ifndef DOXYGEN_SKIP

	explicit BoolBRepSection(const std::shared_ptr<BOAlgoPaveFiller>& PF);

	BoolBRepSection(const TopoShape& S1, const TopoShape& S2, const std::shared_ptr<BOAlgoPaveFiller>& PF, bool PerfomNow = true);

#endif

	/// @brief Special case: compute the section of a shape and an infinite plane
	/// @param s1 The argument shape
	/// @param p1 The tool plane
	/// @param perfomNow If true, the operation is performed immediately; if false, the Build() function has to be called manually
	AMCAX_API BoolBRepSection(const TopoShape& s1, const Plane& p1, bool perfomNow = true);

	/// @brief Special case: compute the section of a shape and a surface
	/// @param s1 The argument shape
	/// @param surface The tool surface
	/// @param perfomNow If true, the operation is performed immediately; if false, the Build() function has to be called manually
	AMCAX_API BoolBRepSection(const TopoShape& s1, const std::shared_ptr<Geom3Surface>& surface, bool perfomNow = true);

	/// @brief Special case: compute the section of a surface and a shape
	/// @param surface The argument surface
	/// @param s2 The tool shape
	/// @param perfomNow If true, the operation is performed immediately; if false, the Build() function has to be called manually
	AMCAX_API BoolBRepSection(const std::shared_ptr<Geom3Surface>& surface, const TopoShape& s2, bool perfomNow = true);

	/// @brief Special case: compute the section of two surfaces
	/// @param s1 The argument surface
	/// @param s2 The tool surface
	/// @param perfomNow If true, the operation is performed immediately; if false, the Build() function has to be called manually
	AMCAX_API BoolBRepSection(const std::shared_ptr<Geom3Surface>& s1, const std::shared_ptr<Geom3Surface>& s2, bool perfomNow = true);

	/// @brief Destructor
	AMCAX_API ~BoolBRepSection();

	/// @brief Set the argument as a shape
	/// @param s The argument shape
	AMCAX_API void Init1(const TopoShape& s);

	/// @brief Set the argument as a plane
	/// @param p1ane The argument plane
	AMCAX_API void Init1(const Plane& p1ane);

	/// @brief Set the argument as a surface
	/// @param surface The argument surface
	AMCAX_API void Init1(const std::shared_ptr<Geom3Surface>& surface);

	/// @brief Set the tool as a shape
	/// @param s The tool shape
	AMCAX_API void Init2(const TopoShape& s);

	/// @brief Set the tool as a plane
	/// @param p1ane The tool plane
	AMCAX_API void Init2(const Plane& p1ane);

	/// @brief Set the tool as a surface
	/// @param surface The tool surface
	AMCAX_API void Init2(const std::shared_ptr<Geom3Surface>& surface);

	/// @brief Set whether the approximation is done in the boolean algorithm, the default value is false
	/// @param b The approximation flag
	AMCAX_API void Approximation(bool b) noexcept;

	/// @brief Set whether the pcurve on the argument is performed, the default value is false
	/// @param b The pcurve flag
	AMCAX_API void ComputePCurveOn1(bool b) noexcept;

	/// @brief Set whether the pcurve on the tool is performed, the default value is false
	/// @param b The pcurve flag
	AMCAX_API void ComputePCurveOn2(bool b) noexcept;

	/// @brief Perform the algorithm
	AMCAX_API void Build() override;

protected:
#ifndef DOXYGEN_SKIP

	void Init(bool PerfromNow);

	void SetAttributes() noexcept override;

#endif

private:
	bool isApprox;
	bool isComputePCurve1;
	bool isComputePCurve2;
};
} // namespace AMCAX
