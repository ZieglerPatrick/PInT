#pragma once

#include "HPCPatternInstrASTTraversal.h"

/**
 * Each source file is treated as a translation unit and
 * is traversed in an arbitrary order, as opposed to the
 * one indicated by the program flow. This consumer will
 * access each unit and count all call expressions.
 */
class ASTInstrumentationConsumer : public clang::ASTConsumer{
	public:
		/**
		 * Creates a new instance for each individual translation unit.
		 * The context is required for instrumentation, to distinguish
		 * between source files that are supposed to be instrumented
		 * and those that ought to be ignored.
		 *
		 * @param myContext The context over the translation unit.
		 */
		explicit ASTInstrumentationConsumer(clang::ASTContext* myContext);
		/**
		 * Applies the visitors to the translation unit.
		 * @param myContext The context over the translation unit
		 */
		virtual void HandleTranslationUnit(clang::ASTContext& myContext) override;
	private:
		/**
		 * A reference to the instrumentation visitor.
		 * It counts all for the analysis relevant call expressions and
		 * create the pattern instances.
		 */
		HPCPatternInstrVisitor myInstrumentationVisitor;
};
