#ifndef JSONEXCEPTION_HPP
#define JSONEXCEPTION_HPP

#include <QtCore/QCoreApplication>
#include <QtCore/QJsonParseError>
#include <stdexcept>

namespace balls {

class JsonException : public std::exception
{
  Q_DECLARE_TR_FUNCTIONS(JsonException)

public:
  JsonException(const QJsonParseError&) noexcept;

  const char* what() const noexcept override {
    return qPrintable(_error.errorString());
  }

  const QString& fullMessage() const noexcept {
    return _fullMsg;
  }

  const QJsonParseError& error() const noexcept { return _error; }
private:
  QJsonParseError _error;
  QString _fullMsg;
};

}
#endif // JSONEXCEPTION_HPP
