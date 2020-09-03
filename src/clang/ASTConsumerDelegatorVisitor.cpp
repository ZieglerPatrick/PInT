#include "clang/ASTConsumerDelegator.h"

void ASTConsumerDelegator::HandleTranslationUnit(clang::ASTContext &Context){
	InstrumentationVisitor.TraverseDecl(Context.getTranslationUnitDecl());
}
