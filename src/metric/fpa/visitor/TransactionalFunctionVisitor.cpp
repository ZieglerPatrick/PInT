#include "metric/fpa/visitor/TransactionalFunctionVisitor.h"
#include "metric/fpa/PrintPretty.h"

bool TransactionalFunctionVisitor::shouldVisitImplicitCode() const{
	return (true);
}

bool TransactionalFunctionVisitor::VisitDeclRefExpr(clang::DeclRefExpr* Node){
	UniqueTypes.emplace(FunctionPointAnalysis::PrintPretty(Node -> getType()));

	this -> det++;
	this -> ftr = UniqueTypes.size();
	return (true);
}

bool TransactionalFunctionVisitor::VisitVarDecl(clang::VarDecl* Node){
	//Include the declared variable
	UniqueTypes.emplace(FunctionPointAnalysis::PrintPretty(Node -> getType()));

	this -> det++;
	this -> ftr = UniqueTypes.size();
	return (true);
}
