#ifndef OPENGLSTATEWIDGET_HPP
#define OPENGLSTATEWIDGET_HPP

#include "ui_OpenGLStateWidget.h"
#include "model/gl/BlendState.hpp"
#include "model/gl/ClipOptions.hpp"
#include "model/gl/ColorOptions.hpp"
#include "model/gl/DepthOptions.hpp"
#include "model/gl/GeometryOptions.hpp"
#include "model/gl/Hints.hpp"
#include "model/gl/ImplementationInfo.hpp"
#include "model/gl/SampleOptions.hpp"
#include "model/gl/StencilOptions.hpp"

namespace balls {

struct OpenGLPointers;

class OpenGLStateWidget : public QWidget {
  Q_OBJECT

public:
  explicit OpenGLStateWidget(OpenGLPointers&, QWidget* = nullptr);

private /* fields */:
  Ui::OpenGLStateWidget ui;

  BlendState m_blendState;
  ClipOptions m_clipOptions;
  ColorOptions m_colorOptions;
  DepthOptions m_depthOptions;
  GeometryOptions m_geometryOptions;
  Hints m_hints;
  ImplementationInfo m_implementationInfo;
  SampleOptions m_sampleOptions;
  StencilOptions m_stencilOptions;
};
}

#endif // OPENGLSTATEWIDGET_HPP
