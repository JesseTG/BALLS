#ifndef IMAGETEXTURE_HPP
#define IMAGETEXTURE_HPP

#include "Texture.hpp"

#include <QImage>

namespace balls {

class ImageTexture : public AbstractTexture {
  Q_OBJECT

public:
  explicit ImageTexture(QImage& image);

private:
  QImage m_image;
};
}

Q_DECLARE_METATYPE(balls::ImageTexture*)

#endif // IMAGETEXTURE_HPP
