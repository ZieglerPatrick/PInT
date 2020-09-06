#include "clang/ASTConsumerDelegator.h"

ASTConsumerDelegator::ASTConsumerDelegator(clang::ASTContext *Context) :
	myInstrumentationVisitor(Context),
	myFunctionPointAnalysisVisitor(myInstrumentationVisitor.GetPatternBegin(), myInstrumentationVisitor.GetPatternEnd(), Context),
	myHalsteadVisitor(myInstrumentationVisitor.GetPatternBegin(), myInstrumentationVisitor.GetPatternEnd())
{
}

void ASTConsumerDelegator::HandleTranslationUnit(clang::ASTContext &Context){
	myInstrumentationVisitor.TraverseDecl(Context.getTranslationUnitDecl());
	myFunctionPointAnalysisVisitor.TraverseDecl(Context.getTranslationUnitDecl());
	myHalsteadVisitor.TraverseDecl(Context.getTranslationUnitDecl());
}
