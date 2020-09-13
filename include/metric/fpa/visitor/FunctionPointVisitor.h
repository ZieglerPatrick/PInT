#pragma once

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/SourceManager.h"
#include "metric/fpa/FunctionPoint.h"

/**
 * Base class for the individual AST visitors.
 * @tparam Derived The the visitor implementing this template.
 */
template <typename Derived> class FunctionPointVisitor : public clang::RecursiveASTVisitor<Derived>{
	public:
		/**
		 * Creates a new instance of the visitor.
		 *
		 * @param myContext The context required when comparing two source locations.
		 * @param mySourceRange The range of the closest pattern code region.
		 */
		explicit FunctionPointVisitor(
				clang::ASTContext* myContext,
				clang::SourceRange mySourceRange
		) :
			CodeRegionSourceRange(mySourceRange),
			IsBefore(myContext -> getSourceManager()),
			Context(myContext){
		}
		/**
		 * Contains all function points that have been detected by this visitor.
		 */
		std::vector<FunctionPoint*> FunctionPoints;
	private:

		/**
		 * The source range of the closest pattern code region.
		 */
		clang::SourceRange CodeRegionSourceRange;
		/**
		 * A helper function determining the order in which two source locations appear.
		 */
		clang::BeforeThanCompare<clang::SourceLocation> IsBefore;

		/**
		 * Checks if the source location is inside the code region.
		 * @param SourceLocation An arbitrary position in the code.
		 * @return true if the location is enclosed by the pattern code region.
		 */
		bool Contains(clang::SourceLocation SourceLocation){
			if(IsBefore(SourceLocation, CodeRegionSourceRange.getBegin()))
				return (false);
			if(IsBefore(CodeRegionSourceRange.getEnd(), SourceLocation))
				return (false);
			return (true);
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
	protected:
		/**
		 * The context is required to determine the order between source locations.
		 */
		clang::ASTContext* Context;

		/**
		 * Checks if the provided source range intersects with the environment. I.e.
		 * if it either start before or ends after the code region.
		 * @param SourceRange an arbitrary source range.
		 * @return true if the source range overlaps with the environment.
		 */
		bool OverlapsWithEnvironment(clang::SourceRange SourceRange){
			return (!Contains(SourceRange.getBegin()) || !Contains(SourceRange.getEnd()));
		}

		/**
		 * Checks if the statement overlaps with the environment.
		 * @param Node an arbitrary statement.
		 * @return true if the statement overlaps with the environment.
		 */
		bool OverlapsWithEnvironment(clang::Stmt* Node){
			//Check if at least one declaration is outside the code region
			for(auto DeclarationSourceRange : GetDeclarationSourceRanges(Node))
				if(OverlapsWithEnvironment(DeclarationSourceRange))
					return (true);
			return (false);
		}

		/**
		 * Checks if the declaration overlaps with the environment.
		 * @param Node an declaration declaration.
		 * @return true if the statement overlaps with the environment.
		 */
		bool OverlapsWithEnvironment(clang::Decl* Node){
			return (OverlapsWithEnvironment(Node -> getSourceRange()));
		}

		/**
		 * Checks if the provided source range intersects with the code region. I.e.
		 * if its begin or end is included by the code region..
		 * @param SourceRange an arbitrary source range.
		 * @return true if the source range overlaps with the code region.
		 */
		bool OverlapsWithPattern(clang::SourceRange SourceRange){
			return (Contains(SourceRange.getBegin()) || Contains(SourceRange.getEnd()));
		}

		/**
		 * Checks if the statement overlaps with the pattern code region.
		 * @param Statement an arbitrary statement.
		 * @return true if the statement overlaps with the code region.
		 */
		bool OverlapsWithPattern(clang::Stmt* Node){
			//Check if at least one declaration is outside the code region
			for(auto DeclarationSourceRange : GetDeclarationSourceRanges(Node))
				if(OverlapsWithPattern(DeclarationSourceRange))
					return (true);
			return (false);
		}

		/**
		 * Checks if the declaration overlaps with the pattern code region.
		 * @param Node an arbitrary declaration.
		 * @return true if the declaration overlaps with the code region.
		 */
		bool OverlapsWithPattern(clang::Decl* Node){
			return (OverlapsWithPattern(Node -> getSourceRange()));
		}
};
