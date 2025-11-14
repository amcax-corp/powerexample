#ifndef POWERUI_GLOBAL_H
#define POWERUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(POWER_WIDGETS_EXPORT)
#define PW_API Q_DECL_EXPORT
#else
#define PW_API Q_DECL_IMPORT
#endif

#endif // POWERUI_GLOBAL_H
