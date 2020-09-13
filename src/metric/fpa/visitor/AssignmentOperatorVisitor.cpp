#include "metric/fpa/PrettyPrinter.h"
#include "metric/fpa/visitor/AssignmentOperatorVisitor.h"
#include "metric/fpa/visitor/TransactionalFunctionVisitor.h"
#include "metric/fpa/ExternalInput.h"
#include "metric/fpa/ExternalOutput.h"

AssignmentOperatorVisitor::AssignmentOperatorVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange):
	DeclRefExprVisitor(myContext, mySourceRange){
}

bool AssignmentOperatorVisitor::VisitBinaryOperator(clang::BinaryOperator* Node){
	TransactionalFunctionVisitor Visitor;
	Visitor.TraverseStmt(Node);

	if(Node ->isCompoundAssignmentOp() || Node ->isAssignmentOp()){
		//e.g. x = y
		//where x is inside and y outside the pattern
		if(OverlapsWithPattern(Node -> getLHS()) && OverlapsWithEnvironment(Node -> getRHS())){
			FunctionPoint* FunctionPoint = new ExternalInput(
					Visitor.det,
					Visitor.ftr,
					PrettyPrinter::PrintPretty(Node)
			);

			this -> FunctionPoints.push_back(FunctionPoint);
		//e.g. x = ...
		//where is is outside the pattern
		}else if(OverlapsWithEnvironment(Node -> getLHS())){
			FunctionPoint* FunctionPoint = new ExternalOutput(
					Visitor.det,
					Visitor.ftr,
					PrettyPrinter::PrintPretty(Node)
			);

			this -> FunctionPoints.push_back(FunctionPoint);
		}
	}

	return (true);
}
