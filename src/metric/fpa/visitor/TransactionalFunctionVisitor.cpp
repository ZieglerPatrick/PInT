#include <metric/fpa/PrettyPrinter.h>
#include "metric/fpa/visitor/TransactionalFunctionVisitor.h"

bool TransactionalFunctionVisitor::shouldVisitImplicitCode() const{
	return (true);
}

bool TransactionalFunctionVisitor::VisitDeclRefExpr(clang::DeclRefExpr* Node){
	UniqueTypes.emplace(PrettyPrinter::PrintPretty(Node -> getType()));

	this -> det++;
	this -> ftr = UniqueTypes.size();
	return (true);
}

bool TransactionalFunctionVisitor::VisitVarDecl(clang::VarDecl* Node){
	//Include the declared variable
	UniqueTypes.emplace(PrettyPrinter::PrintPretty(Node -> getType()));

	this -> det++;
	this -> ftr = UniqueTypes.size();
	return (true);
}
