/// @file      AMCAXGCS.h
/// @brief     class of GCSWSystem
/// @details   Wrapper of GCSSystem
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
///
#ifndef AMCAX_GCS_H_
#define AMCAX_GCS_H_

#include <iostream>
#include <memory>
#include <vector>

#ifndef AMCAX_GCS_API
#ifdef _MSC_VER
#ifdef AMCAXGCS_EXPORTS
#define AMCAX_GCS_API __declspec(dllexport)
#else
#define AMCAX_GCS_API __declspec(dllimport)
#endif // AMCAXGCS_EXPORTS
#else
#define AMCAX_GCS_API
#endif // MSC_VER
#endif // AMCAX_GCS_API

namespace AMCAX {
    namespace GCS {
        class GCSConHandle;
        class GCSRigidBody;
        class GCSSystem;
        class GCSVarGeomHandle;
        /**
         * @brief Point
         */
        struct AMCAX_GCS_API Point3d {
            double x;
            double y;
            double z;
        };

        /**
         * @brief Vector
         */
        struct AMCAX_GCS_API Vector3d {
            double x;
            double y;
            double z;
        };

        /**
         * @brief Line represented by a point and the normalized direction vector.
         */
        struct AMCAX_GCS_API Line3d {
            /**
             * @brief A point on the line
             */
            Point3d origin;
            /**
             * @brief Normalized line direction vector
             */
            Vector3d direction;
        };

        /**
         * @brief Plane represented by a point and the normalized normal vector.
         */
        struct AMCAX_GCS_API Plane {
            /**
             * @brief A point on the plane
             */
            Point3d origin;
            /**
             * @brief Normalized normal vector
             */
            Vector3d normal;
        };

        /**
        * @brief Torus represented by a circular spine and the radius of circular
        * cross-section
        */
        struct AMCAX_GCS_API Torus {
            /**
             * @brief Center of the spine curve
             */
            Point3d center;
            /**
             * @brief Normal to the plane of the spline
             */
            Vector3d normal;
            /**
             * @brief Radius of the spine curve
             */
            double majorRadius;
            /**
             * @brief Radius of the circular cross-section
             */
            double minorRadius;
        };

        /**
         * @brief Rigid transformation matrix.
         */
        struct AMCAX_GCS_API Matrix3d {
            double a00 = 1;
            double a01 = 0;
            double a02 = 0;
            double a03 = 0;
            double a10 = 0;
            double a11 = 1;
            double a12 = 0;
            double a13 = 0;
            double a20 = 0;
            double a21 = 0;
            double a22 = 1;
            double a23 = 0;
            double a30 = 0;
            double a31 = 0;
            double a32 = 0;
            double a33 = 1;
        };

        /**
         * @brief Point in 2d
         */
        struct AMCAX_GCS_API Point2d {
            double x;
            double y;
        };

        /**
         * @brief Vector in 2d
         */
        struct AMCAX_GCS_API Vector2d {
            double x;
            double y;
        };

        /**
         * @brief Line in 2d
         */
        struct AMCAX_GCS_API Line2d {
            Point2d start;
            Point2d end;
        };

        /**
         * @brief Circle in 2d
         */
        struct AMCAX_GCS_API Circle2d {
            Point2d center;
            double radius;
        };

        /**
         * @brief Arc of circle in 2d
         */
        struct AMCAX_GCS_API Arc2d {
            Point2d center;
            double radius;
            double thetaStart;
            double thetaRange;
        };

        /**
         * @brief Ellipse in 2d
         */
        struct AMCAX_GCS_API Ellipse2d {
            Point2d center;
            Vector2d majorAxis;
            Vector2d minorAxis;
            double majorRadius;
            double minorRadius;
        };

        /**
         * @brief Arc of ellipse in 2d
         */
        struct AMCAX_GCS_API ArcOfEllipse2d {
            Point2d center;
            Vector2d majorAxis;
            Vector2d minorAxis;
            double majorRadius;
            double minorRadius;
            double thetaStart;
            double thetaRange;
        };

        /**
         * @brief Arc of parabola in 2d
         */
        struct AMCAX_GCS_API ArcOfParabola2d {
            Point2d focus;
            Point2d vertex;
            double paramStart;
            double paramEnd;
        };

        /**
        * @brief Arc of hyperbola in 2d
        */
        struct AMCAX_GCS_API ArcOfHyperbola2d {
            Point2d focus;      // focus
            Point2d center;     // center
            double majorRadius; // major radius
            double paramStart;  // hyperbolic angle of start
            double paramEnd;    // hyperbolic angle of end
        };

        /**
         * @brief B-spline curve in 2d
         */
        struct AMCAX_GCS_API BSplineCurve2d {
            std::vector<Point2d> controlPoints;
            std::vector<double> flatKnots;
            std::vector<double> knots;
            std::vector<int> multiplicities;
            int degree;
        };

        /**
         * @brief Enumeration of GCSSystem status
         */
        enum AMCAX_GCS_API Status {
            kNull = 0,
            kError,
            kOK,
            kSolved,
            kRedundantSolved,
            kRedundantError,
        };

        /**
         * @brief Alignment mode.
         */
        enum AMCAX_GCS_API VecSense {
            kCodirectional, ///< Same direction
            kOpposed,       ///< Opposite direction
            kParallel,      ///< Do not specify direction
            kReference
        };

        /**
         * @brief Geometry constrained status mode.
         */
        enum AMCAX_GCS_API GeometryConstrainedStatus {
            kUnderConstrained, ///< geometry still have degree of freedom
            kWellConstrained,  ///< geometry degree of freedom is 0
            kOverConstrained,  ///< too many constraints related with the geometry
        };

        /**
         * @brief The wrapper for GCSVarGeomHandle.
         */
        class AMCAX_GCS_API GCSWVarGeomHandle {
        public:
            GCSWVarGeomHandle();
            GCSWVarGeomHandle(std::shared_ptr<GCSVarGeomHandle> handle);
            ~GCSWVarGeomHandle();
            void SetVarGeomHandle(std::shared_ptr<GCSVarGeomHandle> handle);
            std::shared_ptr<GCSVarGeomHandle> VarGeomHandle() const;

            /**
             * @brief Check if the geometry is invariable
             * @return If the geometry is invariable/it is part of one invariable
             * geometry
             */
            bool Invariable() const;

            /**
             * @brief Set the property Invariable
             * @return If it works
             */
            bool SetInvariable(bool invariable);

            /**
             * @brief Check if the handle is null
             * @return If the handle is null
             */
            bool IsNull() const;

        private:
            std::shared_ptr<GCSVarGeomHandle> varGeomHandle;
        };

        /**
         * @brief The wrapper for GCSRigidBody.
         */
        class AMCAX_GCS_API GCSWRigidBody {
        public:
            GCSWRigidBody();
            GCSWRigidBody(std::shared_ptr<GCSRigidBody> b);
            ~GCSWRigidBody() {}

            std::shared_ptr<GCSRigidBody> Body() const;
            /** @brief Set transform by 4x4 transform matrix. */
            void SetTransform(std::vector<double> param);
            /** @brief Ground it or not? */
            void SetGrounded(bool t);
            /** @brief check if the body is grounded */
            bool IsGrounded() const;
            /** @brief Set the center of rotation. */
            void SetCOR(const Point3d&);
            /** @brief Get the current transform of the body. */
            Matrix3d Transform() const;

        private:
            std::shared_ptr<GCSRigidBody> body = nullptr;
        };

        /**
         * @brief The wrapper for GCSConHandle.
         */
        class AMCAX_GCS_API GCSWConHandle {
        public:
            GCSWConHandle();
            GCSWConHandle(std::shared_ptr<GCSConHandle> h);
            ~GCSWConHandle();

            /** @brief Set handle for the constraint. */
            void SetConHandle(std::shared_ptr<GCSConHandle> h);
            /** @brief Is the handle related to null. */
            bool IsNull() const;
            /** @brief Is the handle related to over-constrained part. */
            bool IsOverConstrained() const;

        private:
            std::shared_ptr<GCSConHandle> conHandle;
        };

        /**
         * @brief The wrapper for GCSSystem.
         */
        class AMCAX_GCS_API GCSWSystem {
        public:
            GCSWSystem();
            ~GCSWSystem();

            /**
             * @brief Reset the system for next use.
             */
            void Reset();

            /**
             * @brief Create rigid body from the id.
             * @param id The id of the rigid body.
             * @return The wrapper of rigid body.
             */
            GCSWRigidBody CreateRigidBody(unsigned int id);

            /**
             * @brief Update the point position based on the transformation of the rigid
             * body.
             * @param body The body that contains the point
             * @param point The initial point
             * @return The updated point.
             */
            Point3d UpdatePoint3dPosition(const GCSWRigidBody& body, Point3d& point);

            /**
             * @brief Update the vector based on the transformation of the rigid body.
             * @param body The body that contains the vector
             * @param vector The initial vector
             * @return The updated vector.
             */
            Vector3d UpdateVector3dPosition(
                const GCSWRigidBody& body, Vector3d& vector);

            /**
             * @brief Update the line based on the transformation of the rigid body.
             * @param body The body that contains the line
             * @param line The initial line
             * @return The updated line.
             */
            Line3d UpdateLine3dPosition(const GCSWRigidBody& body, Line3d& line);

            /**
             * @brief Update the plane based on the transformation of the rigid body.
             * @param body The body that contains the plane
             * @param plane The initial plane
             * @return The updated plane.
             */
            Plane UpdatePlanePosition(const GCSWRigidBody& body, Plane& plane);

            /**
             * @brief Create a 3D distance point/point constraint.
             * @param h Return a handle to the constraint
             * @param body1 Body that owns point1
             * @param body2 Body that owns point2
             * @param pt1 Point1
             * @param pt2 Point2
             * @param d Distance between points
             */
            Status Create3dDistPtPt(GCSWConHandle& h, const GCSWRigidBody& body1,
                const GCSWRigidBody& body2, const Point3d& pt1, const Point3d& pt2,
                double d);

            /**
             * @brief Create a 3D distance point/plane constraint.
             * @param h Return a handle to the constraint
             * @param body1 Body that owns point
             * @param body2 Body that owns plane
             * @param pt Point to constrain
             * @param pl Plane to constrain
             * @param d Distance between point and plane
             */
            Status Create3dDistPtPl(GCSWConHandle& h, const GCSWRigidBody& body1,
                const GCSWRigidBody& body2, const Point3d& pt, const Plane& pl,
                double d);

            /**
             * @brief Create a 3D distance point/line constraint.
             * @param h Return a handle to the constraint
             * @param body1 Body that owns the point
             * @param body2 Body that owns the line
             * @param pt Point to constrain
             * @param ln Line to constrain
             * @param d Distance between point and line
             */
            Status Create3dDistPtLn(GCSWConHandle& h, const GCSWRigidBody& body1,
                const GCSWRigidBody& body2, const Point3d& pt, const Line3d& ln,
                double d);

            /**
             * @brief Create a 3D distance line/plane constraint.
             * @param h Return a handle to the constraint
             * @param body1 Body that owns the line
             * @param body2 Body that owns the plane
             * @param ln Line to constrain
             * @param pl Plane to constrain
             * @param d Distance between line and plane
             */
            Status Create3dDistLnPl(GCSWConHandle& h, const GCSWRigidBody& body1,
                const GCSWRigidBody& body2, const Line3d& ln, const Plane& pl,
                double d);

            /**
             * @brief Create a 3D distance line/line constraint. The two lines are
             * forced to be parallel.
             * @param h Return a handle to the constraint
             * @param body1 Body owning line1
             * @param body2 Body owning line2
             * @param ln1 Line1
             * @param ln2 Line2
             * @param d Distance between lines
             * @param vecSense Specify alignment mode of two lines
             */
            Status Create3dDistLnLn(GCSWConHandle& h, const GCSWRigidBody& body1,
                const GCSWRigidBody& body2, const Line3d& ln1, const Line3d& ln2,
                double d, VecSense vecSense);

            /**
             * @brief Create a 3D distance plane/plane constraint.
             * @param h Return a handle to the constraint
             * @param body1 Body owning plane1
             * @param body2 Body owning plane2
             * @param pl1 Plane1
             * @param pl2 Plane2
             * @param vecSense Specify alignment mode of two planes
             * @param d Distance between planes
             */
            Status Create3dDistPlPl(GCSWConHandle& h, const GCSWRigidBody& body1,
                const GCSWRigidBody& body2, const Plane& pl1, const Plane& pl2,
                VecSense vecSense, double d);

            /**
             * @brief Create a 3D angular constraint.
             * @param h Return a handle to the constraint
             * @param body1 Body owning vector1
             * @param body2 Body owning vector2
             * @param vector1 Vector1
             * @param vector2 Vector2
             * @param vecSense Specify alignment mode of two vectors
             * @param a Angle between vectors (radians)
             * @param body3 Body that owns the reference vector
             * @param vector3 The reference vector
             */
            Status Create3dAngVecVec(GCSWConHandle& h, const GCSWRigidBody& body1,
                const GCSWRigidBody& body2, const Vector3d& vector1,
                const Vector3d& vector2, VecSense vecSense, double a,
                const GCSWRigidBody& body3, const Vector3d& vector3);

            /**
             * @brief Create a 3D symmetric constraint between two points about one
             * fixed plane
             * @param h Return a handle to the constraint
             * @param body1 Body owning point1
             * @param body2 Body owning point2
             * @param point1 Point1
             * @param point2 Point2
             * @param plane Symmetry plane
             */
            Status Create3dSymmPtPt(GCSWConHandle& h, const GCSWRigidBody& body1,
                const GCSWRigidBody& body2, const Point3d& point1,
                const Point3d& point2, const Plane& plane);

            /**
             * @brief Create a 3D symmetric constraint between two points about one
             * plane
             * @param h Return a handle to the constraint
             * @param body1 Body owning point1
             * @param body2 Body owning point2
             * @param bodySymm Body owning the symmetry plane
             * @param point1 Point1
             * @param point2 Point2
             * @param plane Symmetry plane
             */
            Status Create3dSymmPtPt(GCSWConHandle& h, const GCSWRigidBody& body1,
                const GCSWRigidBody& body2, const GCSWRigidBody& bodySymm,
                const Point3d& point1, const Point3d& point2, const Plane& plane);

            /**
            * @brief Process dragging.
            * @param body Body to drag
            * @param oldPos Old position of dragged bodies
            * @param newPos New screen position of dragged bodies
            * @param viewVector View vector
            * @param mode Drag mode. mode = 0 means translation drag; mode = 1 means
            rotation drag, notice that: in the rotation dragging mode, the COR of the
            dragBody must be set before dragging
            */
            Status PrioritizedDrag(const GCSWRigidBody& body, const Point3d& oldPos,
                const Point3d& newPos, const Vector3d& viewVector, unsigned int mode);

            /**
             * @brief Create a point in 2D
             * @param h Return a handle to the point
             * @param point Point
             */
            Status Create2dPoint(GCSWVarGeomHandle& h, const Point2d& point);

            /**
             * @brief Get point
             * @param h Handle to the point
             * @return point position
             */
            Point2d GetPoint2d(const GCSWVarGeomHandle& h) const;

            /**
             * @brief Create a line segment in 2D
             * @param h Return h handle to the line segment
             * @param point0 Handle to the start of the line
             * @param point1 Handle to the end of the line
             */
            Status Create2dLine(GCSWVarGeomHandle& h, const GCSWVarGeomHandle& point0,
                const GCSWVarGeomHandle& point1);

            /**
             * @brief Get line
             * @param h Handle to the line
             * @return line
             */
            Line2d GetLine2d(const GCSWVarGeomHandle& h) const;

            /**
             * @brief Create a circle in 2D
             * @param h Return a handle to the circle
             * @param center Handle to the center of circle
             * @param radius Radius
             */
            Status Create2dCircle(
                GCSWVarGeomHandle& h, const GCSWVarGeomHandle& center, double radius);

            /**
             * @brief Get circle
             * @param h Handle to the circle
             * @return circle
             */
            Circle2d GetCircle2d(const GCSWVarGeomHandle& h) const;

            /**
             * @brief Create an arc in 2D
             * @param h Return a handle to the arc
             * @param center Handle to the center of arc
             * @param start Handle to the start of arc
             * @param end Handle to the end of arc
             * @param range Range of arc. If no range is specified, gcs will
             * calculate the range counter-clockwise by default.
             */
            Status Create2dArc(GCSWVarGeomHandle& h, const GCSWVarGeomHandle& center,
                const GCSWVarGeomHandle& start, const GCSWVarGeomHandle& end,
                double range = 0);

            /**
             * @brief Get arc
             * @param h Handle to the arc
             * @return arc
             */
            Arc2d GetArc2d(const GCSWVarGeomHandle& h) const;

            /**
             * @brief Create an ellipse in 2D
             * @param h Return a handle to the ellipse
             * @param center Handle to the center of ellipse
             * @param majorAxis Major axis direction
             * @param majorRadius Major radius of the elliptical shape
             * @param minorAxis Minro axis direction
             * @param minorRadius Minor radius of the elliptical shape
             */
            Status Create2dEllipse(GCSWVarGeomHandle& h,
                const GCSWVarGeomHandle& center, const Vector2d& majorAxis,
                double majorRadius, const Vector2d& minorAxis, double minorRadius);

            /**
             * @brief Get ellipse
             * @param h Handle to the ellipse
             * @return ellipse
             */
            Ellipse2d GetEllipse2d(const GCSWVarGeomHandle& h) const;

            /**
             * @brief Create an arc of ellipse in 2D
             * @param h Return a handle to the arc of ellipse
             * @param center Handle to the center of ellipse
             * @param majorAxis Major axis direction
             * @param majorRadius Major radius of the elliptical shape
             * @param minorAxis Minor axis direction
             * @param minorRadius Minor radius of the elliptical shape
             * @param start Handle to the start of arc of ellipse
             * @param end Handle to the end of arc of ellipse
             * @param range Range of arc. If no range is specified, gcs will
             * calculate the range counter-clockwise by default.
             */
            Status Create2dArcOfEllipse(GCSWVarGeomHandle& h,
                const GCSWVarGeomHandle& center, const Vector2d& majorAxis,
                double majorRadius, const Vector2d& minorAxis, double minorRadius,
                const GCSWVarGeomHandle& start, const GCSWVarGeomHandle& end,
                double range = 0);

            /**
             * @brief Get arc of ellipse
             * @param h Handle to the arc of ellipse
             * @return arc of ellipse
             */
            ArcOfEllipse2d GetArcOfEllipse2d(const GCSWVarGeomHandle& h) const;

            /**
             * @brief Create an arc of parabola in 2D
             * @param h Return a handle to the arc of parabola
             * @param focus Handle to the focus of parabola
             * @param vertex Vertex of parabola
             * @param start Handle to the start of arc
             * @param end Handle to the end of arc
             */
            Status Create2dArcOfParabola(GCSWVarGeomHandle& h,
                const GCSWVarGeomHandle& focus, const Point2d& vertex,
                const GCSWVarGeomHandle& start, const GCSWVarGeomHandle& end);

            /**
             * @brief Get arc of parabola
             * @param h Handle to the arc of parabola
             * @return arc of parabola
             */
            ArcOfParabola2d GetArcOfParabola2d(const GCSWVarGeomHandle& h) const;

            /**
            * @brief Create an arc of hyperbola in 2D
            * @param h Return a handle to the arc of hyperbola
            * @param center Handle to the center of hyperbola
            * @param focus Handle to the focus of hyperbola
            * @param majorRadius Major radius of hyperbola
            * @param start Handle to the start of arc
            * @param end Handle to the end of arc
            */
            Status Create2dArcOfHyperbola(GCSWVarGeomHandle& h,
                const GCSWVarGeomHandle& center, const GCSWVarGeomHandle& focus,
                double majorRadius, const GCSWVarGeomHandle& start,
                const GCSWVarGeomHandle& end);

            /**
             * @brief Get arc of hyperbola
             * @param h Handle to the arc of hyperbola
             * @return arc of hyperbola
             */
            ArcOfHyperbola2d GetArcOfHyperbola2d(const GCSWVarGeomHandle& h) const;

            /**
             * @brief Create a non-rational cubic B-spline curve in 2D
             * @param h Return a handle to the b-spline curve
             * @param controlPoints Array of handles to control points
             * @param knotSequence Array of flat knot
             */
            Status Create2dCubicBSplineCurve(GCSWVarGeomHandle& h,
                const std::vector<GCSWVarGeomHandle>& controlPoints,
                const std::vector<double>& knotSequence);

            /**
             * @brief Create a non-rational B-spline curve in 2D
             * @param h Return a handle to the b-spline curve
             * @param controlPoints Array of handles to control points
             * @param knotSequence Array of flat knot
             * @param degree Degree of the curve. It should not exceed 9.
             */
            Status Create2dBSplineCurve(GCSWVarGeomHandle& h,
                const std::vector<GCSWVarGeomHandle>& controlPoints,
                const std::vector<double>& knotSequence, int degree);

            /**
             * @brief Create a non-rational B-spline curve in 2D
             * @param h Return a handle to the b-spline curve
             * @param controlPoints Array of handles to control points
             * @param knots Array of knots
             * @param multiplicities Array of multiplicity of knots
             * @param degree Degree of the curve. It should not exceed 9.
             */
            Status Create2dBSplineCurve(GCSWVarGeomHandle& h,
                const std::vector<GCSWVarGeomHandle>& controlPoints,
                const std::vector<double>& knots,
                const std::vector<int>& multiplicities, int degree);

            /**
             * @brief Get b-spline curve
             * @param h Handle to the b-spline curve
             * @return b-spline curve
             */
            BSplineCurve2d GetBSplineCurve2d(const GCSWVarGeomHandle& h) const;

            /**
             * @brief Create a 2D distance point/point constraint.
             * @param h Return a handle to the constraint
             * @param pt1 Handle to point1
             * @param pt2 handle to point2
             * @param d Distance between point1 and point2. d=0 indicates coincidence
             */
            Status Create2dDistPtPt(GCSWConHandle& h, GCSWVarGeomHandle& pt1,
                GCSWVarGeomHandle& pt2, double d);

            /**
             * @brief Create a 2D distance point/line constraint.
             * @param h Return a handle to the constraint
             * @param pt Handle to point
             * @param ln handle to line
             * @param d Distance between point and line
             */
            Status Create2dDistPtLn(GCSWConHandle& h, GCSWVarGeomHandle& pt,
                GCSWVarGeomHandle& ln, double d);

            /**
             * @brief Create a constraint to attach the point to the object
             * @param h Return a handle to the constraint
             * @param pt Handle to the point
             * @param geom Handle to the attached object, such as line, circle, ellipse,
             * hyperbola, parabola, b-spline
             */
            Status Create2dPtOnObject(
                GCSWConHandle& h, GCSWVarGeomHandle& pt, GCSWVarGeomHandle& geom);

            /**
             * @brief Create a 2D angle vector/vector constraint.
             * @param h Return a handle to the constraint
             * @param v1 Handle to vector1
             * @param v2 handle to vector2
             * @param a Angle between vector1 and vector2 in radian
             */
            Status Create2dAngVecVec(GCSWConHandle& h, GCSWVarGeomHandle& v1,
                GCSWVarGeomHandle& v2, double a);

            /**
             * @brief Crate an angle constraint on a 2D arc
             * @param h Return a handle to the constraint
             * @param arc Handle to the arc
             * @param a Angle between start and end
             */
            Status Create2dAngArc(GCSWConHandle& h, GCSWVarGeomHandle& arc, double a);

            /**
             * @brief Create a 2D distance line/line constraint.
             * @param h Return a handle to the constraint
             * @param ln1 Handle to line1
             * @param ln2 handle to line2
             * @param d Distance between line1 and line2
             */
            Status Create2dDistLnLn(GCSWConHandle& h, GCSWVarGeomHandle& ln1,
                GCSWVarGeomHandle& ln2, double d);

            /**
             * @brief Create a 2D tangent line/circle constraint.
             * @param h Return a handle to the constraint
             * @param ln Handle to the line
             * @param cir Handle to the circle
             * @param d Gap between the circle and line
             */
            Status Create2dTanLnCir(GCSWConHandle& h, GCSWVarGeomHandle& ln,
                GCSWVarGeomHandle& cir, double d);

            /**
             * @brief Create a 2D tangent line/ellipse constraint.
             * @param h Return a handle to the constraint
             * @param line Handle to the line
             * @param ellipse Handle to the ellipse
             */
            Status Create2dTanLnEll(
                GCSWConHandle& h, GCSWVarGeomHandle& ln, GCSWVarGeomHandle& ellipse);

            /**
             * @brief Create a 2D tangent circle/circle constraint.
             * @param h Return a handle to the constraint
             * @param circle1 Handle to the circle1
             * @param circle2 handle to the circle2
             * @param vecSense Specify circumscribed or inscribed
             * kCodirectional-circumscribed, kOpposed-inscribed, kParallel-both
             * @param d Gap between the circles
             */
            Status Create2dTanCirCir(GCSWConHandle& h, GCSWVarGeomHandle& circle1,
                GCSWVarGeomHandle& circle2, VecSense vecSense, double d);

            /**
             * @brief Create a 2D tangent circle/ellipse constraint.
             * @param h Return a handle to the constraint
             * @param circle Handle to the circle
             * @param ellipse Hadnle to the ellipse
             */
            Status Create2dTanCirEll(GCSWConHandle& h, GCSWVarGeomHandle& circle,
                GCSWVarGeomHandle& ellipse);

            /**
             * @brief Create a 2D tangent ellipse/ellipse constraint.
             * @param h Return a handle to the constraint
             * @param ellipse1 Handle to the first ellipse
             * @param ellipse2 Handle to the second ellipse
             */
            Status Create2dTanEllEll(GCSWConHandle& h, GCSWVarGeomHandle& ellipse1,
                GCSWVarGeomHandle& ellipse2);

            /**
             * @brief Create a 2D tangent line/parabola constraint.
             * @param h Return a handle to the constraint
             * @param line Handle to the line
             * @param parabola Handle to the parabola
             */
            Status Create2dTanLnPar(
                GCSWConHandle& h, GCSWVarGeomHandle& line, GCSWVarGeomHandle& parabola);

            /**
             * @brief Create a 2D tangent circle/parabola constraint.
             * @param h Return a handle to the constraint
             * @param circle Handle to the circle
             * @param parabola Handle to the parabola
             */
            Status Create2dTanCirPar(GCSWConHandle& h, GCSWVarGeomHandle& circle,
                GCSWVarGeomHandle& parabola);

            /**
             * @brief Create a 2D tangent ellipse/parabola constraint.
             * @param h Return a handle to the constraint
             * @param ellipse Handle to the ellipse
             * @param parabola Handle to the parabola
             */
            Status Create2dTanEllPar(GCSWConHandle& h, GCSWVarGeomHandle& ellipse,
                GCSWVarGeomHandle& parabola);

            /**
             * @brief Create a 2D tangent parabola/parabola constraint.
             * @param h Return a handle to the constraint
             * @param parabola1 Handle to the first parabola
             * @param parabola2 Handle to the second parabola
             */
            Status Create2dTanParPar(GCSWConHandle& h, GCSWVarGeomHandle& parabola1,
                GCSWVarGeomHandle& parabola2);

            /**
             * @brief Create a 2D tangent line/b-spline constraint.
             * @param h Return a handle to the constraint
             * @param line Handle to the line
             * @param spline Handle to the b-spline curve
             */
            Status Create2dTanLnBSpline(
                GCSWConHandle& h, GCSWVarGeomHandle& line, GCSWVarGeomHandle& spline);

            /**
             * @brief Create a 2D tangent circle/b-spline constraint.
             * @param h Return a handle to the constraint
             * @param circle Handle to the circle
             * @param spline Handle to the b-spline curve
             */
            Status Create2dTanCirBSpline(
                GCSWConHandle& h, GCSWVarGeomHandle& circle, GCSWVarGeomHandle& spline);

            /**
             * @brief Create a 2D equal constraint between line/line, circle/circle or
             * ellipse/ellipse.
             * @param h Return a handle to the constraint
             * @param g1 Handle to the first geometry
             * @param g2 handle to the second geometry
             */
            Status Create2dEqual(
                GCSWConHandle& h, GCSWVarGeomHandle& g1, GCSWVarGeomHandle& g2);

            /**
             * @brief Create a 2D parallel constraint between line/line.
             * @param h Return a handle to the constraint
             * @param ln1 Handle to line1
             * @param ln2 Handle to line2
             */
            Status Create2dParallel(
                GCSWConHandle& h, GCSWVarGeomHandle& ln1, GCSWVarGeomHandle& ln2);

            /**
             * @brief Create a 2D perpendicular constraint between line and
             * line/circle/ellipse/parabola.
             * @param h Return a handle to the constraint
             * @param ln Handle to line
             * @param cur Handle to the other curve
             */
            Status Create2dPerpendicular(
                GCSWConHandle& h, GCSWVarGeomHandle& ln, GCSWVarGeomHandle& cur);

            /**
             * @brief Create a 2D point-point symmetric constraint with line.
             * @param h Return a handle to the constraint
             * @param pt1 Handle to point1
             * @param pt2 Handle to point2
             * @param axis Handle to the symmetric axis
             */
            Status Create2dSymmPtPtLn(GCSWConHandle& h, GCSWVarGeomHandle& pt1,
                GCSWVarGeomHandle& pt2, GCSWVarGeomHandle& axis);

            /**
             * @brief Create a 2D line-line symmetric constraint with line.
             * @param h Return a handle to the constraint
             * @param ln1 Handle to line1
             * @param ln2 Handle to line2
             * @param axis Handle to the symmetric axis
             */
            Status Create2dSymmLnLnLn(GCSWConHandle& h, GCSWVarGeomHandle& ln1,
                GCSWVarGeomHandle& ln2, GCSWVarGeomHandle& axis);

            /**
             * @brief Create a 2D circle-circle symmetric constraint with line.
             * @param h Return a handle to the constraint
             * @param cir1 Handle to circle1
             * @param cir2 Handle to circle2
             * @param axis Handle to the symmetric axis
             */
            Status Create2dSymmCirCirLn(GCSWConHandle& h, GCSWVarGeomHandle& cir1,
                GCSWVarGeomHandle& cir2, GCSWVarGeomHandle& axis);

            /**
             * @brief Create a 2D length constraint on the line.
             * @param h Return a handle to the constraint
             * @param ln Handle to the constrained line
             * @param d Length
             */
            Status Create2dLnLength(GCSWConHandle& h, GCSWVarGeomHandle& ln, double d);

            /**
             * @brief Create a 2D radius constraint on the circle.
             * @param h Return a handle to the constraint
             * @param cir Handle to the constrained circle
             * @param d Radius
             */
            Status Create2dCirRadius(GCSWConHandle& h, GCSWVarGeomHandle& cir, double d);

            /**
             * @brief Create a 2D major radius constraint on the ellipse
             * @param h Return a handle to the constraint
             * @param ell Handle to the constrained ellipse
             * @param d Major radius
             */
            Status Create2dEllMajorRadius(GCSWConHandle& h, GCSWVarGeomHandle& ell,
                double d);

            /**
             * @brief Create a 2D minor radius constraint on the ellipse
             * @param h Return a handle to the constraint
             * @param ell Handle to the constrained ellipse
             * @param d Minor radius
             */
            Status Create2dEllMinorRadius(GCSWConHandle& h, GCSWVarGeomHandle& ell,
                double d);

            /**
             * @brief Create a coincidence constraint between point and focus1 of ellipse
             * @param h Return a handle to the constraint
             * @param p Handle to the point
             * @param ell Handle to the ellipse
             */
            Status Create2dEllFocus1(GCSWConHandle& h, GCSWVarGeomHandle& p,
                GCSWVarGeomHandle& ell);

            /**
             * @brief Create a coincidence constraint between point and focus2 of ellipse
             * @param h Return a handle to the constraint
             * @param p Handle to the point
             * @param ell Handle to the ellipse
             */
            Status Create2dEllFocus2(GCSWConHandle& h, GCSWVarGeomHandle& p,
                GCSWVarGeomHandle& ell);

            /**
             * @brief Create a coincidence constraint between point and vertex1 of ellipse
             * @param h Return a handle to the constraint
             * @param p Handle to the point
             * @param ell Handle to the ellipse
             */
            Status Create2dEllVertex1(GCSWConHandle& h, GCSWVarGeomHandle& p,
                GCSWVarGeomHandle& ell);

            /**
             * @brief Create a coincidence constraint between point and vertex2 of ellipse
             * @param h Return a handle to the constraint
             * @param p Handle to the point
             * @param ell Handle to the ellipse
             */
            Status Create2dEllVertex2(GCSWConHandle& h, GCSWVarGeomHandle& p,
                GCSWVarGeomHandle& ell);

            /**
             * @brief Create a coincidence constraint between point and co-vertex1 of
             * ellipse
             * @param h Return a handle to the constraint
             * @param p Handle to the point
             * @param ell Handle to the ellipse
             */
            Status Create2dEllCoVertex1(GCSWConHandle& h, GCSWVarGeomHandle& p,
                GCSWVarGeomHandle& ell);

            /**
             * @brief Create a coincidence constraint between point and co-vertex2 of
             * ellipse
             * @param h Return a handle to the constraint
             * @param p Handle to the point
             * @param ell Handle to the ellipse
             */
            Status Create2dEllCoVertex2(GCSWConHandle& h, GCSWVarGeomHandle& p,
                GCSWVarGeomHandle& ell);

            /**
             * @brief Create a coincidence constraint between point and vertex of parabola
             * @param h Return a handle to the constraint
             * @param p Handle to the point
             * @param par Handle to the parabola
             */
            Status Create2dParabolaVertex(GCSWConHandle& h, GCSWVarGeomHandle& p,
                GCSWVarGeomHandle& par);

            /**
             * @brief Create a midpoint on the line segment/arc
             * @param h Return a handle to the constraint
             * @param p Handle to the point
             * @param cur Handle to the curve
             */
            Status Create2dMidPoint(GCSWConHandle& h, GCSWVarGeomHandle& p,
                GCSWVarGeomHandle& cur);

            /**
             * @brief Create a 2D horizontal constraint on the line.
             * @param h Return a handle to the constraint
             * @param ln Handle to the line
             */
            Status Create2dHorizontal(GCSWConHandle& h, GCSWVarGeomHandle& ln);

            /**
             * @brief Create a 2D horizontal distance constraint between the ends of the
             * line.
             * @param h Return a handle to the constraint
             * @param ln Handle to the line
             * @param d Distance
             */
            Status Create2dHorizontalDist(GCSWConHandle& h, GCSWVarGeomHandle& ln,
                double d);

            /**
             * @brief Create a 2D horizontal constraint between point/point.
             * @param h Return a handle to the constraint
             * @param pt1 Handle to point1
             * @param pt2 Handle to point2
             */
            Status Create2dHorizontal(GCSWConHandle& h, GCSWVarGeomHandle& pt1,
                GCSWVarGeomHandle& pt2);

            /**
             * @brief Create a 2D horizontal distance constraint between point/point.
             * @param h Return a handle to the constraint
             * @param pt1 Handle to point1
             * @param pt2 Handle to point2
             * @param d Distance: d=pt1.x-pt2.x
             */
            Status Create2dHorizontalDist(GCSWConHandle& h, GCSWVarGeomHandle& pt1,
                GCSWVarGeomHandle& pt2, double d);

            /**
             * @brief Create a 2D vertical constraint on the line.
             * @param h Return a handle to the constraint
             * @param ln Handle to the line
             */
            Status Create2dVertical(GCSWConHandle& h, GCSWVarGeomHandle& ln);

            /**
             * @brief Create a 2D vertical distance constraint between the ends of the
             * line.
             * @param h Return a handle to the constraint
             * @param ln Handle to the line
             * @param d Distance: d=pt1.y-pt2.y
             */
            Status Create2dVerticalDist(GCSWConHandle& h, GCSWVarGeomHandle& ln,
                double d);

            /**
             * @brief Create a 2D vertical constraint between point/point.
             * @param h Return a handle to the constraint
             * @param pt1 Handle to point1
             * @param pt2 Handle to point2
             */
            Status Create2dVertical(GCSWConHandle& h, GCSWVarGeomHandle& pt1,
                GCSWVarGeomHandle& pt2);

            /**
             * @brief Create a 2D vertical distance constraint between point/point.
             * @param h Return a handle to the constraint
             * @param pt1 Handle to point1
             * @param pt2 Handle to point2
             * @param d Distance: d=pt1.y-pt2.y
             */
            Status Create2dVerticalDist(GCSWConHandle& h, GCSWVarGeomHandle& pt1,
                GCSWVarGeomHandle& pt2, double d);

            /**
             * @brief Process draggging in 2d.
             * @param h Handle to the dragged geometry
             * @param oldPos Old position
             * @param newPos New position
             */
            Status PrioritizedDrag(
                GCSWVarGeomHandle& h, Point2d& oldPos, Point2d& newPos);

            /**
             * @brief General solve. Solve the constraint system.
             * @return The solve status of the system. Currently if solving correctly,
             * then return kSolved; otherwise, return kError.
             */
            Status Solve();

            /**
             * @brief Get geometry status
             * @param h Handle to the geometry
             * @return geometry status
             */
            GeometryConstrainedStatus GetGeometryStatus(const GCSWVarGeomHandle& h);

        private:
            std::unique_ptr<GCSSystem> gcsSystem;
        };
    } // namespace GCS
} // namespace AMCAX

#endif // AMCAX_GCS_H_
