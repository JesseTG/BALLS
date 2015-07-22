#include "precompiled.hpp"
#include "util/Logging.hpp"

namespace balls {
namespace logs {

namespace app {
Q_LOGGING_CATEGORY(Name, "balls")
Q_LOGGING_CATEGORY(Version, "balls.version")

namespace project {
Q_LOGGING_CATEGORY(Name, "balls.project")
}
}

namespace system {
Q_LOGGING_CATEGORY(Name, "system")
Q_LOGGING_CATEGORY(Platform, "system.platform")
Q_LOGGING_CATEGORY(PID, "system.pid")

namespace session {
Q_LOGGING_CATEGORY(Name, "system.session")
Q_LOGGING_CATEGORY(ID, "system.session.id")
Q_LOGGING_CATEGORY(Key, "system.session.key")
}
}

namespace gl {
Q_LOGGING_CATEGORY(Name, "gl")
Q_LOGGING_CATEGORY(State, "gl.state")
Q_LOGGING_CATEGORY(Resource, "gl.resource")
Q_LOGGING_CATEGORY(Feature, "gl.feature")
Q_LOGGING_CATEGORY(Message, "gl.message")
Q_LOGGING_CATEGORY(Type, "gl.type")
}

namespace uniform {
Q_LOGGING_CATEGORY(Name, "uniform")
Q_LOGGING_CATEGORY(Value, "uniform.value")
Q_LOGGING_CATEGORY(Type, "uniform.type")
Q_LOGGING_CATEGORY(Env, "uniform.env")
}

namespace shader {
Q_LOGGING_CATEGORY(Name, "shader")
}


namespace ui {
Q_LOGGING_CATEGORY(Name, "ui")
}

}
}
