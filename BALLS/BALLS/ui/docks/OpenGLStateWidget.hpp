#ifndef OPENGLSTATEWIDGET_HPP
#define OPENGLSTATEWIDGET_HPP

#include "ui_OpenGLStateWidget.h"

#include "gl/OpenGLPointers.hpp"

namespace balls {

class BlendState;
class ClipOptions;
class ColorOptions;
class DepthOptions;
class GeometryOptions;
class Hints;
class ImplementationInfo;
class SampleOptions;
class StencilOptions;

class OpenGLStateWidget : public QWidget {
  Q_OBJECT

public:
  explicit OpenGLStateWidget(QWidget* = nullptr);

public slots:
  void setOpenGLPointers(const OpenGLPointers&) noexcept;

private /* fields */:
  Ui::OpenGLStateWidget ui;

  OpenGLPointers m_gl;

  BlendState* m_blendState;
  ClipOptions* m_clipOptions;
  ColorOptions* m_colorOptions;
  DepthOptions* m_depthOptions;
  GeometryOptions* m_geometryOptions;
  Hints* m_hints;
  ImplementationInfo* m_implementationInfo;
  SampleOptions* m_sampleOptions;
  StencilOptions* m_stencilOptions;
};
}

#endif // OPENGLSTATEWIDGET_HPP
