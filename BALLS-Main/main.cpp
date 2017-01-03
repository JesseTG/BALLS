#include "precompiled.hpp"

#include <QApplication>
#include <generator/generator.hpp>

#include "Constants.hpp"

#include "ui/BallsWindow.hpp"
#include "util/Logging.hpp"
#include "util/MetaTypeConverters.hpp"

int main(int argc, char* argv[]) {
  using namespace balls::logs;

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
