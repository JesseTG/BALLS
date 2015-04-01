#ifndef GLSLHIGHLIGHTER_HPP
#define GLSLHIGHLIGHTER_HPP

#include <QSyntaxHighlighter>

class QString;

namespace balls {
namespace ui {

class GLSLHighlighter : public QSyntaxHighlighter {
  Q_OBJECT
public:
  explicit GLSLHighlighter(QObject* parent = 0);

  void highlightBlock(const QString&) override;

signals:

public slots:
};
}
}

#endif // GLSLHIGHLIGHTER_HPP
