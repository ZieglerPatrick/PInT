#pragma once

#include "clang/AST/RecursiveASTVisitor.h"

struct TransactionalFunctionVisitor : public clang::RecursiveASTVisitor<TransactionalFunctionVisitor>{

	/**
	 * Contains the number of data element types. It relates
	 * to the total number of variables used in the expression.
	 */
	int det = 0;
	/**
	 * Contains the number of file type referenced. It relates
	 * to the total number of distinct data types used in the expression.
	 */
	int ftr = 0;

	bool shouldVisitImplicitCode() const;
	bool VisitDeclRefExpr(clang::DeclRefExpr* Node);
	bool VisitVarDecl(clang::VarDecl* Node);

	private:
		/**
		 * Contains the name of all unique types. Two types are considered to
		 * be equal, if they share the same class name.
		 */
		std::set<std::string> UniqueTypes;
};
