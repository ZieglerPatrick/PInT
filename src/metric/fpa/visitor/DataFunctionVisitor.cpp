#include "metric/fpa/visitor/DataFunctionVisitor.h"

DataFunctionVisitor::DataFunctionVisitor(clang::ASTContext* NewContext) :
	Context(NewContext){
}

bool DataFunctionVisitor::shouldVisitImplicitCode() const{
	return (true);
}

bool DataFunctionVisitor::VisitDeclRefExpr(clang::DeclRefExpr* Node){
	return (TraverseDecl(Node -> getFoundDecl()));
}

bool DataFunctionVisitor::VisitVarDecl(clang::VarDecl* Node){
	//Primitive types don't have constructors, attributes & methods
	if(Node -> getType().isTrivialType(*Context)){
		this -> det = 1;
		this -> ret = 1;
	//getAsRecordDecl doesn't specify if it returns null
	}else if(Node -> getType() -> getAsRecordDecl() != NULL){
		ObjectVisitor Visitor;
		Visitor.TraverseRecordDecl(Node -> getType() -> getAsRecordDecl());

		this -> det = Visitor.det;
		this -> ret = Visitor.ret;
	}

	return (true);
}

bool ObjectVisitor::shouldVisitImplicitCode() const{
	return (false);
}

bool ObjectVisitor::VisitFieldDecl(clang::FieldDecl* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
	this -> det++;
	return (true);
}

bool ObjectVisitor::VisitCXXMethodDecl(clang::CXXMethodDecl* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
	this -> det++;
	return (true);
}

bool ObjectVisitor::WalkUpFromCXXConstructorDecl(clang::CXXConstructorDecl* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
	this -> ret++;
	return (true);
}

bool ObjectVisitor::WalkUpFromCXXDestructorDecl(clang::CXXDestructorDecl* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
	return (true);
}

bool ObjectVisitor::WalkUpFromCXXConversionDecl(clang::CXXConversionDecl* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
	return (true);
}
