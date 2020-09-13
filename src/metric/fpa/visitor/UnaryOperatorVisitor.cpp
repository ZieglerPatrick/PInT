#include "metric/fpa/PrettyPrinter.h"
#include "metric/fpa/visitor/UnaryOperatorVisitor.h"
#include "metric/fpa/visitor/TransactionalFunctionVisitor.h"
#include "metric/fpa/ExternalInput.h"

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
		FunctionPoint* FunctionPoint;

		if(Node -> isIncrementDecrementOp()){
			FunctionPoint = new ExternalOutput(
				Visitor.det,
				Visitor.ftr,
				PrettyPrinter::PrintPretty(Node)
			);
		}else{
			FunctionPoint = new ExternalInput(
				Visitor.det,
				Visitor.ftr,
				PrettyPrinter::PrintPretty(Node)
			);
		}

		this -> FunctionPoints.push_back(FunctionPoint);;
	}

	return (true);
}
