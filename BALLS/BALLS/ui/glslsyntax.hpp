
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
#ifndef __GLSL_SYNTAX_H__
#define __GLSL_SYNTAX_H__

#include <QStringList>

// Base: 1.30
const extern QString glsl_syntax_Reserved_All;
const extern QString glsl_syntax_TransparentTypes;
const extern QString glsl_syntax_TransparentTypes_400;
const extern QString glsl_syntax_SamplerTypes;
const extern QString glsl_syntax_PreprocessorDirectives;
const extern QString glsl_syntax_PredefinedMacros;
const extern QString glsl_syntax_Qualifiers;
const extern QString glsl_syntax_Qualifiers_330;
const extern QString glsl_syntax_Qualifiers_400;
const extern QString glsl_syntax_Qualifiers_400_t;
const extern QString glsl_syntax_InterpolationQualifier;
const extern QString glsl_syntax_CompatibilityUniforms;
const extern QString glsl_syntax_BuiltIn_v;
const extern QString glsl_syntax_BuiltIn_g;
const extern QString glsl_syntax_BuiltIn_f;
const extern QString glsl_syntax_ConstantsBuiltIn;
const extern QString glsl_syntax_Layouts;
const extern QString glsl_syntax_PrecisionQualifiers;
const extern QString glsl_syntax_IterationAndJumps;
const extern QString glsl_syntax_IterationAndJumps_f;
const extern QString glsl_syntax_Functions;
const extern QString glsl_syntax_AngleAndTrigonometryFunctions;
const extern QString glsl_syntax_ExponentialFunctions;
const extern QString glsl_syntax_CommonFunctions;
const extern QString glsl_syntax_CommonFunctions_330;
const extern QString glsl_syntax_CommonFunctions_400;
const extern QString glsl_syntax_GeometricFunctions;
const extern QString glsl_syntax_MatrixFunctions;
const extern QString glsl_syntax_VectorRelationalFunctions;
const extern QString glsl_syntax_DerivativeFunctions_f;
const extern QString glsl_syntax_NoiseFunctions;
const extern QString glsl_syntax_Functions_g;
const extern QString glsl_syntax_TextureLookupFunctions;
const extern QStringList glsl_complete_common;
const extern QStringList glsl_complete_v;
const extern QStringList glsl_complete_g;
const extern QStringList glsl_complete_f;

#endif // __GLSL_SYNTAX_H__
