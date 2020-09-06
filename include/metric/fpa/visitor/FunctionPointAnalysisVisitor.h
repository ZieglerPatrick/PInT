#pragma once

#include "visitor/ClangPatternVisitor.h"
#include "metric/fpa/FunctionPoint.h"

class FunctionPointAnalysisVisitor : public ClangPatternVisitor<FunctionPointAnalysisVisitor>{
	public:
		explicit FunctionPointAnalysisVisitor(
				std::shared_ptr<PatternMap> myPatternBegin,
				std::shared_ptr<PatternMap> myPatternEnd,
				clang::ASTContext* myContext
		);

		//Hookpoint for the AST visitor
		bool TraverseDeclRefExpr(clang::DeclRefExpr* Node);
		bool TraverseVarDecl(clang::VarDecl* Node);
		bool TraverseUnaryOperator(clang::UnaryOperator* Node);
		bool TraverseBinaryOperator(clang::BinaryOperator* Node);
		bool TraverseAbstractConditionalOperator(clang::AbstractConditionalOperator* Node);

		//Hookpoint for the pattern visitor
		virtual void VisitPatternCodeRegion(PatternCodeRegion* PatternCodeRegion) override;
		virtual void EndVisitPatternCodeRegion(PatternCodeRegion* PatternCodeRegion) override;

	protected:
		clang::ASTContext* Context;
		/**
		 * Contains the current code region, as well as all parent code regions.
		 * A function point encountered in the current region will also exist in all parents.
		 */
		std::vector<PatternCodeRegion*> CodeRegions;
	private:
		/**
		 * Adds the function point to all code regions containing it.
		 * @param NewFunctionPoint an arbitrary function point
		 */
		void AddFunctionPoint(FunctionPoint* NewFunctionPoint);
};
