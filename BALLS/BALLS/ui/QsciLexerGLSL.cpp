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

#include "precompiled.hpp"
#include <Qsci/qsciscintilla.h>

#include "QsciLexerGLSL.h"

QsciLexerGLSL::QsciLexerGLSL(QObject* parent) noexcept
:
QsciLexerCustom(parent)
{
  _defaultFont.setFamily("Monospace");
  _defaultFont.setPointSize(9);
  QFont ft(_defaultFont);

  ft.setBold(true);

  _styles[Default] = QsciStyle(Default);
  _styles[Default].setDescription("Default");
  // _styles[Default].setFont(defaultFont(0));

  _styles[Comment] = QsciStyle(Comment);
  _styles[Comment].setDescription("Comment");
  _styles[Comment].setColor("#888888");
  // _styles[Comment].setFont(defaultFont(0));

  _styles[Keyword] = QsciStyle(Keyword);
  _styles[Keyword].setDescription("Keyword");
  _styles[Keyword].setColor("#22ff55");
  // _styles[Keyword].setFont(ft);

  _styles[Operator] = QsciStyle(Operator);
  _styles[Operator].setDescription("Operator");
  _styles[Operator].setColor("#2288ff");
  // _styles[Operator].setFont(ft);

  _styles[Macro] = QsciStyle(Macro);
  _styles[Macro].setDescription("Macro");
  _styles[Macro].setColor("#001100");
  // _styles[Macro].setFont(ft);

}

QsciLexerGLSL::~QsciLexerGLSL() {}

const char* QsciLexerGLSL::language() const noexcept
{
  return "GLSL";
}

QStringList QsciLexerGLSL::autoCompletionWordSeparators() const noexcept
{
  return {"."};
}

const char* QsciLexerGLSL::blockStartKeyword(int* style) const noexcept
{
  if (style) {
    *style = Keyword;
  }

  return ("case catch class default do else for if while");
}

const char* QsciLexerGLSL::blockStart(int* style) const noexcept
{
  if (style) {
    *style = Operator;
  }

  return ("{");
}

const char* QsciLexerGLSL::blockEnd(int* style) const noexcept
{
  if (style) {
    *style = Operator;
  }

  return ("}");
}

int QsciLexerGLSL::braceStyle() const noexcept
{
  return (Operator);
}

void QsciLexerGLSL::styleText(int start, int end) noexcept
{
  std::vector<char> range(end - start + 1, '\0');
  editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end, range.data());
  QString text(range.data());

  startStyling(start);
  QStringList lines = text.split('\n');

  for (int i = 0; i < lines.size(); i++)
  {
    int style = Default;

    if (lines.at(i).startsWith("//")) {
      style = Comment;
    }

    if (lines.at(i).startsWith("#")) {
      style = Macro;
    }

    setStyling(lines.at(i).size(), style);

    if (Q_LIKELY(i < lines.size() - 1)) {
      setStyling(1, Default);
    }
  }
}

QString QsciLexerGLSL::description(int style) const noexcept
{
  if (style < 0 || style >= Count) {
    style = 0;
  }

  return (_styles.at(style).description());
}

QFont QsciLexerGLSL::defaultFont(int style) const noexcept
{
  if (style < 0 || style >= Count) {
    style = 0;
  }

  return (_styles.at(style).font());
}

QColor QsciLexerGLSL::defaultColor(int style) const noexcept
{
  if (style < 0 || style >= Count) {
    style = 0;
  }

  return (_styles.at(style).color());
}

QColor QsciLexerGLSL::defaultPaper(int style) const noexcept
{
  return QsciLexer::defaultPaper(style);
}

bool QsciLexerGLSL::defaultEolFill(int style) const noexcept
{
  return QsciLexer::defaultEolFill(style);
}

const char* QsciLexerGLSL::keywords(int set) const noexcept
{
  if (set == 1) {
    return ("in out varying uniform");
  }

  return (0);
}

const char* QsciLexerGLSL::wordCharacters() const noexcept
{
  return ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_");
}

void QsciLexerGLSL::styleLine(const QString& line, int size) noexcept
{
  setStyling(size, Default);
  qDebug() << "styleLine(" + line;
}
