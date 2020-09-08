#pragma once

#include "HPCPatternInstrASTTraversal.h"
#include "metric/halstead/HalsteadVisitor.h"
#include "metric/fpa/visitor/FunctionPointAnalysisVisitor.h"

/**
 * This class applies the
 */
class ASTConsumerDelegator : public clang::ASTConsumer{
	public:
		explicit ASTConsumerDelegator(clang::ASTContext *Context);
		virtual ~ASTConsumerDelegator(){};
		virtual void HandleTranslationUnit(clang::ASTContext &Context);
	private:
		HPCPatternInstrVisitor myInstrumentationVisitor;
		FunctionPointAnalysisVisitor myFunctionPointAnalysisVisitor;
		HalsteadVisitor myHalsteadVisitor;
};
