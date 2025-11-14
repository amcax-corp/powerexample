/// @file      CameraManage.h
/// @brief     Camera Management Class
/// @details   Used to manage camera property settings
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef CameraManage_h
#define CameraManage_h

#include "Macros.h"
#include "Constants.h"

namespace AMCAXRender {

    /// @brief Camera Management Module
    class AMCAX_RENDER_API CameraManage {
    public:
        virtual ~CameraManage() {};
    public:
        /// @brief Set Camera Mode
        /// @details Typically used for switching between 3D and 2D camera modes
        /// @param mode Camera mode
        virtual void SetCameraMode(CameraMode mode) = 0;

        /// @brief Get Camera Mode
        virtual void GetCameraMode(CameraMode& mode) = 0;

        /// @brief Set Sketch Coordinate System
        /// @param center Center point of the coordinate system
        /// @param directionZ Direction of the Z axis
        /// @param directionX Direction of the X axis
        virtual void SetSketchMode(double center[3], double directionZ[3], double directionX[3]) = 0;
        
        /// @brief Set Parallel Projection Flag
        /// @param flag Parallel projection flag, e.g., true: enable, false: disable
        virtual void SetParallelProjection(bool flag) = 0;

        /// @brief Get Parallel Projection Flag
        virtual void GetParallelProjection(bool& flag) = 0;

        /// @brief Reset Camera View
        virtual void ResetCamera() = 0;

        /// @brief Reset Camera View for Entity
        /// @param[in] EntityId
        virtual void ResetCamera(EntityId id) = 0;

        /// @brief Set Camera Position
        /// @param x X-axis coordinate
        /// @param y Y-axis coordinate
        /// @param z Z-axis coordinate
        virtual void SetPosition(double x, double y, double z) = 0;
        
        /// @brief Get Camera Position
        virtual void GetPosition(double& x, double& y, double& z) = 0;

        /// @brief Set Camera Focal Point
        /// @param x X-axis coordinate
        /// @param y Y-axis coordinate
        /// @param z Z-axis coordinate
        virtual void SetFocalPoint(double x, double y, double z) = 0;

        /// @brief Get Camera Focal Point
        virtual void GetFocalPoint(double& x, double& y, double& z) = 0;


        /// @brief Set the scaling used for a parallel projection
        /// @param scale Scale
        virtual void SetParallelScale(double scale) = 0;

        /// @brief Get the scaling used for a parallel projection
        virtual double GetParallelScale() = 0;

        /// @brief Set the camera view angle, which is the angular height of the camera view measured in degrees
        /// @param angle Angle
        virtual void SetViewAngle(double angle) = 0;

        /// @brief Get the camera view angle, which is the angular height of the camera view measured in degrees
        virtual double GetViewAngle() = 0;

        /// @brief Set Camera View Up Direction
        /// @details Set the viewUp vector, default is (0,0,1)
        /// @param vx X-axis coordinate
        /// @param vy Y-axis coordinate
        /// @param vz Z-axis coordinate
        virtual void SetViewUp(double vx, double vy, double vz) = 0;
        
        /// @brief Get Camera View Up Direction
        virtual void GetViewUp(double& vx, double& vy, double& vz) = 0;

        /// @brief Set Camera Azimuth Angle
        virtual void Azimuth(double angle) = 0;

        /// @brief Set Camera Elevation Angle
        virtual void Elevation(double angle) = 0;

        /// @brief Set Clipping Range
        /// @param dNear Near clipping plane
        /// @param dFar Far clipping plane
        virtual void SetClippingRange(double dNear, double dFar) = 0;

        /// @brief Get Clipping Range
        /// @param dNear Near clipping plane
        /// @param dFar Far clipping plane
        virtual void GetClippingRange(double& dNear, double& dFar) = 0;

        /// @brief Quick Camera View Switch
        /// @param type View type, e.g., (UP, DOWN, ...)
        virtual void SetCameraView(CameraView type) = 0;

        /// @brief Automatically Reset Clipping Range
        virtual void ResetClippingRange() = 0;

        /// @brief Camera Look At Position
        /// @param[in] pos Camera look at position
        /// @param[in] direction Direction vector of the camera look at position
        /// @param[in] length Distance from the camera to the target position
        virtual void LookAt(double pos[3], double direction[3], double length) = 0;

        /// @brief Computes the bounding box 
        /// @param bound Bounding box data  
        virtual void ComputeBounds(double bound[6]) = 0;
    };
}
#endif