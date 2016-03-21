#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <memory>

#include <QObject>
#include <QOpenGLTexture>


Q_DECLARE_METATYPE(QOpenGLTexture::DepthStencilMode)
Q_DECLARE_METATYPE(QOpenGLTexture::Filter)
Q_DECLARE_METATYPE(QOpenGLTexture::Target)
Q_DECLARE_METATYPE(QOpenGLTexture::TextureFormat)
Q_DECLARE_METATYPE(GLuint)

namespace balls {

class AbstractTexture : public QObject {
  Q_OBJECT

  Q_PROPERTY(
      QColor borderColor READ borderColor WRITE borderColor STORED false FINAL)

  Q_PROPERTY(QOpenGLTexture::DepthStencilMode depthStencilMode READ
                 depthStencilMode WRITE depthStencilMode STORED false FINAL)
  // TODO: Register foreign enum types

  Q_PROPERTY(int faces READ faces STORED false FINAL)

  Q_PROPERTY(QOpenGLTexture::TextureFormat format READ format WRITE format
                 STORED false FINAL)

  Q_PROPERTY(QOpenGLTexture::Filter magnificationFilter READ magnificationFilter
                 WRITE magnificationFilter STORED false FINAL)

  Q_PROPERTY(QOpenGLTexture::Filter minificationFilter READ minificationFilter
                 WRITE minificationFilter STORED false FINAL)

  Q_PROPERTY(float maxAnisotropy READ maxAnisotropy WRITE maxAnisotropy
                 STORED false FINAL)

  Q_PROPERTY(float maxLod READ maxLod WRITE maxLod STORED false FINAL)

  Q_PROPERTY(float minLod READ minLod WRITE minLod STORED false FINAL)

  Q_PROPERTY(int samples READ samples WRITE samples STORED false FINAL)

  Q_PROPERTY(QOpenGLTexture::Target target READ target STORED false FINAL)

  Q_PROPERTY(GLuint id READ id STORED false FINAL)

  // TODO: Properties for mipmap levels
  // TODO: Swizzle masks
  // TODO: Wrap modes
public /* ctors/dtors */:
  virtual ~AbstractTexture() {}

public /* getters/setters */:
  QColor borderColor() const noexcept { return texture_->borderColor(); }

  void borderColor(const QColor &color) noexcept {
    texture_->setBorderColor(color);
  }

  QOpenGLTexture::DepthStencilMode depthStencilMode() const noexcept {
    return texture_->depthStencilMode();
  }

  void depthStencilMode(QOpenGLTexture::DepthStencilMode mode) noexcept {
    texture_->setDepthStencilMode(mode);
  }

  int faces() const noexcept { return texture_->faces(); }

  QOpenGLTexture::TextureFormat format() const noexcept {
    return texture_->format();
  }

  void format(QOpenGLTexture::TextureFormat format) noexcept {
    texture_->setFormat(format);
  }

  QOpenGLTexture::Filter magnificationFilter() const noexcept {
    return texture_->magnificationFilter();
  }

  void magnificationFilter(QOpenGLTexture::Filter filter) noexcept {
    texture_->setMagnificationFilter(filter);
  }

  QOpenGLTexture::Filter minificationFilter() const noexcept {
    return texture_->minificationFilter();
  }

  void minificationFilter(QOpenGLTexture::Filter filter) noexcept {
    texture_->setMinificationFilter(filter);
  }

  float maxAnisotropy() const noexcept { return texture_->maximumAnisotropy(); }

  void maxAnisotropy(float anisotropy) noexcept {
    texture_->setMaximumAnisotropy(anisotropy);
  }

  float maxLod() const noexcept { return texture_->maximumLevelOfDetail(); }

  void maxLod(float lod) noexcept { texture_->setMaximumLevelOfDetail(lod); }

  float minLod() const noexcept { return texture_->minimumLevelOfDetail(); }

  void minLod(float lod) noexcept { texture_->setMinimumLevelOfDetail(lod); }

  int samples() const noexcept { return texture_->samples(); }

  void samples(int samples) noexcept { texture_->setSamples(samples); }

  QOpenGLTexture::Target target() const noexcept { return texture_->target(); }

  GLuint id() const noexcept { return texture_->textureId(); }

signals:

public slots:

protected:
  std::unique_ptr<QOpenGLTexture> texture_;
};
}

Q_DECLARE_METATYPE(balls::AbstractTexture*)
#endif // TEXTURE_HPP
