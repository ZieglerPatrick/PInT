#pragma once

#include "HPCPatternInstrASTTraversal.h"

class ASTConsumerDelegator : public clang::ASTConsumer{
	public:
		explicit ASTConsumerDelegator(clang::ASTContext *Context) : InstrumentationVisitor(Context){}
		virtual ~ASTConsumerDelegator(){};
		virtual void HandleTranslationUnit(clang::ASTContext &Context);
	private:
		HPCPatternInstrVisitor InstrumentationVisitor;
};
