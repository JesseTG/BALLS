#ifndef GLSLPATTERNS_HPP
#define GLSLPATTERNS_HPP

class QRegularExpression;
class QString;
class QStringList;

namespace balls {
namespace ui {
namespace patterns {
const extern QRegularExpression TYPE;
const extern QRegularExpression STORAGE;
const extern QRegularExpression PRECISION;
const extern QRegularExpression CONTROL;
const extern QRegularExpression GL_BUILTIN;
const extern QRegularExpression LITERALS;
const extern QRegularExpression PREPROCESSOR;
const extern QRegularExpression COMMENT;
}

namespace lists {
const extern QStringList TYPE;
const extern QStringList KEYWORD;
const extern QStringList BUILTIN_FUNCTIONS;
}
}
}
#endif // GLSLPATTERNS_HPP
