#pragma once

#include "metric/fpa/visitor/DeclRefExprVisitor.h"

/**
 * Extracts the function point of assignment operators.
 */
class AssignmentOperatorVisitor : public DeclRefExprVisitor<AssignmentOperatorVisitor>{
	public:
		explicit AssignmentOperatorVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange);
		bool VisitBinaryOperator(clang::BinaryOperator* Node);
};
