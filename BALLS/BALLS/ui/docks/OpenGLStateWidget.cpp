#include "precompiled.hpp"
#include "ui/docks/OpenGLStateWidget.hpp"

#include "gl/OpenGLPointers.hpp"

namespace balls {

OpenGLStateWidget::OpenGLStateWidget(OpenGLPointers& gl, QWidget* parent)
  : QWidget(parent),
    m_blendState(gl),
    m_clipOptions(gl),
    m_colorOptions(gl),
    m_depthOptions(gl),
    m_geometryOptions(gl),
    m_hints(gl),
    m_implementationInfo(gl),
    m_sampleOptions(gl),
    m_stencilOptions(gl) {
  ui.setupUi(this);

  ui.openGlProperties->addObject(&m_blendState);
  ui.openGlProperties->addObject(&m_clipOptions);
  ui.openGlProperties->addObject(&m_colorOptions);
  ui.openGlProperties->addObject(&m_depthOptions);
  ui.openGlProperties->addObject(&m_geometryOptions);
  ui.openGlProperties->addObject(&m_hints);
  ui.openGlProperties->addObject(&m_implementationInfo);
  ui.openGlProperties->addObject(&m_sampleOptions);
  ui.openGlProperties->addObject(&m_stencilOptions);
}
}
