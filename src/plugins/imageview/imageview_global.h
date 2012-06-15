#ifndef HELLOWORLD_GLOBAL_H
#define HELLOWORLD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HELLOWORLD_LIBRARY)
#  define IMAGEVIEW_EXPORT Q_DECL_EXPORT
#else
#  define IMAGEVIEW_EXPORT Q_DECL_IMPORT
#endif

#endif // HELLOWORLD_GLOBAL_H
