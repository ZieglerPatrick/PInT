#pragma once

#include "metric/fpa/visitor/DeclRefExprVisitor.h"

/**
 * Extracts the function point of unary operators.
 * Multiple operators in an expressions are counted as members of a single
 * function point. Additionally, all used variables are counted as independent
 * function points.
 */
class UnaryOperatorVisitor : public DeclRefExprVisitor<UnaryOperatorVisitor>{
	public:
		explicit UnaryOperatorVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange);
		bool VisitUnaryOperator(clang::UnaryOperator* Node);
	private:
		/**
		 * In case an expression consists of multiple operators, that
		 * this is the first occurrence and that all further operators
		 * are member of the initial function point.
		 */
		bool IsFirstOccurrence;
};
