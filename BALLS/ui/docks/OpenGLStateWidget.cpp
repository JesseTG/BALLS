#include "precompiled.hpp"
#include "ui/docks/OpenGLStateWidget.hpp"

#include "Constants.hpp"
#include "model/gl/BlendState.hpp"
#include "model/gl/ClipOptions.hpp"
#include "model/gl/ColorOptions.hpp"
#include "model/gl/DepthOptions.hpp"
#include "model/gl/GeometryOptions.hpp"
#include "model/gl/Hints.hpp"
#include "model/gl/ImplementationInfo.hpp"
#include "model/gl/SampleOptions.hpp"
#include "model/gl/StencilOptions.hpp"
#include "shader/ShaderUniform.hpp"

namespace balls {

OpenGLStateWidget::OpenGLStateWidget(QWidget* parent)
  : QWidget(parent),
    m_blendState(nullptr),
    m_clipOptions(nullptr),
    m_colorOptions(nullptr),
    m_depthOptions(nullptr),
    m_geometryOptions(nullptr),
    m_hints(nullptr),
    m_implementationInfo(nullptr),
    m_sampleOptions(nullptr),
    m_stencilOptions(nullptr) {
  ui.setupUi(this);
}


void OpenGLStateWidget::setOpenGLPointers(const OpenGLPointers& gl) noexcept {
  m_gl = gl;

  m_blendState = new BlendState(m_gl, this);
  m_clipOptions = new ClipOptions(m_gl, this);
  m_colorOptions = new ColorOptions(m_gl, this);
  m_depthOptions = new DepthOptions(m_gl, this);
  m_geometryOptions = new GeometryOptions(m_gl, this);
  m_hints = new Hints(m_gl, this);
  m_implementationInfo = new ImplementationInfo(m_gl, this);
  m_sampleOptions = new SampleOptions(m_gl, this);
  m_stencilOptions = new StencilOptions(m_gl, this);

  ui.openGlProperties->setNameFilter(constants::regex::NAME_FILTER);
  ui.openGlProperties->registerCustomPropertyCB(shader::createShaderProperty);

  m_blendState->setObjectName(tr("Blending"));
  m_clipOptions->setObjectName(tr("Clipping"));
  m_colorOptions->setObjectName(tr("Colors"));
  m_depthOptions->setObjectName(tr("Depth"));
  m_geometryOptions->setObjectName(tr("Geometry"));
  m_hints->setObjectName(tr("Hints"));
  m_implementationInfo->setObjectName(tr("Implementation"));
  m_sampleOptions->setObjectName(tr("Sampling"));
  m_stencilOptions->setObjectName(tr("Stenciling"));

  ui.openGlProperties->addObject(m_blendState);
  ui.openGlProperties->addObject(m_clipOptions);
  ui.openGlProperties->addObject(m_colorOptions);
  ui.openGlProperties->addObject(m_depthOptions);
  ui.openGlProperties->addObject(m_geometryOptions);
  ui.openGlProperties->addObject(m_hints);
  ui.openGlProperties->addObject(m_implementationInfo);
  ui.openGlProperties->addObject(m_sampleOptions);
  ui.openGlProperties->addObject(m_stencilOptions);
}
}
