#include "ui/GLSLHighlighter.hpp"

#include <QColor>
#include <QDebug>
#include <QFont>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QString>
#include <QTextCharFormat>

#include "ui/GLSLPatterns.hpp"

namespace balls {
namespace ui {

QTextCharFormat _makeFormat(const QFont::Weight, const QColor&) noexcept;

const QTextCharFormat TYPE_FORMAT =
 _makeFormat(QFont::Weight::Bold, QColor(167, 61, 164));

const QRegularExpression KEYWORD_REGEX("\\b(?:"
                                       ""
                                       ")\\b",
                                       QRegularExpression::OptimizeOnFirstUsageOption);

const QTextCharFormat KEYWORD_FORMAT =
 _makeFormat(QFont::Weight::Normal, QColor(157, 142, 50));

const QTextCharFormat PREPROCESSOR_FORMAT =
 _makeFormat(QFont::Weight::Normal, QColor(22, 140, 99));

const QTextCharFormat COMMENT_FORMAT =
 _makeFormat(QFont::Weight::Normal, QColor(141, 141, 141));

GLSLHighlighter::GLSLHighlighter(QObject* parent)
    : QSyntaxHighlighter(parent) {}

void GLSLHighlighter::highlightBlock(const QString& text) {
  typedef QRegularExpressionMatchIterator Matches;
  typedef QRegularExpressionMatch Match;

  auto highlight = [this](Matches& m, const QTextCharFormat& f) {
    // Small convenience to shorten this method a bit
    while (m.hasNext()) {
      Match match = m.next();
      this->setFormat(match.capturedStart(), match.capturedLength(), f);
    }
  };

  Matches preprocessor = patterns::PREPROCESSOR.globalMatch(text);
  if (preprocessor.hasNext()) {
    highlight(preprocessor, PREPROCESSOR_FORMAT);
    return;
  }

  Matches comment = patterns::COMMENT.globalMatch(text);
  if (comment.hasNext()) {
    highlight(comment, COMMENT_FORMAT);
    return;
  }

  Matches type = patterns::TYPE.globalMatch(text);
  if (type.hasNext()) {
    while (type.hasNext()) {
      QRegularExpressionMatch match = type.next();

      if (lists::TYPE.contains(match.captured())) {
        this->setFormat(match.capturedStart(), match.capturedLength(), TYPE_FORMAT);
      }
    }
  }
}

QTextCharFormat _makeFormat(const QFont::Weight weight, const QColor& color) noexcept {
  QTextCharFormat format;

  format.setFontWeight(weight);
  format.setForeground(color);
  return format;
}
}
}
