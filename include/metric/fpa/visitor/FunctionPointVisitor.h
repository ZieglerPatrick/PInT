#pragma once

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/SourceManager.h"
#include "metric/fpa/FunctionPoint.h"

/**
 * Base class for the individual AST visitors.
 * @tparam Derived The inheriting visitor
 */
template <typename Derived> class FunctionPointVisitor : public clang::RecursiveASTVisitor<Derived>{
	public:
		explicit FunctionPointVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange) :
			Context(myContext),
			SourceRange(mySourceRange),
			IsBefore(Context -> getSourceManager()){
		}
		std::vector<FunctionPoint*> FunctionPoints;

	protected:
		clang::ASTContext* Context;
		clang::SourceRange SourceRange;
		clang::BeforeThanCompare<clang::SourceLocation> IsBefore;

		bool FullyContains(clang::SourceRange Source, clang::SourceRange Target){
			return (!IsBefore(Target.getBegin(), Source.getBegin()) && !IsBefore(Source.getEnd(), Target.getEnd()));
		}

		/**
		 * Derives the declaration ranges of all references in the given statement.
		 * This includes both variable and function declaration.
		 * @param Statement An arbitrary statement.
		 * @return A vector containing the range of all declarations.
		 */
		std::vector<clang::SourceRange> GetDeclarationSourceRanges(clang::Stmt* Statement){
			//A little helper class to access the range of all declaration
			struct DeclarationSourceRangeVisitor : public clang::RecursiveASTVisitor<DeclarationSourceRangeVisitor>{
				std::vector<clang::SourceRange> DeclarationSourceRanges;

				bool VisitDeclRefExpr(clang::DeclRefExpr* Expression){
					return (this -> TraverseDecl(Expression -> getDecl()));
				}

				bool VisitVarDecl(clang::VarDecl* Declaration){
					DeclarationSourceRanges.push_back(Declaration -> getSourceRange());
					return (true);
				}

				bool VisitFunctionDecl(clang::FunctionDecl* Declaration){
					DeclarationSourceRanges.push_back(Declaration -> getSourceRange());
					return (true);
				}
			};

			DeclarationSourceRangeVisitor Visitor;
			Visitor.TraverseStmt(Statement);

			return (Visitor.DeclarationSourceRanges);
		}

		/**
		 * Checks if the statement overlaps with the pattern. Returns true if
		 * at least one variable referenced in the statement has been declared inside
		 * the pattern.
		 * @param Statement an arbitrary statement.
		 * @return true if the statement overlaps with the pattern.
		 */
		bool OverlapsWithPattern(clang::Stmt* Statement){
			//Check if at least one declaration is inside the code region
			for(auto DeclarationRange : GetDeclarationSourceRanges(Statement))
				if(!FullyContains(SourceRange, DeclarationRange))
					return (true);
			return (false);
		}

		/**
		 * Checks if the statement overlaps with the environment. Returns true if
		 * at least one variable referenced in the statement has been declared outside
		 * the pattern.
		 * @param Statement an arbitrary statement.
		 * @return true if the statement overlaps with the environment.
		 */
		bool OverlapsWithEnvironment(clang::Stmt* Statement){
			//Check if at least one declaration is outside the code region
			for(auto DeclarationRange : GetDeclarationSourceRanges(Statement))
				if(!FullyContains(SourceRange, DeclarationRange))
					return (true);
			return (false);
		}
};
