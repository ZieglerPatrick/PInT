#include "metric/fpa/PrettyPrinter.h"
#include "metric/fpa/visitor/BinaryOperatorVisitor.h"
#include "metric/fpa/visitor/TransactionalFunctionVisitor.h"
#include "metric/fpa/ExternalInput.h"

BinaryOperatorVisitor::BinaryOperatorVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange):
	DeclRefExprVisitor(myContext, mySourceRange),
	IsFirstOccurrence(true){
}

bool BinaryOperatorVisitor::VisitBinaryOperator(clang::BinaryOperator* Node){
	//Skip invalid operators
	if(Node -> isCompoundAssignmentOp() || Node ->isAssignmentOp() || !IsFirstOccurrence)
		return (true);

	IsFirstOccurrence = false;
	TransactionalFunctionVisitor Visitor;
	Visitor.TraverseStmt(Node);

	if(OverlapsWithEnvironment(Node -> getLHS()) || OverlapsWithEnvironment(Node -> getRHS())){
		FunctionPoint* FunctionPoint = new ExternalInput(
				Visitor.det,
				Visitor.ftr,
				PrettyPrinter::PrintPretty(Node) + " (" + Node -> getOpcodeStr().str() + ")"
		);

		this -> FunctionPoints.push_back(FunctionPoint);;
	}

	return (true);
}
