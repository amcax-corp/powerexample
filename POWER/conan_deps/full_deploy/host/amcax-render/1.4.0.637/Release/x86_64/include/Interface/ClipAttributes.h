/// @file      ClipAttributes.h
/// @brief     Point Cloud Clipping Attributes
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef ClipAttributes_h
#define ClipAttributes_h

#include "Macros.h"
#include "Constants.h"

namespace AMCAXRender
{
    /// @brief	ClipAttributes Class
    class AMCAX_RENDER_API ClipAttributes
    {
    public:
        enum Quality
        {
            Fast,       // Fast Clipping
            Accurate    // Accurate Clipping
        };

        ClipAttributes();
        ~ClipAttributes();

        /// @brief Set Clipping Quality
        /// @param[in] quality_ Quality attribute
        void SetQuality(Quality quality_);

        /// @brief Set Clipping Plane 1
        /// @param[in] plane1Status_ Clipping Plane 1 Status
        void SetPlane1Status(bool plane1Status_);

        /// @brief Set Clipping Plane 2
        /// @param[in] plane2Status_ Clipping Plane 2 Status
        void SetPlane2Status(bool plane2Status_);

        /// @brief Set Clipping Plane 3
        /// @param[in] plane3Status_ Clipping Plane 3 Status
        void SetPlane3Status(bool plane3Status_);

        /// @brief Set Origin Position of Clipping Plane 1
        /// @param[in] plane1Origin_ Origin Position double [3]
        void SetPlane1Origin(const double* plane1Origin_);

        /// @brief Set Origin Position of Clipping Plane 2
        /// @param[in] plane2Origin_ Origin Position double [3]
        void SetPlane2Origin(const double* plane2Origin_);

        /// @brief Set Origin Position of Clipping Plane 3
        /// @param[in] plane3Origin_ Origin Position double [3]
        void SetPlane3Origin(const double* plane3Origin_);

        /// @brief Set Direction of Clipping Plane 1
        /// @param[in] plane1Normal_ Direction double [3]
        void SetPlane1Normal(const double* plane1Normal_);

        /// @brief Set Direction of Clipping Plane 2
        /// @param[in] plane2Normal_ Direction double [3]
        void SetPlane2Normal(const double* plane2Normal_);

        /// @brief Set Direction of Clipping Plane 3
        /// @param[in] plane3Normal_ Direction double [3]
        void SetPlane3Normal(const double* plane3Normal_);

        /// @brief Set Clipping Inverse
        /// @param[in] planeInverse_ Inverse
        void SetPlaneInverse(bool planeInverse_);

        /// @brief Get Clipping Quality
        /// @return Type
        /// @see Quality
        Quality      GetQuality() const;

        /// @brief Get Clipping Plane 1 Status
        /// @return Status
        bool         GetPlane1Status() const;

        /// @brief Get Clipping Plane 2 Status
        /// @return Status
        bool         GetPlane2Status() const;

        /// @brief Get Clipping Plane 3 Status
        /// @return Status
        bool         GetPlane3Status() const;

        /// @brief Get Origin Position of Clipping Plane 1
        /// @return Origin Position double [3]
        const double* GetPlane1Origin() const;
        double* GetPlane1Origin();

        /// @brief Get Origin Position of Clipping Plane 2
        /// @return Origin Position double [3]
        const double* GetPlane2Origin() const;
        double* GetPlane2Origin();

        /// @brief Get Origin Position of Clipping Plane 3
        /// @return Origin Position double [3]
        const double* GetPlane3Origin() const;
        double* GetPlane3Origin();

        /// @brief Get Direction of Clipping Plane 1
        /// @return Direction double [3]
        const double* GetPlane1Normal() const;
        double* GetPlane1Normal();

        /// @brief Get Direction of Clipping Plane 2
        /// @return Direction double [3]
        const double* GetPlane2Normal() const;
        double* GetPlane2Normal();

        /// @brief Get Direction of Clipping Plane 3
        /// @return Direction double [3]
        const double* GetPlane3Normal() const;
        double* GetPlane3Normal();

        /// @brief Get Clipping Inverse Status
        /// @return Status
        bool         GetPlaneInverse() const;
    private:
        int    quality;
        bool   plane1Status;
        bool   plane2Status;
        bool   plane3Status;
        double plane1Origin[3];
        double plane2Origin[3];
        double plane3Origin[3];
        double plane1Normal[3];
        double plane2Normal[3];
        double plane3Normal[3];
        bool   planeInverse;
    private:
        void Init();
        void Copy(const ClipAttributes& obj);

    };
}

#endif