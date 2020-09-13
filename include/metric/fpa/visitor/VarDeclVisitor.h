#pragma once

#include "metric/fpa/visitor/DeclRefExprVisitor.h"
/**
 * Handles data and transactional function points that may occur
 * during a variable declaration.
 */
class VarDeclVisitor : public DeclRefExprVisitor<VarDeclVisitor>{
	public:
		/**
		 * Creates a new visitor for variable declarations.
		 *
		 * @param myContext The context required when comparing two source locations.
		 * @param mySourceRange The range of the closest pattern code region.
		 */
		explicit VarDeclVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange);

		/**
		 * Processes a variable declaration. In case the variable is initialized, the declaration
		 * can be an external input. Otherwise, since the declaration happens inside a pattern
		 * code region, it is also an internal logical file.
		 * @param Node The node associated with the variable declaration.
		 * @return true
		 */
		bool VisitVarDecl(clang::VarDecl* Node);
	private:
		/**
		 * Checks if the node is a data function and adds it to the function points
		 * of the current pattern code region.
		 * @param Node The node associated with the variable declaration.
		 */
		void HandleDataFunction(clang::VarDecl* Node);
		/**
		 * Checks if the node is a transactional function and adds it to the function points
		 * of the current pattern code region.
		 * @param Node The node associated with the variable declaration.
		 */
		void HandleTransactionalFunction(clang::VarDecl* Node);
};
