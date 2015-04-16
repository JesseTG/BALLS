#ifndef PRECOMPILED_HPP
#define PRECOMPILED_HPP

// Standard Library
#include <array>
#include <cmath>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

// Qt Core
#include <QtCore/Qt>
#include <QtCore/QtGlobal>
#include <qmath.h>
#include <QtCore/QDebug>
#include <QtCore/QMetaType>
#include <QtCore/QPoint>
#include <QtCore/QPointF>
#include <QtCore/QPointer>
#include <QtCore/QSize>
#include <QtCore/QSizeF>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtCore/QVector>

// Qt GUI
#include <QtGui/QColor>
#include <QtGui/QGenericMatrix>
#include <QtGui/QMatrix>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>

// Defines
#ifndef M_PI
Q_CONSTEXPR float M_PI = 3.141592653589793f;
#endif

#endif // PRECOMPILED_HPP
