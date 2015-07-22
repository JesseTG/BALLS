#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <QtCore/QLoggingCategory>

namespace balls {
namespace logs {

namespace app {
Q_DECLARE_LOGGING_CATEGORY(Name)
Q_DECLARE_LOGGING_CATEGORY(Version)

namespace project {
Q_DECLARE_LOGGING_CATEGORY(Name)
}
}

namespace system {
Q_DECLARE_LOGGING_CATEGORY(Name)
Q_DECLARE_LOGGING_CATEGORY(Platform)
Q_DECLARE_LOGGING_CATEGORY(PID)

namespace session {
Q_DECLARE_LOGGING_CATEGORY(Name)
Q_DECLARE_LOGGING_CATEGORY(ID)
Q_DECLARE_LOGGING_CATEGORY(Key)
}
}

namespace gl {
Q_DECLARE_LOGGING_CATEGORY(Name)
Q_DECLARE_LOGGING_CATEGORY(State)
Q_DECLARE_LOGGING_CATEGORY(Resource)
Q_DECLARE_LOGGING_CATEGORY(Feature)
Q_DECLARE_LOGGING_CATEGORY(Message)
Q_DECLARE_LOGGING_CATEGORY(Type)
}

namespace uniform {
Q_DECLARE_LOGGING_CATEGORY(Name)
Q_DECLARE_LOGGING_CATEGORY(Value)
Q_DECLARE_LOGGING_CATEGORY(Type)
Q_DECLARE_LOGGING_CATEGORY(Env)
}

namespace shader {
Q_DECLARE_LOGGING_CATEGORY(Name)
}



namespace ui {
Q_DECLARE_LOGGING_CATEGORY(Name)
}

}
}

#endif // LOGGING_HPP