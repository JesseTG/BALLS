#include "precompiled.hpp"
#include "exception/FileException.hpp"

#include <QMetaEnum>

namespace balls {

FileException::FileException(const QFileDevice& file) noexcept
  : FileException(&file) {
}

FileException::FileException(const QFileDevice* file) noexcept
  : std::exception() {
  if (file == nullptr) {
    _error = QFileDevice::FileError::UnspecifiedError;
    _errorMsg = "Invalid file pointer";
    _fullMsg = _errorMsg;
  } else {
    _error = file->error();
    _errorMsg = file->errorString();
    _fullMsg =
      QString("%1: %2 (%3)").arg(_errorMsg).arg(file->fileName()).arg(_error);
  }
}
}
