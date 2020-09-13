#include "clang/ASTDelegatorConsumer.h"

ASTDelegatorConsumer::ASTDelegatorConsumer(
		clang::ASTContext *myContext
) :
		myFunctionPointAnalysisVisitor(myContext),
		myHalsteadVisitor(myContext){
}

void ASTDelegatorConsumer::HandleTranslationUnit(clang::ASTContext &myContext){
	myFunctionPointAnalysisVisitor.TraverseDecl(myContext.getTranslationUnitDecl());
	myHalsteadVisitor.TraverseDecl(myContext.getTranslationUnitDecl());
}
