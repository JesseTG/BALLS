/*
 * This file is part of GLShaderDev.
 *
 * GLShaderDev is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GLShaderDev is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GLShaderDev.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef QSCILEXERGLSL_H
#define QSCILEXERGLSL_H

#include <unordered_map>

#include <Qsci/qscilexercustom.h>
#include <Qsci/qscistyle.h>

class QsciLexerGLSL : public QsciLexerCustom {
  Q_OBJECT
public:
  QsciLexerGLSL(QObject* parent = nullptr) noexcept;
  ~QsciLexerGLSL();

public:
  const char* language() const noexcept override;
  QStringList autoCompletionWordSeparators() const noexcept override;
  const char* blockStartKeyword(int* style = 0) const noexcept override;
  const char* blockStart(int* style = 0) const noexcept override;
  const char* blockEnd(int* style = 0) const noexcept override;
  int braceStyle() const noexcept override;
  void styleText(int start, int end) noexcept override;
  QString description(int style) const noexcept override;
  QFont defaultFont(int style) const noexcept override;
  QColor defaultColor(int style) const noexcept override;
  QColor defaultPaper(int style) const noexcept override;
  bool defaultEolFill(int style) const noexcept override;
  const char* keywords(int set) const noexcept override;
  const char* wordCharacters() const noexcept override;

private:
  QsciLexerGLSL(const QsciLexerGLSL& other) = delete;
  QsciLexerGLSL& operator=(const QsciLexerGLSL& other) = delete;

  void styleLine(const QString& line, int size) noexcept;

private:
  enum StyleType { Default = 0, Comment, Keyword, Operator, Macro, Count };

private:
  std::unordered_map<int, QsciStyle> _styles;
  QFont _defaultFont;
};

#endif // QSCILEXERGLSL_H
