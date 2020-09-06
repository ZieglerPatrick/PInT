#pragma once

#include "HPCPatternInstrASTTraversal.h"
#include "metric/fpa/visitor/FunctionPointAnalysisVisitor.h"

class ASTConsumerDelegator : public clang::ASTConsumer{
	public:
		explicit ASTConsumerDelegator(clang::ASTContext *Context);
		virtual ~ASTConsumerDelegator(){};
		virtual void HandleTranslationUnit(clang::ASTContext &Context);
	private:
		HPCPatternInstrVisitor InstrumentationVisitor;
		FunctionPointAnalysisVisitor FPAVisitor;
};
