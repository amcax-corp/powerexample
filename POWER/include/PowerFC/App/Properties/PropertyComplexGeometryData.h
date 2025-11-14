#ifndef POWERFC_APP_PROPERTIES_PROPERTYCOMPLEXGEOMETRYDATA_H_
#define POWERFC_APP_PROPERTIES_PROPERTYCOMPLEXGEOMETRYDATA_H_

#pragma once
#include <App/Properties/PropertyGeometry.h>


namespace data {

    class ComplexGeometryData;
}


namespace app {

class PFC_APP_API PropertyComplexGeometryData : public PropertyGeometry {

    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

public:
    PropertyComplexGeometryData() = default;
    ~PropertyComplexGeometryData() override = default;

    void TransformGeometry(const base::Matrix4D &) override = 0;

    virtual const data::ComplexGeometryData* GetComplexGeometryData() const = 0;
    base::BoundBox3d GetBoundingBox() const override = 0;


    virtual std::string GetElementMapVersion(bool restored = false) const;

    virtual bool CheckElementMapVersion(std::string_view version) const;

    void AfterRestore() override;

};


}

#endif