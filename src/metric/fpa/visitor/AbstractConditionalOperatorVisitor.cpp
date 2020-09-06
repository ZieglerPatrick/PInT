#include <metric/fpa/visitor/AbstractConditionalOperatorVisitor.h>
#include "metric/fpa/visitor/TransactionalFunctionVisitor.h"
#include "metric/fpa/ExternalInput.h"
#include "metric/fpa/PrintPretty.h"

AbstractConditionalOperatorVisitor::AbstractConditionalOperatorVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange):
	DeclRefExprVisitor(myContext, mySourceRange),
	IsFirstOccurrence(true){
}

bool AbstractConditionalOperatorVisitor::VisitAbstractConditionalOperator(clang::AbstractConditionalOperator* Node){
	//Skip invalid operators
	if(!IsFirstOccurrence)
		return (true);

	IsFirstOccurrence = false;
	TransactionalFunctionVisitor Visitor;
	Visitor.TraverseStmt(Node);

	if
	(
			OverlapsWithEnvironment(Node -> getCond()) ||
			OverlapsWithEnvironment(Node -> getTrueExpr()) ||
			OverlapsWithEnvironment(Node -> getFalseExpr())
	)
	{
		FunctionPoint* FunctionPoint = new ExternalInput
		(
				Visitor.det,
				Visitor.ftr,
				FunctionPointAnalysis::PrintPretty(Node)
		);

		this -> FunctionPoints.push_back(FunctionPoint);;
	}

	return (true);
}
