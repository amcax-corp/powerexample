#pragma once

#include <QObject>
#include <Widgets/PowerWidgetsConfig.h>

namespace PowerUI
{
    Q_NAMESPACE
    class PW_API ShapeSelection
    {
        Q_GADGET
    public:
        enum StepStatus
        {

            Required,
            Optional,
            Satisfied
        };
        Q_ENUM(StepStatus)

        enum SelectMode
        {
            Single,
            Multiple
        };
        Q_ENUM(SelectMode)
    };
}