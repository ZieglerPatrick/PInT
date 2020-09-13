#pragma once

#include "metric/fpa/visitor/DeclRefExprVisitor.h"

/**
 * Extracts the function point of conditional operators. An expression may consist
 * of multiple operators, but they all belong to a single function point.
 * If at least one of the expressions of the operator overlap with the environment,
 * it will be counted as an external input.
 */
class AbstractConditionalOperatorVisitor : public DeclRefExprVisitor<AbstractConditionalOperatorVisitor>{
	public:
		/**
		 * Creates a new visitor for conditional operators.
		 *
		 * @param myContext The context required when comparing two source locations.
		 * @param mySourceRange The range of the closest pattern code region.
		 */
		explicit AbstractConditionalOperatorVisitor(
				clang::ASTContext* myContext,
				clang::SourceRange mySourceRange
		);
		/**
		 * Processes a conditional operator. If this is the first occurrence of the operator, it will be treated as
		 * a function point, with all children being its members.<br>
		 * @param Node The node associated with the conditional operator.
		 * @return true
		 */
		bool VisitAbstractConditionalOperator(clang::AbstractConditionalOperator* Node);
	private:
		/**
		 * In case an expression consists of multiple operators, that
		 * this is the first occurrence and that all further operators
		 * are member of the initial function point.
		 */
		bool IsFirstOccurrence;
};
