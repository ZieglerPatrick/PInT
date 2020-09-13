#include "metric/fpa/PrettyPrinter.h"
#include "clang/AST/PrettyPrinter.h"
#include <sstream>

std::string PrettyPrinter::PrintPretty(FunctionPointComplexity Complexity){
	static std::vector<std::string> Names = {"Low", "Medium", "High"};
	return (Names[Complexity]);
}

std::string PrettyPrinter::PrintPretty(clang::Stmt* Statement){
	std::string PrettyStatement;
	llvm::raw_string_ostream Stream(PrettyStatement);
	Statement -> printPretty(Stream, 0, clang::PrintingPolicy(clang::LangOptions()));
	return (Stream.str());
}

std::string PrettyPrinter::PrintPretty(clang::Decl* Declaration){
	std::string PrettyDeclaration;
	llvm::raw_string_ostream Stream(PrettyDeclaration);
	Declaration -> print(Stream, clang::PrintingPolicy(clang::LangOptions()));
	return (Stream.str());
}

std::string PrettyPrinter::PrintPretty(clang::QualType Type){
	return (Type.getAsString());
}
