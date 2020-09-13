#include "clang/ASTInstrumentationConsumer.h"

ASTInstrumentationConsumer::ASTInstrumentationConsumer(clang::ASTContext *myContext) :
		myInstrumentationVisitor(myContext){
}

void ASTInstrumentationConsumer::HandleTranslationUnit(clang::ASTContext &myContext){
	myInstrumentationVisitor.TraverseDecl(myContext.getTranslationUnitDecl());
}
