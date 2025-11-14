#ifndef POWERFC_STANDARD_CURVETOOL_H
#define POWERFC_STANDARD_CURVETOOL_H
#pragma once
#include <memory>

namespace AMCAX {
    class Geom3Curve;
    class TopoEdge;
}

namespace standard{
    class CurveTool{
        public:
        std::shared_ptr<AMCAX::Geom3Curve> GetCurve3(AMCAX::TopoEdge const& edge);
    };
}

#endif