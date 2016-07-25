#include "precompiled.hpp"
#include "exception/JsonException.hpp"

namespace balls {

JsonException::JsonException(const QJsonParseError& error) noexcept :
_error(error),
       _fullMsg(QString(tr("JSON parse error at offset %2: %1"))
                .arg(error.errorString())
.arg(error.offset)) {}
}
