#include "ui/GLSLPatterns.hpp"

#include <QRegularExpression>
#include <QString>
#include <QStringList>

namespace balls {
namespace ui {
namespace patterns {
const QRegularExpression
 TYPE("\\b(void|bool|u?int|float|[biu]?vec[234]|mat[234]"
      "(?:x[234])?|[ui]?sampler(?:Cube|Buffer|[123]D(?:"
      "(?:Rect|Array)?(?:Shadow)?|MS(?:Array)?)))\\b",
      QRegularExpression::OptimizeOnFirstUsageOption);

const QRegularExpression
 STORAGE("\\b(const|(?:(?:smooth|flat|noperspective)\\s+)?(?:centroid\\s+)?(?:"
         "in|out|varying)|attribute|uniform)\\b",
         QRegularExpression::OptimizeOnFirstUsageOption);

const QRegularExpression PRECISION("\\b(low|medium|high)p\\b",
                                   QRegularExpression::OptimizeOnFirstUsageOption);

const QRegularExpression CONTROL("\\b(if|else|switch|case|default|for|while|do|"
                                 "break|continue|return|discard|struct)\\b",
                                 QRegularExpression::OptimizeOnFirstUsageOption);

const QRegularExpression
 GL_BUILTIN("\\bgl_[\\w_]+\\b", QRegularExpression::OptimizeOnFirstUsageOption);

const QRegularExpression
 LITERALS("\\b(true|false|[-+]?[0-9]*\\.?[0-9]+(?:[eE][-+]?[0-9]+)?|(?:[1-9]"
          "\\d*|0[0-7]+|0[xX][0-9a-fA-F]+)[uU]?)\\b",
          QRegularExpression::OptimizeOnFirstUsageOption);

const QRegularExpression PREPROCESSOR(
 "\\G\\s*\\#\\s*(?:define|undef|if(?:n?def)?|el(?:se|if)|endif|error|"
 "pragma|extension|version|line)?.*(?:\\n|$)",
 QRegularExpression::OptimizeOnFirstUsageOption);

const QRegularExpression COMMENT(R"#((\/\/[^\n]*|\/\*.*?\*\/))#",
                                 QRegularExpression::OptimizeOnFirstUsageOption |
                                  QRegularExpression::DotMatchesEverythingOption);
}
namespace lists {
const QStringList TYPE = {
 "void",
 "bool",
 "int",
 "uint",
 "float",
 "vec2",
 "vec3",
 "vec4",
 "bvec2",
 "bvec3",
 "bvec4",
 "ivec2",
 "ivec3",
 "ivec4",
 "uvec2",
 "uvec3",
 "uvec4",
 "mat2",
 "mat3",
 "mat4",
 "mat2x2",
 "mat2x3",
 "mat2x4",
 "mat3x2",
 "mat3x3",
 "mat3x4",
 "mat4x2",
 "mat4x3",
 "mat4x4",
 "sampler1D",
 "sampler2D",
 "sampler3D",
 "samplerCube",
 "sampler2DRect",
 "sampler1DShadow",
 "sampler2DShadow",
 "sampler2DRectShadow",
 "sampler1DArray",
 "sampler2DArray",
 "sampler1DArrayShadow",
 "sampler2DArrayShadow",
 "samplerBuffer",
 "sampler2DMS",
 "sampler2DMSArray",
 "isampler1D",
 "isampler2D",
 "isampler3D",
 "isamplerCube",
 "isampler2DRect",
 "isampler1DArray",
 "isampler2DArray",
 "isamplerBuffer",
 "isampler2DMS",
 "isampler2DMSArray",
 "usampler1D",
 "usampler2D",
 "usampler3D",
 "usamplerCube",
 "usampler2DRect",
 "usampler1DArray",
 "usampler2DArray",
 "usamplerBuffer",
 "usampler2DMS",
 "usampler2DMSArray",
};

const QStringList BUILTIN_FUNCTIONS = {
 "radians",
 "degrees",
 "sin",
 "cos",
 "tan",
 "asin",
 "acos",
 "atan",
 "sinh",
 "cosh",
 "tanh",
 "asinh",
 "acosh",
 "atanh",
 "pow",
 "exp",
 "log",
 "exp2",
 "log2",
 "sqrt",
 "inversesqrt",
 "abs",
 "sign",
 "floor",
 "trunc",
 "round",
 "roundEven",
 "ceil",
 "fract",
 "mod",
 "modf",
 "min",
 "max",
 "clamp",
 "mix",
 "step",
 "smoothstep",
 "isinf",
 "isnan",
 "length",
 "distance",
 "dot",
 "cross",
 "normalize",
 "faceforward",
 "reflect",
 "refract",
 "matrixCompMult",
 "outerProduct",
 "transpose",
 "determinant",
 "inverse",
 "lessThan",
 "lessThanEqual",
 "greaterThan",
 "greaterThanEqual",
 "equal",
 "notEqual",
 "any",
 "all",
 "not",
 "textureSize",
 "textureProj",
 "texture",
 "textureLod",
 "textureOffset",
 "texelFetch",
 "texelFetchOffset",
 "textureProjOffset",
 "textureLodOffset",
 "textureProjLod",
 "textureProjLodOffset",
 "textureGrad",
 "textureGradOffset",
 "textureProjGrad",
 "textureProjGradOffset",
 "texture1D",
 "texture1DProj",
 "texture1DLod",
 "texture1DProjLod",
 "texture2D",
 "texture2DProj",
 "texture2DLod",
 "texture2DProjLod",
 "texture3D",
 "texture3DProj",
 "texture3DLod",
 "texture3DProjLod",
 "textureCube",
 "textureCubeLod",
 "shadow1D",
 "shadow2D",
 "shadow1DProj",
 "shadow2DProj",
 "shadow1DLod",
 "shadow2DLod",
 "shadow1DProjLod",
 "shadow2DProjLod",
 "dFdx",
 "dFdy",
 "fwidth",
 "noise1",
 "noise2",
 "noise3",
 "noise4",
 "EmitVertex",
 "EndPrimitive",
};
}
}
}
