#pragma once

#include "metric/halstead/HalsteadVisitor.h"
#include "metric/fpa/FunctionPointAnalysisVisitor.h"

/**
 * This consumer applies the visitor required for the analysis,
 * like the function point analysis or Halstead metrics.
 * It is possible that a parallel pattern is nested inside
 * a pattern located in a different translation unit. In
 * order to ensure that this pattern is found, it is necessary
 * that the pattern graph has been created before this consumer
 * is executed.
 */
class ASTDelegatorConsumer : public clang::ASTConsumer{
	public:
		/**
		 * Creates a new instance for each individual translation unit.
		 * The context is required for the function point analysis, in
		 * order to determine the order between the pattern code regions
		 * and the AST nodes.
		 *
		 * @param myContext The context over the translation unit.
		 */
		explicit ASTDelegatorConsumer(clang::ASTContext* myContext);
		/**
		 * Applies the visitors to the translation unit.
		 * @param myContext The context over the translation unit
		 */
		virtual void HandleTranslationUnit(clang::ASTContext& myContext) override;
	private:
		/**
		 * A reference to the function point analysis visitor.
		 * It counts the function points inside
		 * the respective parallel patterns.
		 */
		FunctionPointAnalysisVisitor myFunctionPointAnalysisVisitor;
		/**
		 * A reference to the Halstead visitor.
		 * It counts the operators and operands inside
		 * the respective parallel patterns.
		 */
		HalsteadVisitor myHalsteadVisitor;
};
