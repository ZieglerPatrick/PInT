#pragma once

#include "metric/fpa/visitor/DeclRefExprVisitor.h"

/**
 * Extracts the function point of assignment operators. It is possible to have multiple assignments
 * in a single line. But since each of those modify a value, they are treated as independent
 * function points.
 * If the left-hand side overlaps with the closest pattern code region and the right-hand side
 * with the environment, it is an external input. Otherwise, if the left-hand side overlaps with
 * the environment, it is an external output.
 *
 */
class AssignmentOperatorVisitor : public DeclRefExprVisitor<AssignmentOperatorVisitor>{
	public:
		/**
		 * Creates a new visitor for assignment operators.
		 *
		 * @param myContext The context required when comparing two source locations.
		 * @param mySourceRange The range of the closest pattern code region.
		 */
		explicit AssignmentOperatorVisitor(
				clang::ASTContext* myContext,
				clang::SourceRange mySourceRange
		);
		/**
		 * Processes a binary operator if it is an (compound) assignment. Clang doesn't allow for a more detailed
		 * distinction.
		 * @param Node The node associated with the binary operator.
		 * @return true
		 */
		bool VisitBinaryOperator(clang::BinaryOperator* Node);
};
