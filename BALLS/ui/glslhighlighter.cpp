
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

#include "precompiled.hpp"
#include "ui/glslhighlighter.hpp"
#include "ui/glslsyntax.hpp"

#include <QTextDocument>
#include <QStringListModel>

GlslHighlighter::GlslHighlighter(QObject* parent, const QOpenGLShader::ShaderType type)
    : QSyntaxHighlighter(parent) {
  setLanguage(type, 3, 0);
}

void GlslHighlighter::createAndAppendRules(const QString& pattern, const int format) {
  QRegExp p(pattern);
  Q_ASSERT(p.isValid());
  m_patternsByFormat[format].push_back(p);
}

void GlslHighlighter::setLanguage(const QOpenGLShader::ShaderType language,
                                  const int major,
                                  const int minor) {
  m_language = language;
  m_formats.clear();
  m_patternsByFormat.clear();
  _major = major;
  _minor = minor;

  if (0 == m_language)
    return;

  m_formats = std::vector<QTextCharFormat>(4);
  m_formats[0].setForeground(QColor("#0000ff"));
  m_formats[1].setForeground(QColor("#888888"));
  m_formats[2].setForeground(QColor("#a000a0"));
  m_formats[3].setForeground(QColor("#880000"));

  createAndAppendRules(glsl_syntax_TransparentTypes, 0);
  createAndAppendRules(glsl_syntax_SamplerTypes, 0);
  createAndAppendRules(glsl_syntax_PreprocessorDirectives, 1);
  createAndAppendRules(glsl_syntax_PredefinedMacros, 0);
  createAndAppendRules(glsl_syntax_Qualifiers, 0);
  createAndAppendRules(glsl_syntax_InterpolationQualifier, 0);
  createAndAppendRules(glsl_syntax_CompatibilityUniforms, 2);
  createAndAppendRules(glsl_syntax_ConstantsBuiltIn, 2);
  createAndAppendRules(glsl_syntax_IterationAndJumps, 0);
  createAndAppendRules(glsl_syntax_Functions, 3);
  createAndAppendRules(glsl_syntax_AngleAndTrigonometryFunctions, 3);
  createAndAppendRules(glsl_syntax_ExponentialFunctions, 3);
  createAndAppendRules(glsl_syntax_CommonFunctions, 3);
  createAndAppendRules(glsl_syntax_GeometricFunctions, 3);
  createAndAppendRules(glsl_syntax_MatrixFunctions, 3);
  createAndAppendRules(glsl_syntax_VectorRelationalFunctions, 3);
  createAndAppendRules(glsl_syntax_NoiseFunctions, 3);
  createAndAppendRules(glsl_syntax_TextureLookupFunctions, 3);

  switch (m_language) {
  case QOpenGLShader::Vertex:
    createAndAppendRules(glsl_syntax_BuiltIn_v, 2);
    break;
  case QOpenGLShader::Geometry:
    createAndAppendRules(glsl_syntax_BuiltIn_g, 2);
    createAndAppendRules(glsl_syntax_Functions_g, 3);
    break;
  case QOpenGLShader::Fragment:
    createAndAppendRules(glsl_syntax_BuiltIn_f, 2);
    createAndAppendRules(glsl_syntax_IterationAndJumps_f, 0);
    createAndAppendRules(glsl_syntax_DerivativeFunctions_f, 3);
    break;
  default:
    break;
  }
}


void GlslHighlighter::highlightBlock(const QString& text) {
  for (auto& f : m_patternsByFormat) {
    const QTextCharFormat& format = m_formats[f.first];

    for (QRegExp& pattern : f.second) {
      int index(text.indexOf(pattern));
      while (-1 != index) {
        const int length(pattern.matchedLength());
        setFormat(index, length, format);

        index = text.indexOf(pattern, index + length);
      }
    }
  }
}
