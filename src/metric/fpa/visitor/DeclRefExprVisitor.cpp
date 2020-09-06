#include "metric/fpa/visitor/DeclRefExprVisitor.h"

DeclRefExprVisitorImplementation::DeclRefExprVisitorImplementation(clang::ASTContext* myContext, clang::SourceRange mySourceRange):
	DeclRefExprVisitor(myContext, mySourceRange){
}
