/// @file      GeneralTransformationT.hpp
/// @brief     Class of general transformation
/// @details   Implementation of general affine transformation
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/Precision.hpp>
#include <common/TransformationT.hpp>

namespace AMCAX
{
/// @brief Class of general transformation
/// @tparam Scalar Underlying scalar type of transformation
/// @tparam DIM Dimension
template<typename Scalar, int DIM>
class GeneralTransformationT
{
public:
	/// @brief Default constructor
	/// @details The default transformation is the identity transformation
	constexpr GeneralTransformationT() noexcept
		: scale(Scalar{1}),
		  type(TransformationType::Identity)
	{
		matrix.SetIdentity();
	}

	/// @brief Construct from a transformation
	/// @param trans The transformation
	constexpr explicit GeneralTransformationT(const TransformationT<Scalar, DIM>& trans) noexcept
		: scale(trans.ScaleFactor()),
		  type(trans.Type()),
		  matrix(trans.HVectorialPart()),
		  location(trans.TranslationPart())
	{
	}

	/// @brief Construct from a matrix and a vector
	/// @param m The matrix
	/// @param v The vector
	constexpr GeneralTransformationT(const MatrixT<Scalar, DIM, DIM>& m, const CoordT<Scalar, DIM>& v) noexcept
		: scale(Scalar{0}),
		  type(TransformationType::Other),
		  matrix(m),
		  location(v)
	{
	}

	/// @brief Set the transformation as the affine transformation from an axis and a ratio
	/// @details Scaling along the plane perpendicular to the axis, scaling with respect to the axis
	/// @param axis The affine axis
	/// @param ratio The ratio
	constexpr void SetAffinity(const AxisT<Scalar, DIM>& axis, const Scalar& ratio) noexcept
	{
		type = TransformationType::Other;
		scale = Scalar{0};
		matrix.SetDot(axis.Direction().Coord());
		MatrixT<Scalar, DIM, DIM> identity;
		identity.SetIdentity();
		matrix = matrix * (Scalar{1} - ratio) + identity * ratio;
		location = axis.Location().Coord() - matrix * axis.Location().Coord();
	}

	/// @brief Set the transformation as the affine transformation from a frame and a ratio
	/// @details Scaling along z-axis of frame by a ratio, scaling with respect to xy-plane
	/// @param frame The affine frame
	/// @param ratio The ratio
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	constexpr void SetAffinity(const FrameT<Scalar, DIM>& frame, const Scalar& ratio) noexcept
	{
		type = TransformationType::Other;
		scale = Scalar{0};
		matrix.SetDot(frame.Direction().Coord());
		matrix *= (ratio - Scalar{1});
		location = -matrix * frame.Location().Coord();
		MatrixT<Scalar, DIM, DIM> identity;
		identity.SetIdentity();
		matrix += identity;
	}

	/// @brief Set the values at given indices
	/// @param i The row index
	/// @param j The column index
	/// @param value The value
	constexpr void SetValue(int i, int j, const Scalar& value) noexcept
	{
		assert(i >= 0 && i < DIM && j >= 0 && j <= DIM);
		if (j == DIM)
		{
			location[i] = value;
		}
		else
		{
			matrix(i, j) = value;
		}
		type = TransformationType::Other;
	}

	/// @brief Set the translation part of the transformation
	/// @param vec The translation vector
	constexpr void SetTranslationPart(const CoordT<Scalar, DIM>& vec) noexcept
	{
		location = vec;
		const bool isZero = (location.SquaredNorm() < std::numeric_limits<Scalar>::min());
		switch (type)
		{
		case TransformationType::Identity:
			if (!isZero)
			{
				type = TransformationType::Translation;
			}
			break;
		case TransformationType::Translation:
			if (isZero)
			{
				type = TransformationType::Identity;
			}
			break;
		case TransformationType::Rotation:
		case TransformationType::PointMirror:
		case TransformationType::AxisMirror:
		case TransformationType::FrameMirror:
		case TransformationType::Scale:
		case TransformationType::Compound:
			if (!isZero)
			{
				type = TransformationType::Compound;
			}
			break;
		default:
			break;
		}
	}

	/// @brief Set the transformation as a standard transformation
	/// @param tr The transformation
	constexpr void SetTransformation(const TransformationT<Scalar, DIM>& tr) noexcept
	{
		scale = tr.ScaleFactor();
		type = tr.Type();
		matrix = tr.HVectorialPart();
		location = tr.TranslationPart();
	}

	/// @brief Set the vectorial part of the transformation
	/// @param m The matrix
	constexpr void SetVectorialPart(const MatrixT<Scalar, DIM, DIM>& m) noexcept
	{
		matrix = m;
		scale = Scalar{0};
		type = TransformationType::Other;
	}

	/// @brief Is the transformation negative
	/// @return True if the determinant of matrix is negative
	[[nodiscard]] constexpr bool IsNegative() const noexcept
	{
		return matrix.Determinant() < Scalar{0};
	}

	/// @brief Is the transformation singular
	/// @return True if the matrix is singular
	[[nodiscard]] bool IsSingular() const noexcept
	{
		return matrix.IsSingular();
	}

	/// @brief Get the type of transformation
	/// @return The type of transformation
	[[nodiscard]] constexpr TransformationType Type() const noexcept
	{
		return type;
	}

	/// @brief Get the scale factor of the transformation
	/// @return The scale factor
	[[nodiscard]] constexpr Scalar ScaleFactor() const noexcept
	{
		return scale;
	}

	/// @brief Get the translation part of the transformation
	/// @return The translation part
	[[nodiscard]] constexpr const CoordT<Scalar, DIM>& TranslationPart() const noexcept
	{
		return location;
	}

	/// @brief Get the vectorial part of the transformation
	/// @return The vectorial part
	[[nodiscard]] constexpr const MatrixT<Scalar, DIM, DIM>& VectorialPart() const noexcept
	{
		return matrix;
	}

	/// @brief Get the matrix of linear homogeneous transformation over projective space
	/// @return The transformation matrix
	constexpr MatrixT<Scalar, DIM + 1, DIM + 1> HomogeneousMatrix() const noexcept
	{
		MatrixT<Scalar, DIM + 1, DIM + 1> m;
		if (type == TransformationType::Other)
		{
			for (int i = 0; i < DIM; i++)
			{
				for (int j = 0; j < DIM; j++)
				{
					m(i, j) = matrix(i, j);
				}
				m(i, DIM) = location[i];
			}
		}
		else
		{
			for (int i = 0; i < DIM; i++)
			{
				for (int j = 0; j < DIM; j++)
				{
					m(i, j) = matrix(i, j) * scale;
				}
				m(i, DIM) = location[i];
			}
		}
		m(DIM, DIM) = Scalar{1};
		return m;
	}

	/// @brief Get the value by index
	/// @param i The row index
	/// @param j The column index
	/// @return The value at index (i, j)
	[[nodiscard]] constexpr Scalar Value(int i, int j) const noexcept
	{
		assert(i >= 0 && i < DIM && j >= 0 && j <= DIM);
		return j < DIM ? (type == TransformationType::Other ? matrix(i, j) : scale * matrix(i, j)) : location[i];
	}

	/// @brief Invert the transformation
	/// @return The reference to self
	GeneralTransformationT& Invert()
	{
		if (type == TransformationType::Other)
		{
			matrix.Invert();
			location = -matrix * location;
		}
		else
		{
			TransformationT<Scalar, DIM> t = Transformation();
			t.Invert();
			SetTransformation(t);
		}
		return *this;
	}

	/// @brief Get the inverted transformation
	/// @return The inverted transformation
	[[nodiscard]] GeneralTransformationT Inverted() const
	{
		return GeneralTransformationT(*this).Invert();
	}

	/// @brief Transformation multiplication assignment
	/// @param other The other transformation
	/// @return The reference to self
	GeneralTransformationT& operator*=(const GeneralTransformationT<Scalar, DIM>& other)
	{
		if (type == TransformationType::Other || other.type == TransformationType::Other)
		{
			type = TransformationType::Other;
			location += matrix * other.location;
			matrix *= other.matrix;
		}
		else
		{
			TransformationT<Scalar, DIM> t = Transformation();
			t *= other.Transformation();
			SetTransformation(t);
		}
		return *this;
	}

	/// @brief Get the transformation multiplied by the other transformation
	/// @param other The other transformation
	/// @return The multiplied transformation
	[[nodiscard]] GeneralTransformationT operator*(const GeneralTransformationT<Scalar, DIM>& other) const
	{
		return GeneralTransformationT(*this) *= other;
	}

	/// @brief Transformation left multiplication assignment
	/// @param other The other transformation
	/// @return The reference to self
	GeneralTransformationT& LeftMultiply(const GeneralTransformationT<Scalar, DIM>& other)
	{
		if (type == TransformationType::Other || other.type == TransformationType::Other)
		{
			type = TransformationType::Other;
			location = other.matrix * location + other.location;
			matrix.LeftMultiply(other.matrix);
		}
		else
		{
			TransformationT<Scalar, DIM> t = Transformation();
			t.LeftMultiply(other.Transformation());
			SetTransformation(t);
		}
		return *this;
	}

	/// @brief Get the transformation left-multiplied by the other transformation
	/// @param other The other transformation
	/// @return The left-multiplied transformation
	[[nodiscard]] GeneralTransformationT LeftMultiplied(const GeneralTransformationT<Scalar, DIM>& other) const
	{
		return GeneralTransformationT(*this).LeftMultiply(other);
	}

	/// @brief Power the transformation
	/// @param power The exponential
	/// @return The reference to self
	GeneralTransformationT& Power(int power)
	{
		if (type == TransformationType::Other)
		{
			if (power == 0)
			{
				scale = Scalar{1};
				type = TransformationType::Identity;
				matrix.SetIdentity();
				location.fill(0.0);
			}
			else if (power == 1)
			{
			}
			else if (power == -1)
			{
				Invert();
			}
			else
			{
				if (power < 0)
				{
					Invert();
				}
				int Npower = power;
				if (Npower < 0)
				{
					Npower = -Npower;
				}
				Npower--;
				CoordT<Scalar, DIM> Temploc = location;
				MatrixT<Scalar, DIM, DIM> Tempmatrix(matrix);
				while (true)
				{
					if (Npower % 2)
					{
						location += matrix * Temploc;
						matrix *= Tempmatrix;
					}
					if (Npower == 1)
					{
						break;
					}
					Temploc += Tempmatrix * Temploc;
					Tempmatrix *= Tempmatrix;
					Npower /= 2;
				}
			}
		}
		else
		{
			TransformationT<Scalar, DIM> t = Transformation();
			t.Power(power);
			SetTransformation(t);
		}
		return *this;
	}

	/// @brief Get the power of tranformation
	/// @param power The exponential
	/// @return The power of transformation
	[[nodiscard]] GeneralTransformationT Powered(int power) const
	{
		return GeneralTransformationT(*this).Power(power);
	}

	/// @brief Transform a vector
	/// @param[in,out] coord The vector
	constexpr void Transform(CoordT<Scalar, DIM>& coord) const noexcept
	{
		coord = type == TransformationType::Other || scale == Scalar{1} ? matrix * coord + location : scale * (matrix * coord) + location;
	}

	/// @brief Cast to a standard transformation
	/// @return The standard transformation
	[[nodiscard]] TransformationT<Scalar, DIM> Transformation() const
	{
		Scalar tol = static_cast<Scalar>(Precision::Angular());
		Scalar tol2 = Scalar{2} * tol;
		Throw_Construction_Error_if(type == TransformationType::Other, "non-orthogonal");
		for (int i = 0; i < DIM; i++)
		{
			for (int j = 0; j < DIM; j++)
			{
				Throw_Construction_Error_if(std::fabs(matrix.Column(i).Dot(matrix.Column(j)) - (i == j ? 1.0 : 0.0)) > tol2, "non-orthogonal");
			}
		}
		TransformationT<Scalar, DIM> transformation;
		transformation.matrix = matrix;
		transformation.type = type;
		transformation.scale = scale;
		transformation.location = location;
		return transformation;
	}

	/// @brief Write the general transformation
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param tr The general transformation
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const GeneralTransformationT& tr)
	{
		os << tr.ScaleFactor() << ' ' << static_cast<std::underlying_type_t<TransformationType>>(tr.Type()) << '\n';
		for (int i = 0; i < DIM; i++)
		{
			os << tr.Value(i, 0);
			for (int j = 1; j < DIM + 1; j++)
			{
				os << ' ' << tr.Value(i, j);
			}
			os << '\n';
		}
		return os;
	}

private:
	/// @brief Scale factor
	Scalar scale;

	/// @brief Type of transformation
	TransformationType type;

	/// @brief Vectorial part
	MatrixT<Scalar, DIM, DIM> matrix;

	/// @brief Translation part
	CoordT<Scalar, DIM> location;
};

/// @brief 2D general transformation
using GeneralTransformation2 = GeneralTransformationT<double, 2>;

/// @brief 3D general transformation
using GeneralTransformation3 = GeneralTransformationT<double, 3>;

} // namespace AMCAX
