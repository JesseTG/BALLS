// Copyright (c) 2011-2012, Daniel M�ller <dm@g4t3.de>
// Computer Graphics Systems Group at the Hasso-Plattner-Institute, Germany
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of the Computer Graphics Systems Group at the
//     Hasso-Plattner-Institute (HPI), Germany nor the names of its
//     contributors may be used to endorse or promote products derived from
//     this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#pragma once
#ifndef __GLSL_HIGHLIGHTER_H__
#define __GLSL_HIGHLIGHTER_H__

#include <cstdint>
#include <unordered_map>
#include <vector>

#include <QOpenGLShader>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;
class QStringListModel;
class QColor;
class QStringList;


class GlslHighlighter : public QSyntaxHighlighter {
public:
  GlslHighlighter(QObject*, const QOpenGLShader::ShaderType);
  virtual ~GlslHighlighter() {}

protected:
  void setLanguage(const QOpenGLShader::ShaderType language, const int, const int);

  void createAndAppendRules(const QString& pattern, const int);

  // QSyntaxHighlighter interface

  void highlightBlock(const QString& text) override;

protected:
  std::vector<QTextCharFormat> m_formats;
  std::unordered_map<int, std::vector<QRegExp>> m_patternsByFormat;

  QOpenGLShader::ShaderType m_language;
  int _major;
  int _minor;
};

#endif // __GLSL_HIGHLIGHTER_H__
