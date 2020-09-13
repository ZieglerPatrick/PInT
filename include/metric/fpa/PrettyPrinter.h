#include "metric/fpa/FunctionPointComplexity.h"
#include "clang/AST/Expr.h"
#include <string>

namespace PrettyPrinter{
	extern std::string PrintPretty(FunctionPointComplexity Complexity);
	extern std::string PrintPretty(clang::Stmt* Statement);
	extern std::string PrintPretty(clang::Decl* Declaration);
	extern std::string PrintPretty(clang::QualType Type);
}
