#include "clang/ASTConsumerDelegator.h"

ASTConsumerDelegator::ASTConsumerDelegator(clang::ASTContext *Context) :
	InstrumentationVisitor(Context),
	FPAVisitor(InstrumentationVisitor.GetPatternBegin(), InstrumentationVisitor.GetPatternEnd(), Context)
{
}

void ASTConsumerDelegator::HandleTranslationUnit(clang::ASTContext &Context){
	InstrumentationVisitor.TraverseDecl(Context.getTranslationUnitDecl());
	FPAVisitor.TraverseDecl(Context.getTranslationUnitDecl());
}
