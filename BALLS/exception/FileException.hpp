#ifndef FILEEXCEPTION_HPP
#define FILEEXCEPTION_HPP

#include <stdexcept>
#include <QtCore/QFileDevice>
#include <QtCore/QString>

namespace balls {

class Q_DECL_DEPRECATED FileException : public std::exception {
public:
  FileException(const QFileDevice&) noexcept;
  FileException(const QFileDevice*) noexcept;
  const char* what() const noexcept override {
    return qPrintable(_errorMsg);
  }

  const QString& fullMessage() const noexcept {
    return _fullMsg;
  }

  QFileDevice::FileError error() const noexcept { return _error; }
private:
  QFileDevice::FileError _error;
  QString _errorMsg;
  QString _fullMsg;

};
}

#endif // FILEEXCEPTION_HPP
