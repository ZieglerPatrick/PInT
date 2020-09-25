#include "metric/fpa/visitor/DataFunctionVisitor.h"
#include <iostream>

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
	//getAsCXXRecordDecl doesn't specify if may return null
	}else if(Node -> getType() -> getAsCXXRecordDecl() != NULL){
		ObjectVisitor Visitor;
		//Visitor.TraverseDecl(Node -> getType() -> getAsRecordDecl());
		Visitor.TraverseDecl(Node -> getType() -> getAsCXXRecordDecl());

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

bool ObjectVisitor::VisitCXXRecordDecl(clang::CXXRecordDecl* Node){
	this -> ret += Node -> getNumBases();	//Each superclass is a potential subgroup
	return (true);
}
