#pragma once

#include "metric/fpa/visitor/DeclRefExprVisitor.h"

/**
 * Extracts the function point of binary operators. An expression may consist
 * of multiple operators, but they all belong to a single function point.
 * Assignment operators are a special case and handled by {@link AssignmentOperatorVisitor}. All other operators
 * are considered to be external inputs, if at least one side of the expression overlaps with the environment.
 */
class BinaryOperatorVisitor : public DeclRefExprVisitor<BinaryOperatorVisitor>{
	public:
		/**
		 * Creates a new visitor for binary operators.
		 *
		 * @param myContext The context required when comparing two source locations.
		 * @param mySourceRange The range of the closest pattern code region.
		 */
		explicit BinaryOperatorVisitor(
				clang::ASTContext* myContext,
				clang::SourceRange mySourceRange
		);
		/**
		 * Processes a binary operator. If this is the first occurrence of the operator, it will be treated as
		 * a function point, with all children being its members. If the argument is an assignment operator,
		 * the node and all its child nodes will be ignored.
		 * @param Node The node associated with the conditional operator.
		 * @return true
		 */
		bool VisitBinaryOperator(clang::BinaryOperator* Node);
	private:
		/**
		 * In case an expression consists of multiple operators, that
		 * this is the first occurrence and that all further operators
		 * are member of the initial function point.
		 */
		bool IsFirstOccurrence;
};
