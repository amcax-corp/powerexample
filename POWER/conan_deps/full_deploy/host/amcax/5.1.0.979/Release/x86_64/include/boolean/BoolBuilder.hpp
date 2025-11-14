/// @file      BoolBuilder.hpp
/// @brief     The base class of general boolean operation
/// @details   The base class of general boolean operation, including API definition, option settings required by all kinds of boolean operations.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <boolean/BOAlgoMacros.hpp>
#include <common/Precision.hpp>
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
class BOAlgoBuilder;
class BOAlgoOptions;
class BOAlgoPaveFiller;
class TopoToolHistory;

/// @brief The base class of general boolean operation
class AMCAX_CLASS_API BoolBuilder : public MakeShape
{
public:
	/// @brief Default constructor
	/// @details Do nothing.
	AMCAX_API BoolBuilder();

#ifndef DOXYGEN_SKIP

	explicit BoolBuilder(const std::shared_ptr<BOAlgoPaveFiller>& PF);

#endif

	/// @brief Set the shapes to be processed
	/// @param listargs The argument shapes
	AMCAX_API void SetArguments(const std::list<TopoShape>& listargs);

	/// @brief Get all the shape to be processed
	/// @return The argument shapes
	AMCAX_API const std::list<TopoShape>& Arguments() const noexcept;

	/// @brief Set the flag that defines whether the input arguments are not allowed to be modified
	/// @details If the non-destructive mode is enabled, the input shape will not be modified. The default value is false
	/// @param flag The non-destructive mode flag
	AMCAX_API void SetNonDestructive(bool flag) noexcept;

	/// @brief Get the flag that defines whether the input arguments are not allowed to be modified
	/// @return The flag of non-destructive mode
	AMCAX_API bool IsNonDestructive() const noexcept;

	/// @brief Set the type of gluing algorithm
	/// @details This option is used to accelerate the compuation of intersetions on the special cases, when some sub-shapes are coinciding.
	/// @param gType The type of gluing algorithm
	AMCAX_API void SetGlue(BOAlgoGlueType gType) noexcept;

	/// @brief Get the type of gluing algorithm
	/// @return The type of gluing algorithm
	AMCAX_API BOAlgoGlueType Glue() const noexcept;

	/// @brief Enable or disable the check of inverted solids
	/// @details The default value is true, i.e. the check is performed.
	/// @param isCheck The flag
	AMCAX_API void SetCheckInverted(bool isCheck) noexcept;

	/// @brief Get the flag defining whether the check of inverted solids should be performed or not
	/// @return The status whether the algorithm performs the check of inverted solids
	AMCAX_API bool IsCheckInverted() const noexcept;

	/// @brief Perform the algorithm
	AMCAX_API void Build() override;

	/// @brief Simplify the boolean result, remove redundant edges and faces
	/// @param isUnfiyEdges Set whether unify edges
	/// @param isUnifyFaces Set whether unify faces
	/// @param angularTol The angular tolerance for checking parallel
	AMCAX_API void SimplifyResult(bool isUnfiyEdges = true, bool isUnifyFaces = true, double angularTol = Precision::Angular());

	/// @brief Compute the shape modified from a given shape s
	/// @details If any, the list will contain only those splits of the given shape, contained in the result.
	/// @param s The given shape
	/// @return The list of modified shapes
	AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s) override;

	/// @brief Compute the shape generated from a given shape s
	/// @details Only edges and faces could have generated shapes, i.e. edges generate new vertices, and faces generate new edges and vertices.
	/// @param s The given shape
	/// @return The list of generated shapes
	AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s) override;

	/// @brief Check if the shape s has been deleted during the operation
	/// @details The general boolean operation should not have deleted shapes, but the derived operations can have.
	/// @param s The given shape
	/// @return Whether the shape is deleted
	AMCAX_API bool IsDeleted(const TopoShape& s) override;

	/// @brief Check if any of the input shapes has been modefied.
	/// @return Whether there has any modified object
	AMCAX_API virtual bool HasModified() const;

	/// @brief Check if there are shape been genereted during the operation.
	/// @return Whether there are shapes been generated.
	AMCAX_API virtual bool HasGenerated() const;

	/// @brief Check if there are any shapes been deleted.
	/// @details The general boolean operation should not have deleted shapes, but the derived operations can have.
	/// @return Whether there are any shapes been deleted.
	AMCAX_API virtual bool HasDeleted() const;

	/// @brief Set the flag that enable or disable the collection of the history of shape modifications during the opreation
	/// @param fillFlag The flag that enables the history collection
	AMCAX_API void SetToFillHistory(bool fillFlag) noexcept;

	/// @brief Get the flag that enable or disable the history collection
	/// @return Whether the history collection is enabled
	AMCAX_API bool HasHistory() const noexcept;

#ifndef DOXYGEN_SKIP

	const std::list<TopoShape>& SectionEdges();
	const std::shared_ptr<BOAlgoPaveFiller>& DSFiller() const noexcept;
	const std::shared_ptr<BOAlgoBuilder>& Builder() const noexcept;
	std::shared_ptr<TopoToolHistory> History() const noexcept;

#endif

protected:
#ifndef DOXYGEN_SKIP

	virtual void SetAttributes() noexcept;
	void IntersectShapes(const std::list<TopoShape>& args);
	void BuildResult();
	void Clear() noexcept;
	void AddError(const std::string& s);
	void AddWarning(const std::string& s);
	bool HasError() const noexcept;
	void SetRunParallel(bool isPara) noexcept;
	void SetFuzzyValue(double fuzzy) noexcept;
	void SetUseOBB(bool obb) noexcept;
	double GetFuzzyValue() const noexcept;
	bool GetRunParallel() const noexcept;
	bool GetUseOBB() const noexcept;

	/// @brief Input shapes
	std::list<TopoShape> arguments;

	BOAlgoGlueType glueType = BOAlgoGlueType::GlueOff;

	/// @brief Non-destructive mode management
	bool isNonDestructiveMode = false;

	/// @brief Check for inverted solids management
	bool isCheckInverted = true;

	/// @brief Controls the history collection
	bool isFillHistory = true;

	/// @brief Flag to control whether the intersection of arguments should be performed or not
	bool isIntersectionNeeded = true;

	std::shared_ptr<BOAlgoPaveFiller> mDSFiller;

	std::shared_ptr<BOAlgoBuilder> mBuilder;

	/// @brief General History tool, containing all History of shapes modifications during the operation
	std::shared_ptr<TopoToolHistory> mHistory;

	/// @brief History of result shape simplification
	std::shared_ptr<TopoToolHistory> mSimplifierHistory;

	std::shared_ptr<BOAlgoOptions> mOption;

#endif
};
} // namespace AMCAX
