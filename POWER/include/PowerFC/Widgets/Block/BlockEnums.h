#ifndef BLOCKENUMS_H
#define BLOCKENUMS_H

#include "PFCGlobal.h"

#include <qnamespace.h>
namespace gui {
enum class BasicPickFilter;
}
inline namespace BlockEnum
{
    enum class PickType
    {
        Unknown = 1 << 4,
        Point = 1 << 0,
        Edge = 1 << 1,
        Face = 1 << 2,
        Body = 1 << 3,

        Point_Edge = Point | Edge,
        Point_Face = Point | Face,
        Edge_Face = Edge | Face,
        AllGeom = Point | Edge | Face,

        Body_Point = Body | Point,
        Body_Edge = Body | Edge,
        Body_Face = Body | Face,
        Body_Point_Edge = Body | Point_Edge,
        Body_Edge_Face = Body | Edge_Face,
        Body_Point_Face = Body | Point_Face,

        All = Body | AllGeom,

        // ToolPath = 1 << 4,
    };
    Q_DECLARE_FLAGS(PickTypes, PickType);

    gui::BasicPickFilter ConvertPickType(PickTypes);
};


#endif //BLOCKENUMS_H
