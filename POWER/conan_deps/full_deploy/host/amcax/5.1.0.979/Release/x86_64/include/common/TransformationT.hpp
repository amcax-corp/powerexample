/// @file      TransformationT.hpp
/// @brief     Class of transformation
/// @details   Implementation of affine transformation
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/QuaternionT.hpp>
#include <common/TransformationType.hpp>

namespace AMCAX
{
template<typename Scalar, int DIM>
class AxisT;
template<typename Scalar, int DIM>
class FrameT;
template<typename Scalar, int DIM>
class PointT;
template<typename Scalar, int DIM>
class VectorT;

/// @brief Class of transformation
/// @tparam Scalar Underlying scalar type of transformation
/// @tparam DIM Dimension
template<typename Scalar, int DIM>
class TransformationT
{
public:
	/// @brief Default constructor
	/// @details The default transformation is the identity transformation
	constexpr TransformationT() noexcept
		: scale(1.0),
		  type(TransformationType::Identity),
		  matrix(Scalar{1})
	{
	}

	/// @brief Construct from the other transformation
	/// @details If the other transformaiton is in higher dimension, the information in higher dimension will be truncated.
	/// @tparam OtherScalar The scalar type of the other transformation
	/// @tparam OtherDIM The dimension of the other transformation
	/// @param trans The other transformation
	template<typename OtherScalar, int OtherDIM>
	constexpr explicit TransformationT(const TransformationT<OtherScalar, OtherDIM>& trans) noexcept
		: scale(trans.ScaleFactor()),
		  type(trans.Type())
	{
		const auto& m = trans.HVectorialPart();
		constexpr int ADIM = DIM < OtherDIM ? DIM : OtherDIM;
		for (int i = 0; i < ADIM; i++)
		{
			for (int j = 0; j < ADIM; j++)
			{
				matrix(i, j) = static_cast<Scalar>(m(i, j));
			}
			location[i] = trans.TranslationPart()[i];
		}
		if constexpr (OtherDIM < DIM)
		{
			for (int i = OtherDIM; i < DIM; i++)
			{
				matrix(i, i) = Scalar{1};
			}
		}
		if (type == TransformationType::AxisMirror)
		{
			if constexpr (DIM == 3)
			{
				if (scale == Scalar{-1})
				{
					scale = Scalar{1};
					matrix *= Scalar{-1};
				}
			}
			else if constexpr (DIM == 2)
			{
				if (scale == Scalar{1})
				{
					scale = Scalar{-1};
					matrix *= Scalar{1};
				}
			}
		}
	}

	/// @brief Set the transformation as mirroring by point
	/// @tparam OtherScalar The scalar type of the mirror point
	/// @param point The mirror point
	template<typename OtherScalar>
	constexpr void SetMirror(const PointT<OtherScalar, DIM>& point) noexcept
	{
		type = TransformationType::PointMirror;
		scale = Scalar{-1};
		location = point.Coord() * OtherScalar{2};
		matrix.SetIdentity();
	}

	/// @brief Set the transformation as mirroring by axis
	/// @tparam OtherScalar The scalar type of the mirror axis
	/// @param axis The mirror axis
	template<typename OtherScalar>
	constexpr void SetMirror(const AxisT<OtherScalar, DIM>& axis) noexcept
	{
		type = TransformationType::AxisMirror;
		scale = Scalar{1};
		matrix.SetDot(axis.Direction().Coord());
		matrix *= Scalar{-2};
		for (int i = 0; i < DIM; i++)
		{
			matrix(i, i) += Scalar{1};
		}
		location = matrix * axis.Location().Coord() + axis.Location().Coord();
		matrix *= Scalar{-1};
	}

	/// @brief Set the transformation as mirroring by frame, i.e. the hyperplane orthogonal to the main direction of the frame
	/// @tparam OtherScalar The scalar type of the mirror frame
	/// @param frame The mirror frame
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	constexpr void SetMirror(const FrameT<OtherScalar, DIM>& frame) noexcept
	{
		type = TransformationType::FrameMirror;
		scale = Scalar{-1};
		matrix.SetDot(frame.Direction().Coord());
		matrix *= Scalar{2};
		for (int i = 0; i < DIM; i++)
		{
			matrix(i, i) -= Scalar{1};
		}
		location = matrix * frame.Location().Coord() + frame.Location().Coord();
	}

	/// @brief Set the transformation as rotation around a point with an angle in 2D
	/// @tparam OtherScalar The scalar type of the rotation center point
	/// @tparam OtherScalar2 The type of teh rotation angle
	/// @param point The rotation center point
	/// @param angle The rotation angle
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	void SetRotation(const PointT<OtherScalar, DIM>& point, const OtherScalar2& angle) noexcept
	{
		type = TransformationType::Rotation;
		scale = Scalar{1};
		matrix.SetRotation(angle);
		location = point.Coord() - matrix * point.Coord();
	}

	/// @brief Set the transformation as rotation around an axis with an angle in 3D
	/// @tparam OtherScalar The scalar type of the rotation axis
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param axis The rotaion axis
	/// @param angle The rotation angle
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	void SetRotation(const AxisT<OtherScalar, DIM>& axis, const OtherScalar2& angle) noexcept
	{
		type = TransformationType::Rotation;
		scale = Scalar{1};
		matrix.SetRotation(axis.Direction().Coord(), angle);
		location = axis.Location().Coord() - matrix * axis.Location().Coord();
	}

	/// @brief Set the transformation as the rotation from a quaternion in 3D
	/// @tparam OtherScalar The scalar type of the quaternion
	/// @param q The quaternion
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	constexpr void SetRotation(const QuaternionT<OtherScalar>& q) noexcept
	{
		type = TransformationType::Rotation;
		scale = Scalar{1};
		location.SetCoord(Scalar{0}, Scalar{0}, Scalar{0});
		matrix = q.GetMatrix();
	}

	/// @brief Set the rotation part of the transformation from a quaternion in 3D
	/// @tparam OtherScalar The scalar type of the quaternion
	/// @param q The quaternion
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	void SetRotationPart(const QuaternionT<OtherScalar>& q) noexcept
	{
		const bool hasRotation = !q.IsEqual(QuaternionT<OtherScalar>());
		if (hasRotation)
		{
			matrix = q.GetMatrix();
		}
		else
		{
			matrix.SetIdentity();
		}
		switch (type)
		{
		case TransformationType::Identity:
			if (hasRotation)
			{
				type = TransformationType::Rotation;
			}
			break;
		case TransformationType::Rotation:
			if (!hasRotation)
			{
				type = TransformationType::Identity;
			}
			break;
		case TransformationType::Translation:
		case TransformationType::PointMirror:
		case TransformationType::AxisMirror:
		case TransformationType::FrameMirror:
		case TransformationType::Scale:
		case TransformationType::Compound:
		case TransformationType::Other:
			if (hasRotation)
			{
				type = TransformationType::Compound;
			}
			break;
		default:
			break;
		}
	}

	/// @brief Set the transformation as the scaling from a point
	/// @tparam OtherScalar The scalar type of the scaling center point
	/// @tparam OtherScalar2 The type of the scale
	/// @param point The scaling center point
	/// @param s The scale
	template<typename OtherScalar, typename OtherScalar2>
	void SetScale(const PointT<OtherScalar, DIM>& point, const OtherScalar2& s)
	{
		type = TransformationType::Scale;
		scale = static_cast<Scalar>(s);
		CheckScale();
		location = point.Coord() * (OtherScalar2{1} - s);
		matrix.SetIdentity();
	}

	/// @brief Set the transformation as the transformation of two frames in 3D
	/// @tparam OtherScalar The scalar type of the source coordinate system
	/// @tparam OtherScalar2 The scalar type of the target coordinate system
	/// @param frameFrom The source frame
	/// @param frameTo The target frame
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	constexpr void SetDisplacement(const FrameT<OtherScalar, DIM>& frameFrom, const FrameT<OtherScalar2, DIM>& frameTo) noexcept
	{
		type = TransformationType::Compound;
		scale = Scalar{1};
		matrix.SetRows(frameFrom.XDirection().Coord(), frameFrom.YDirection().Coord(), frameFrom.Direction().Coord());
		matrix.LeftMultiply(Matrix3(frameTo.XDirection().Coord(), frameTo.YDirection().Coord(), frameTo.Direction().Coord()));
		location = frameTo.Location().Coord() - matrix * frameFrom.Location().Coord();
	}

	/// @brief Set the transformation as the coordinate transformation between two local coordinate systems in 2D
	/// @tparam OtherScalar The scalar type of the source axis
	/// @tparam OtherScalar2 The scalar type of the target axis
	/// @param axisFrom The source axis
	/// @param axisTo The target axis
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	constexpr void SetTransformation(const AxisT<OtherScalar, DIM>& axisFrom, const AxisT<OtherScalar2, DIM>& axisTo) noexcept
	{
		type = TransformationType::Compound;
		scale = Scalar{1};
		const auto& v1 = axisFrom.Direction().Coord();
		const auto& v2 = axisTo.Direction().Coord();
		matrix.SetRow(0, v2);
		matrix(1, 0) = -v2.Y();
		matrix(1, 1) = v2.X();
		location = matrix * (axisFrom.Location().Coord() - axisTo.Location().Coord());
		matrix *= MatrixT<Scalar, DIM, DIM>(v1, CoordT<Scalar, DIM>{-v1.Y(), v1.X()});
	}

	/// @brief Set the transformation as the coordinate transformation between two local coordinate systems in 3D
	/// @tparam OtherScalar The scalar type of the source frame
	/// @tparam OtherScalar2 The scalar type of the target frame
	/// @param frameFrom The source frame
	/// @param frameTo The target frame
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	constexpr void SetTransformation(const FrameT<OtherScalar, DIM>& frameFrom, const FrameT<OtherScalar2, DIM>& frameTo) noexcept
	{
		type = TransformationType::Compound;
		scale = Scalar{1};
		matrix.SetRows(frameTo.XDirection().Coord(), frameTo.YDirection().Coord(), frameTo.Direction().Coord());
		location = matrix * (frameFrom.Location().Coord() - frameTo.Location().Coord());
		matrix *= MatrixT<Scalar, DIM, DIM>(frameFrom.XDirection().Coord(), frameFrom.YDirection().Coord(), frameFrom.Direction().Coord());
	}

	/// @brief Set the transformation as the coordinate transformation from the standard coordinate system to the target in 2D
	/// @tparam OtherScalar The scalar type of the target axis
	/// @param axisTo The target axis
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	constexpr void SetTransformation(const AxisT<OtherScalar, DIM>& axisTo) noexcept
	{
		type = TransformationType::Compound;
		scale = Scalar{1};
		const auto& v = axisTo.Direction().Coord();
		matrix = MatrixT<Scalar, DIM, DIM>(v, CoordT<Scalar, DIM>{-v.Y(), v.X()}).Transpose();
		location = matrix * (-axisTo.Location().Coord());
	}

	/// @brief Set the transformation as the coordinate transformation from the standard coordinate system to the target in 3D
	/// @tparam OtherScalar The scalar type of the target frame
	/// @param frameTo The target frame
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	constexpr void SetTransformation(const FrameT<OtherScalar, DIM>& frameTo) noexcept
	{
		type = TransformationType::Compound;
		scale = Scalar{1};
		matrix.SetRows(frameTo.XDirection().Coord(), frameTo.YDirection().Coord(), frameTo.Direction().Coord());
		location = matrix * (-frameTo.Location().Coord());
	}

	/// @brief Set the transformation as the translation
	/// @tparam OtherScalar The scalar type of the translation vector
	/// @param vec The translation vector
	template<typename OtherScalar>
	constexpr void SetTranslation(const VectorT<OtherScalar, DIM>& vec) noexcept
	{
		type = TransformationType::Translation;
		scale = Scalar{1};
		matrix.SetIdentity();
		location = vec.Coord();
	}

	/// @brief Set the transformation as the translation formed by two points
	/// @tparam OtherScalar The scalar type of the start point
	/// @tparam OtherScalar2 The scalar type of the end point
	/// @param p1 The start point
	/// @param p2 The end point
	template<typename OtherScalar, typename OtherScalar2>
	constexpr void SetTranslation(const PointT<OtherScalar, DIM>& p1, const PointT<OtherScalar2, DIM>& p2) noexcept
	{
		type = TransformationType::Translation;
		scale = Scalar{1};
		matrix.SetIdentity();
		location = p2.Coord() - p1.Coord();
	}

	/// @brief Set the translation part of the transformation
	/// @tparam OtherScalar The scalar type of the new translation vector
	/// @param vec The translation vector
	template<typename OtherScalar>
	constexpr void SetTranslationPart(const VectorT<OtherScalar, DIM>& vec) noexcept
	{
		location = vec.Coord();
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
		case TransformationType::Other:
			if (!isZero)
			{
				type = TransformationType::Compound;
			}
			break;
		default:
			break;
		}
	}

	/// @brief The the scale factor
	/// @tparam OtherScalar The type of the new scale factor
	/// @param s The new scale factor
	template<typename OtherScalar>
	void SetScaleFactor(const OtherScalar& s)
	{
		scale = static_cast<Scalar>(s);
		CheckScale();
		constexpr Scalar em = Scalar{1.0} - std::numeric_limits<Scalar>::epsilon();
		constexpr Scalar ep = Scalar{1.0} + std::numeric_limits<Scalar>::epsilon();
		bool unit = em <= scale && scale <= ep;
		bool munit = -ep <= scale && scale <= -em;
		switch (type)
		{
		case TransformationType::Identity:
		case TransformationType::Translation:
			if (!unit)
			{
				type = TransformationType::Scale;
			}
			if (munit)
			{
				type = TransformationType::PointMirror;
			}
			break;
		case TransformationType::Rotation:
			if (!unit)
			{
				type = TransformationType::Compound;
			}
			break;
		case TransformationType::PointMirror:
		case TransformationType::AxisMirror:
		case TransformationType::FrameMirror:
			if (!munit)
			{
				type = TransformationType::Scale;
			}
			if (unit)
			{
				type = TransformationType::Identity;
			}
			break;
		case TransformationType::Scale:
			if (unit)
			{
				type = TransformationType::Identity;
			}
			if (munit)
			{
				type = TransformationType::PointMirror;
			}
			break;
		case TransformationType::Compound:
			break;
		case TransformationType::Other:
			break;
		default:
			break;
		}
	}

	/// @brief Set the type of transformation
	/// @param t The new type of transformation
	constexpr void SetType(const TransformationType& t) noexcept
	{
		type = t;
	}

	/// @brief Set the tranformations by values
	/// @details The dimension is DIM * (DIM + 1).
	/// @tparam ...Ts The types of the values
	/// @param ...vs The values
	template<typename... Ts, std::enable_if_t<static_cast<int>(sizeof...(Ts)) == DIM*(DIM + 1) && are_convertible_v<Scalar, Ts...>, int> = 0>
	void SetValues(Ts&&... vs)
	{
		Scalar data[DIM * (DIM + 1)] = {std::forward<Ts>(vs)...};
		MatrixT<Scalar, DIM, DIM> mat;
		for (int i = 0; i < DIM; i++)
		{
			for (int j = 0; j < DIM; j++)
			{
				mat(i, j) = data[i * (DIM + 1) + j];
			}
			location[i] = data[i * (DIM + 1) + DIM];
		}
		Scalar s = mat.Determinant();
		if constexpr (DIM % 2 == 0)
		{
			s = std::fabs(s);
		}
		if constexpr (DIM == 2)
		{
			s = std::sqrt(s);
		}
		else if constexpr (DIM == 3)
		{
			s = std::cbrt(s);
		}
		else
		{
			if (s > 0.0)
			{
				s = std::pow(s, 1.0 / DIM);
			}
			else
			{
				s = -std::pow(-s, 1.0 / DIM);
			}
		}
		scale = s;
		CheckScale();
		matrix = mat / s;
		for (int i = 0; i < DIM; i++)
		{
			auto vec = matrix.Column(i);
			for (int j = 0; j < i; j++)
			{
				vec -= matrix.Column(j) * (matrix.Column(i).Dot(matrix.Column(j)));
			}
			matrix.SetCol(i, vec.Normalized());
		}
		for (int i = 0; i < DIM; i++)
		{
			auto vec = matrix.Row(i);
			for (int j = 0; j < i; j++)
			{
				vec -= matrix.Row(j) * (matrix.Row(i).Dot(matrix.Row(j)));
			}
			matrix.SetRow(i, vec.Normalized());
		}
		type = TransformationType::Compound;
	}

	/// @brief Is the vectorial part of the transformation negative
	/// @return True if the scale factor is negative
	[[nodiscard]] constexpr bool IsNegative() const noexcept
	{
		if constexpr (DIM == 2)
		{
			return matrix.Determinant() < 0.0;
		}
		else
		{
			return scale < Scalar{0};
		}
	}

	/// @brief Get the type of the transformation
	/// @return The transformation type
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

	/// @brief Get the roataion part by an axis and an angle in 3D
	/// @tparam OtherScalar The scalar type of the axis
	/// @tparam OtherScalar2 The type of the angle
	/// @param axis The axis
	/// @param angle The angle
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	void GetRotation(CoordT<OtherScalar, DIM>& axis, OtherScalar2& angle) const noexcept
	{
		CoordT<OtherScalar, DIM> vecTemp;
		GetRotation().GetAxisAngle(vecTemp, angle);
		axis = vecTemp;
	}

	/// @brief Get the rotation part by a quaternion in 3D
	/// @return The quaternion
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] constexpr QuaternionT<Scalar> GetRotation() const noexcept
	{
		return QuaternionT<Scalar>(matrix);
	}

	/// @brief Get the vectorial part of the transformation, i.e. the scaled rotation matrix
	/// @return The vectorial matrix
	[[nodiscard]] constexpr MatrixT<Scalar, DIM, DIM> VectorialPart() const noexcept
	{
		if (scale == Scalar{1})
		{
			return matrix;
		}
		else if (type == TransformationType::Scale || type == TransformationType::PointMirror)
		{
			MatrixT<Scalar, DIM, DIM> mat(matrix);
			for (int i = 0; i < DIM; i++)
			{
				mat(i, i) *= scale;
			}
			return mat;
		}
		else
		{
			return matrix * scale;
		}
	}

	/// @brief Get the homogeneous vectorial part of the transformation, i.e. the rotation matrix
	/// @return The homogeneous matrix
	[[nodiscard]] constexpr const MatrixT<Scalar, DIM, DIM>& HVectorialPart() const noexcept
	{
		return matrix;
	}

	/// @brief Get the matrix of linear homogeneous transformation over projective space
	/// @return The transformation matrix
	constexpr MatrixT<Scalar, DIM + 1, DIM + 1> HomogeneousMatrix() const noexcept
	{
		MatrixT<Scalar, DIM + 1, DIM + 1> m;
		for (int i = 0; i < DIM; i++)
		{
			for (int j = 0; j < DIM; j++)
			{
				m(i, j) = matrix(i, j) * scale;
			}
			m(i, DIM) = location[i];
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
		assert(i >= 0 && i < DIM && j >= 0 && j < DIM + 1);
		return j < DIM ? scale * matrix(i, j) : location[i];
	}

	/// @brief Invert the transformation
	/// @return The reference to self
	constexpr TransformationT& Invert() noexcept
	{
		if (type == TransformationType::Identity)
		{
		}
		else if (type == TransformationType::Translation || type == TransformationType::PointMirror)
		{
			location.Reverse();
		}
		else if (type == TransformationType::Scale)
		{
			scale = Scalar{1} / scale;
			location *= -scale;
		}
		else
		{
			scale = Scalar{1} / scale;
			matrix.Transpose();
			location = -scale * (matrix * location);
		}
		return *this;
	}

	/// @brief Get the inverted transformation
	/// @return The inverted transformation
	[[nodiscard]] constexpr TransformationT Inverted() const noexcept
	{
		return TransformationT(*this).Invert();
	}

	/// @brief Tranformation multiplication assignment
	/// @tparam OtherScalar The scalar type of the other transformation
	/// @param other The other tranformation
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr TransformationT& operator*=(const TransformationT<OtherScalar, DIM>& other) noexcept
	{
		if (other.type == TransformationType::Identity)
		{
		}
		else if (type == TransformationType::Identity)
		{
			type = other.type;
			matrix = other.matrix;
			scale = static_cast<Scalar>(other.scale);
			location = other.location;
		}
		else if (type == TransformationType::Rotation && other.type == TransformationType::Rotation)
		{
			if (other.location.SquaredNorm() != Scalar{0})
			{
				location += matrix * other.location;
			}
			matrix *= other.matrix;
		}
		else if (type == TransformationType::Translation && other.type == TransformationType::Translation)
		{
			location += other.location;
		}
		else if (type == TransformationType::Scale && other.type == TransformationType::Scale)
		{
			location += other.location * scale;
			scale *= other.scale;
		}
		else if (type == TransformationType::PointMirror && other.type == TransformationType::PointMirror)
		{
			scale = Scalar{1};
			type = TransformationType::Translation;
			location -= other.location;
		}
		else if (type == TransformationType::AxisMirror && other.type == TransformationType::AxisMirror)
		{
			type = TransformationType::Rotation;
			location += matrix * other.location;
			matrix *= other.matrix;
		}
		else if ((type == TransformationType::Compound || type == TransformationType::Rotation || type == TransformationType::AxisMirror || type == TransformationType::FrameMirror) && other.type == TransformationType::Translation)
		{
			location += scale * (matrix * other.location);
		}
		else if ((type == TransformationType::Scale || type == TransformationType::PointMirror) && other.type == TransformationType::Translation)
		{
			location += scale * other.location;
		}
		else if (type == TransformationType::Translation && (other.type == TransformationType::Compound || other.type == TransformationType::Rotation || other.type == TransformationType::AxisMirror || other.type == TransformationType::FrameMirror))
		{
			type = TransformationType::Compound;
			scale = other.scale;
			location += other.location;
			matrix = other.matrix;
		}
		else if (type == TransformationType::Translation && (other.type == TransformationType::Scale || other.type == TransformationType::PointMirror))
		{
			type = other.type;
			location += other.location;
			scale = other.scale;
		}
		else if ((type == TransformationType::PointMirror || type == TransformationType::Scale) && (other.type == TransformationType::PointMirror || other.type == TransformationType::Scale))
		{
			type = TransformationType::Compound;
			location += scale * other.location;
			scale *= other.scale;
		}
		else if ((type == TransformationType::Compound || type == TransformationType::Rotation || type == TransformationType::AxisMirror || type == TransformationType::FrameMirror) && (other.type == TransformationType::Scale || other.type == TransformationType::PointMirror))
		{
			type = TransformationType::Compound;
			if (scale == Scalar{1})
			{
				location += matrix * other.location;
				scale = other.scale;
			}
			else
			{
				location += scale * (matrix * other.location);
				scale *= other.scale;
			}
		}
		else if ((other.type == TransformationType::Compound || other.type == TransformationType::Rotation || other.type == TransformationType::AxisMirror || other.type == TransformationType::FrameMirror) && (type == TransformationType::Scale || type == TransformationType::PointMirror))
		{
			type = TransformationType::Compound;
			location += scale * other.location;
			scale *= other.scale;
			matrix = other.matrix;
		}
		else
		{
			type = TransformationType::Compound;
			if (scale != Scalar{1})
			{
				location += scale * (matrix * other.location);
				scale *= other.scale;
			}
			else
			{
				location += matrix * other.location;
				scale = other.scale;
			}
			matrix *= other.matrix;
		}
		return *this;
	}

	/// @brief Tranformation multiplication operator
	/// @tparam OtherScalar The scalar type of the other transformation
	/// @param other The other transformation
	/// @return The multiplied transformation
	template<typename OtherScalar>
	[[nodiscard]] constexpr TransformationT operator*(const TransformationT<OtherScalar, DIM>& other) const noexcept
	{
		return TransformationT(*this) *= other;
	}

	/// @brief Transformation left multiplication assignment
	/// @tparam OtherScalar The scalar type of the other transformation
	/// @param other The other transformation
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr TransformationT& LeftMultiply(const TransformationT<OtherScalar, DIM>& other) noexcept
	{
		if (other.type == TransformationType::Identity)
		{
		}
		else if (type == TransformationType::Identity)
		{
			type = other.type;
			scale = static_cast<Scalar>(other.scale);
			location = other.location;
			matrix = other.matrix;
		}
		else if (type == TransformationType::Rotation && other.type == TransformationType::Rotation)
		{
			location = other.matrix * location + other.location;
			matrix.LeftMultiply(other.matrix);
		}
		else if (type == TransformationType::Translation && other.type == TransformationType::Translation)
		{
			location += other.location;
		}
		else if (type == TransformationType::Scale && other.type == TransformationType::Scale)
		{
			location *= other.scale;
			location += other.location;
			scale *= other.scale;
		}
		else if (type == TransformationType::PointMirror && other.type == TransformationType::PointMirror)
		{
			scale = Scalar{1};
			type = TransformationType::Translation;
			location = other.location - location;
		}
		else if (type == TransformationType::AxisMirror && other.type == TransformationType::AxisMirror)
		{
			type = TransformationType::Rotation;
			location = other.matrix * location + other.location;
			matrix.LeftMultiply(other.matrix);
		}
		else if ((type == TransformationType::Compound || type == TransformationType::Rotation || type == TransformationType::AxisMirror || type == TransformationType::FrameMirror) && other.type == TransformationType::Translation)
		{
			location += other.location;
		}
		else if ((type == TransformationType::Scale || type == TransformationType::PointMirror) && other.type == TransformationType::Translation)
		{
			location += other.location;
		}
		else if (type == TransformationType::Translation && (other.type == TransformationType::Compound || other.type == TransformationType::Rotation || other.type == TransformationType::AxisMirror || other.type == TransformationType::FrameMirror))
		{
			type = TransformationType::Compound;
			matrix = other.matrix;
			if (other.scale == OtherScalar{1})
			{
				location = other.matrix * location + other.location;
			}
			else
			{
				scale = other.scale;
				location = scale * (matrix * location) + other.location;
			}
		}
		else if ((other.type == TransformationType::Scale || other.type == TransformationType::PointMirror) && type == TransformationType::Translation)
		{
			location = other.scale * location + other.location;
			scale = static_cast<Scalar>(other.scale);
			type = other.type;
		}
		else if ((type == TransformationType::PointMirror || type == TransformationType::Scale) && (other.type == TransformationType::PointMirror || other.type == TransformationType::Scale))
		{
			type = TransformationType::Compound;
			location = other.scale * location + other.location;
			scale *= other.scale;
		}
		else if ((type == TransformationType::Compound || type == TransformationType::Rotation || type == TransformationType::AxisMirror || type == TransformationType::FrameMirror) && (other.type == TransformationType::Scale || other.type == TransformationType::PointMirror))
		{
			type = TransformationType::Compound;
			location = other.scale * location + other.location;
			scale *= other.scale;
		}
		else if ((other.type == TransformationType::Compound || other.type == TransformationType::Rotation || other.type == TransformationType::AxisMirror || other.type == TransformationType::FrameMirror) && (type == TransformationType::Scale || type == TransformationType::PointMirror))
		{
			type = TransformationType::Compound;
			matrix = other.matrix;
			if (other.scale == OtherScalar{1})
			{
				location = matrix * location + other.location;
			}
			else
			{
				location = other.scale * matrix * location + other.location;
				scale *= other.scale;
			}
		}
		else
		{
			type = TransformationType::Compound;
			if (other.scale != OtherScalar{1})
			{
				location = other.scale * (other.matrix * location) + other.location;
				scale *= other.scale;
			}
			else
			{
				location = other.matrix * location + other.location;
			}
			matrix.LeftMultiply(other.matrix);
		}
		return *this;
	}

	/// @brief Get the transformation left multiplied by the other transformation
	/// @tparam OtherScalar The scalar type of the other transformation
	/// @param other The other transformation
	/// @return The multiplied transformation
	template<typename OtherScalar>
	[[nodiscard]] constexpr TransformationT LeftMultiplied(const TransformationT<OtherScalar, DIM>& other) const noexcept
	{
		return TransformationT(*this).LeftMultiply(other);
	}

	/// @brief Power of transformation
	/// @param power The exponential
	/// @return The reference to self
	constexpr TransformationT& Power(int power) noexcept
	{
		if (type == TransformationType::Identity)
		{
		}
		else
		{
			if (power == 0)
			{
				scale = Scalar{1};
				type = TransformationType::Identity;
				matrix.SetIdentity();
				location.fill(Scalar{0});
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
				if (type == TransformationType::Translation)
				{
					location *= power;
				}
				else if (type == TransformationType::Scale)
				{
					int Npower = power < 0 ? -power : power;
					Scalar fscale{1.0};
					for (int i = 0; i < Npower; i++)
					{
						fscale *= scale;
					}
					if (power < 0)
					{
						fscale = Scalar{1} / fscale;
					}
					location *= scale == Scalar{1} ? Scalar{1} : (Scalar{1} - fscale) / (Scalar{1} - scale);
					scale = fscale;
				}
				else if (type == TransformationType::Rotation)
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
					MatrixT<Scalar, DIM, DIM> Tempmatrix(matrix);
					if (location.SquaredNorm() == Scalar{0})
					{
						while (true)
						{
							if (Npower % 2)
							{
								matrix *= Tempmatrix;
							}
							if (Npower == 1)
							{
								break;
							}
							Tempmatrix *= Tempmatrix;
							Npower /= 2;
						}
					}
					else
					{
						CoordT<Scalar, DIM> Temploc = location;
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
				else if (type == TransformationType::PointMirror || type == TransformationType::AxisMirror)
				{
					if (power < 0)
					{
						Invert();
					}
					if (power % 2 == 0)
					{
						type = TransformationType::Identity;
						scale = Scalar{1};
						matrix.SetIdentity();
						location.fill(Scalar{0});
					}
				}
				else
				{
					if (power < 0)
					{
						Invert();
					}
					type = TransformationType::Compound;
					int Npower = power;
					if (Npower < 0)
					{
						Npower = -Npower;
					}
					Npower--;
					CoordT<Scalar, DIM> Temploc = location;
					Scalar Tempscale = scale;
					MatrixT<Scalar, DIM, DIM> Tempmatrix(matrix);
					while (true)
					{
						if (Npower % 2)
						{
							location += scale * (matrix * Temploc);
							scale *= Tempscale;
							matrix *= Tempmatrix;
						}
						if (Npower == 1)
						{
							break;
						}
						Tempscale *= Tempscale;
						Temploc += Tempscale * (Tempmatrix * Temploc);
						Tempmatrix *= Tempmatrix;
						Npower /= 2;
					}
				}
			}
		}
		return *this;
	}

	/// @brief Get the power of transformation
	/// @param power The exponential
	/// @return The power of transformation
	[[nodiscard]] constexpr TransformationT Powered(int power) const noexcept
	{
		return TransformationT(*this).Power(power);
	}

	/// @brief Transform the vector
	/// @tparam OtherScalar The scalar type of the vector
	/// @param[in,out] coord The coordinate of the vector
	template<typename OtherScalar>
	constexpr void Transform(CoordT<OtherScalar, DIM>& coord) const noexcept
	{
		coord = scale == Scalar{1.0} ? matrix * coord + location : scale * (matrix * coord) + location;
	}

	/// @brief Write the transformation
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param tr The transformation
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const TransformationT& tr)
	{
		os << tr.ScaleFactor() << ' ' << std::to_underlying(tr.Type()) << '\n';
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

#ifndef DOXYGEN_SKIP
protected:
	/// @brief Check the validity of scale
	void CheckScale()
	{
		if (std::abs(scale) <= std::numeric_limits<Scalar>::min())
		{
			throw ConstructionError("transformation has zero scale");
		}
	}

	template<typename, int>
	friend class GeneralTransformationT;

	/// @brief Scale factor
	Scalar scale;

	/// @brief Type of transformation
	TransformationType type;

	/// @brief Rotation part
	MatrixT<Scalar, DIM, DIM> matrix;

	/// @brief Translation part
	CoordT<Scalar, DIM> location;
#endif
};

/// @brief 2D transformation
using Transformation2 = TransformationT<double, 2>;

/// @brief 3D transformation
using Transformation3 = TransformationT<double, 3>;

} // namespace AMCAX
