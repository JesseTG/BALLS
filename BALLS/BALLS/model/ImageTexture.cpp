#include "precompiled.hpp"

#include "ImageTexture.hpp"

namespace balls {

ImageTexture::ImageTexture(QImage& image) : m_image(image) {
  texture_.reset(new QOpenGLTexture(image));
}
}
