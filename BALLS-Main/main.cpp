#include "precompiled.hpp"

#include <QApplication>
#include <generator/generator.hpp>

#include "Constants.hpp"

#include "ui/BallsWindow.hpp"
#include "util/Logging.hpp"
#include "util/MetaTypeConverters.hpp"

using FormatOption = QSurfaceFormat::FormatOption;
using FormatOptions = QSurfaceFormat::FormatOptions;
using OpenGLContextProfile = QSurfaceFormat::OpenGLContextProfile;
using RenderableType = QSurfaceFormat::RenderableType;
using SwapBehavior = QSurfaceFormat::SwapBehavior;
using UsagePattern = QOpenGLBuffer::UsagePattern;

constexpr FormatOption FORMAT_OPTION =
#ifdef DEBUG
  FormatOption::DebugContext;
#else
  FormatOption::StereoBuffers;
#endif
constexpr OpenGLContextProfile PROFILE = OpenGLContextProfile::CoreProfile;
constexpr RenderableType RENDER_TYPE = RenderableType::OpenGL;
constexpr SwapBehavior SWAP_TYPE = SwapBehavior::DefaultSwapBehavior;
constexpr int SAMPLES = 4;
constexpr int DEPTH_BUFFER_BITS = 8;

constexpr FormatOptions
  FLAGS(FORMAT_OPTION | RENDER_TYPE | PROFILE | SWAP_TYPE);

int main(int argc, char* argv[]) {
  using namespace balls::logs;

  QSurfaceFormat format;
#ifdef Q_OS_LINUX
  format.setOption(FORMAT_OPTION);
  format.setRenderableType(RENDER_TYPE);
  format.setSwapBehavior(SWAP_TYPE);
  format.setProfile(PROFILE);
  format.setVersion(4, 5);
  format.setSamples(SAMPLES);
  format.setDepthBufferSize(DEPTH_BUFFER_BITS);
#elif defined(Q_OS_MAC)
  format.setVersion(4, 1);
  format.setAlphaBufferSize(8);
  format.setRedBufferSize(8);
  format.setBlueBufferSize(8);
  format.setGreenBufferSize(8);
  format.setDepthBufferSize(16);
  format.setSamples(0);
  format.setStencilBufferSize(8);
  format.setProfile(PROFILE);
  format.setStereo(false);
  format.setSwapBehavior(SwapBehavior::DoubleBuffer);
  format.setRenderableType(RENDER_TYPE);
#endif

  QSurfaceFormat::setDefaultFormat(format);

  balls::registerMetaTypeConverters();
  balls::util::types::init();

  Q_ASSERT(balls::util::types::info.size() > 0);
  // TODO: Output all logging categories, and whether or not they're enabled
  QApplication balls(argc, argv);

  balls.setApplicationName(constants::meta::APP);
  balls.setOrganizationName(constants::meta::AUTHOR);
  balls.setOrganizationDomain(constants::meta::AUTHOR_DOMAIN);
  balls.setApplicationVersion("0.0");

#ifdef DEBUG
  qDebug() << "Running a debug build of" << constants::meta::APP;
#endif

  qCDebug(app::Version) << balls.applicationVersion();
  qCDebug(system::session::Key) << balls.sessionKey();
  qCDebug(system::session::ID) << balls.sessionId();
  qCDebug(system::Platform) << balls.platformName();
  qCDebug(system::PID) << balls.applicationPid();

  balls::BallsWindow w;
  w.show();
  return balls.exec();
}
