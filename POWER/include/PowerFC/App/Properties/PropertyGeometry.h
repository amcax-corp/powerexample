#ifndef POWERFC_APP_PROPERTIES_PROPERTYGEOMETRY_H_
#define POWERFC_APP_PROPERTIES_PROPERTYGEOMETRY_H_
#pragma once

#include <App/Property.h>
#include <Base/Matrix.h>
#include <Base/BoundBox.h>

namespace app {

/**
 * @brief 几何属性的基类.
 * 
 */
class PFC_APP_API PropertyGeometry : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

public:
    PropertyGeometry()=default;
    ~PropertyGeometry() override=default;

    /** @name Modification */
    //@{
    /// Set the placement of the geometry
    virtual void SetTransformation(const base::Matrix4D& transformation) = 0;
    /// Get the placement of the geometry
    virtual base::Matrix4D GetTransformation() const = 0;

    /// Applies a transformation on the real geometric data type
    virtual void TransformGeometry(const base::Matrix4D &matrix) = 0;
    /// Retrieve bounding box information
    virtual base::BoundBox3d GetBoundingBox() const = 0;
    //@}
};

}



#endif