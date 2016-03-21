#ifndef IMAGETEXTURE_HPP
#define IMAGETEXTURE_HPP

#include <QImage>
#include "Texture.hpp"

namespace balls {

class ImageTexture : public AbstractTexture {
  Q_OBJECT

public:
  ImageTexture(QImage& image);

private:
  QImage m_image;
};
}

Q_DECLARE_METATYPE(balls::ImageTexture*)
#endif // IMAGETEXTURE_HPP
