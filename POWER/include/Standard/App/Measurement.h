#ifndef POWERFC_STANDARD_KERNEL_MEASUREMENT_H
#define POWERFC_STANDARD_KERNEL_MEASUREMENT_H
#pragma once
#include <topology/TopoShape.hpp>
#include <common/PointT.hpp>
#include <common/AxisT.hpp>
#include <vector>
#include <Standard/StandardGlobal.h>

namespace standard {
    class Standard_API Measurement{
    public:
        Measurement() = default;
        ~Measurement() = default;
        void GetPoints(std::vector<AMCAX::TopoShape> const& selected_shapes, std::vector<AMCAX::Point3>& points);
        void GetMinimumBall(std::vector<AMCAX::TopoShape> const& selected_shapes, AMCAX::Point3* center, double* radius);
        void GetMinimumCylinder(std::vector<AMCAX::TopoShape> const& selected_shapes, AMCAX::Axis3 const& axis, double* radius, double* height);
        void GetMinimumCylinder(std::vector<AMCAX::TopoShape> const& selected_shapes, AMCAX::Direction3 const& axis, AMCAX::Point3* center, double* radius, double* height);
    };
}

#endif