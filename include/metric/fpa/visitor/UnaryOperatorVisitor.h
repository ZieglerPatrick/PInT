#pragma once

#include "metric/fpa/visitor/DeclRefExprVisitor.h"

/**
 * Extracts the function point of unary operators. An expression may consist
 * of multiple operators, but they all belong to a single function point.
 * If the expression overlaps with the environment, it is an external input.
 */
class UnaryOperatorVisitor : public DeclRefExprVisitor<UnaryOperatorVisitor>{
	public:
		/**
		 * Creates a new visitor for unary operators.
		 *
		 * @param myContext The context required when comparing two source locations.
		 * @param mySourceRange The range of the closest pattern code region.
		 */
		explicit UnaryOperatorVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange);
		/**
		 * Processes an unary operator. If this is the first occurrence of the operator, it will be treated as
		 * a function point, with all children being its members.
		 * @param Node The node associated with the conditional operator.
		 * @return true
		 */
		bool VisitUnaryOperator(clang::UnaryOperator* Node);
	private:
		/**
		 * In case an expression consists of multiple operators, that
		 * this is the first occurrence and that all further operators
		 * are member of the initial function point.
		 */
		bool IsFirstOccurrence;
};
