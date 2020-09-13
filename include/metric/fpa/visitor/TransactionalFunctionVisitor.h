#pragma once

#include "clang/AST/RecursiveASTVisitor.h"
/**
 * Counts the attributes for transactional functions. More specifically,
 * it counts the number of data element types and file type referenced.
 */
class TransactionalFunctionVisitor : public clang::RecursiveASTVisitor<TransactionalFunctionVisitor>{
	public:
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

		/**
		 * As much information as possible should be used
		 * to count the attributes.
		 *
		 * @return true
		 */
		bool shouldVisitImplicitCode() const;

		/**
		 * Continues the tree traversal with the declaration of argument.
		 * @param Node The node associated with the expression.
		 * @return false if the visitation was terminated early, true otherwise
		 */
		bool VisitDeclRefExpr(clang::DeclRefExpr* Node);

		/**
		 * Counts the occurrence and type of the variable declaration.
		 * @param Node The node associated with the declaration.
		 * @return false if the visitation was terminated early, true otherwise
		 */
		bool VisitVarDecl(clang::VarDecl* Node);

	private:
		/**
		 * Contains the name of all unique types. Two types are considered to
		 * be equal, if they share the same class name.
		 */
		std::set<std::string> UniqueTypes;
};
