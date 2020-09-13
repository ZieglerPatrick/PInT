#include "metric/fpa/PrettyPrinter.h"
#include "metric/fpa/visitor/VarDeclVisitor.h"
#include "metric/fpa/visitor/DataFunctionVisitor.h"
#include "metric/fpa/visitor/TransactionalFunctionVisitor.h"
#include "metric/fpa/InternalLogicalFile.h"
#include "metric/fpa/ExternalInput.h"

VarDeclVisitor::VarDeclVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange):
	DeclRefExprVisitor(myContext, mySourceRange){
}

bool VarDeclVisitor::VisitVarDecl(clang::VarDecl* Node){
	HandleDataFunction(Node);
	HandleTransactionalFunction(Node);

	return (true);
}

void VarDeclVisitor::HandleDataFunction(clang::VarDecl* Node){
	DataFunctionVisitor Visitor(Context);
	Visitor.TraverseVarDecl(Node);

	FunctionPoint* FunctionPoint = new InternalLogicalFile(
			Visitor.det,
			Visitor.ret,
			PrettyPrinter::PrintPretty(Node)
	);

	this -> FunctionPoints.push_back(FunctionPoint);
}

void VarDeclVisitor::HandleTransactionalFunction(clang::VarDecl* Node){
	if(Node -> getInit() == NULL)
		return;

	TransactionalFunctionVisitor Visitor;
	Visitor.TraverseVarDecl(Node);

	if(OverlapsWithEnvironment(Node ->getInit())){
		FunctionPoint* FunctionPoint = new ExternalInput(
				Visitor.det,
				Visitor.ftr,
				PrettyPrinter::PrintPretty(Node)
		);

		this -> FunctionPoints.push_back(FunctionPoint);
	}
}
