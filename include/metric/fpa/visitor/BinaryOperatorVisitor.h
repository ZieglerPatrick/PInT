#pragma once

#include "metric/fpa/visitor/DeclRefExprVisitor.h"

/**
 * Extracts the function point of binary operators.
 * Multiple operators in an expressions are counted as members of a single
 * function point. Additionally, all used variables are counted as independent
 * function points.
 */
class BinaryOperatorVisitor : public DeclRefExprVisitor<BinaryOperatorVisitor>{
	public:
		explicit BinaryOperatorVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange);
		bool VisitBinaryOperator(clang::BinaryOperator* Node);
	private:
		/**
		 * In case an expression consists of multiple operators, that
		 * this is the first occurrence and that all further operators
		 * are member of the initial function point.
		 */
		bool IsFirstOccurrence;
};
