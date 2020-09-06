#pragma once

#include "metric/fpa/visitor/DeclRefExprVisitor.h"

class VarDeclVisitor : public DeclRefExprVisitor<VarDeclVisitor>{
	public:
		explicit VarDeclVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange);
		bool VisitVarDecl(clang::VarDecl* Node);
	private:
		void HandleDataFunction(clang::VarDecl* Node);
		void HandleTransactionalFunction(clang::VarDecl* Node);
};
