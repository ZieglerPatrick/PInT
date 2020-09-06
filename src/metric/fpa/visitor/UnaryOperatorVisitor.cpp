#include <metric/fpa/visitor/UnaryOperatorVisitor.h>
#include "metric/fpa/visitor/TransactionalFunctionVisitor.h"
#include "metric/fpa/ExternalInput.h"
#include "metric/fpa/PrintPretty.h"

UnaryOperatorVisitor::UnaryOperatorVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange):
	DeclRefExprVisitor(myContext, mySourceRange),
	IsFirstOccurrence(true){
}

bool UnaryOperatorVisitor::VisitUnaryOperator(clang::UnaryOperator* Node){
	//Skip invalid operators
	if(!IsFirstOccurrence)
		return (true);

	IsFirstOccurrence = false;
	TransactionalFunctionVisitor Visitor;
	Visitor.TraverseStmt(Node);

	if(OverlapsWithEnvironment(Node ->getSubExpr())){
		FunctionPoint* FunctionPoint = new ExternalInput(
				Visitor.det,
				Visitor.ftr,
				FunctionPointAnalysis::PrintPretty(Node)
		);

		this -> FunctionPoints.push_back(FunctionPoint);;
	}

	return (true);
}
