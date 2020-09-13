#pragma once

#include "visitor/ClangPatternVisitor.h"
#include "metric/fpa/FunctionPoint.h"

/**
 * This class extracts the function points from the syntax tree.
 * There are three distinct types of nodes we're looking for.

 * - Function aren't inherently pure, so they may change the state
 * of the program, making function calls applicable for external outputs,
 * depending on where they have been declared.
 * - Variables are either external interface files or internal logical files,
 * depending on whether they're declared inside the current pattern code region.
 * - Operators may be either external inputs or external outputs, depending
 * on where the variables they used are located.
 */
class FunctionPointAnalysisVisitor : public ClangPatternVisitor<FunctionPointAnalysisVisitor>{
	public:
		/**
		 * Creates a new instance of this visitor.
		 *
		 * @param myContext The context required when comparing two source locations.
		 */
		explicit FunctionPointAnalysisVisitor(
				clang::ASTContext* myContext
		);

		/**
		 * A declaration reference can either refer to a method or variable.
		 * Variables are data functions, while methods are transactional functions.
		 *
		 * @param Node The node associated with the declaration reference.
		 * @return true
		 */
		bool TraverseDeclRefExpr(clang::DeclRefExpr* Node);
		/**
		 * An explicit variable declaration is an internal logical file.
		 * @param Node The node associated with the variable declaration.
		 * @return true
		 */
		bool TraverseVarDecl(clang::VarDecl* Node);
		/**
		 * An unary operator may be an external input, if one of the used variables
		 * has been declared outside the code region.
		 * @param Node the node associated with the operator.
		 * @return true
		 */
		bool TraverseUnaryOperator(clang::UnaryOperator* Node);
		/**
		 * A binary operator may be an external input, if one of the used variables
		 * has been declared outside the code region.
		 * @param Node the node associated with the operator.
		 * @return true
		 */
		bool TraverseBinaryOperator(clang::BinaryOperator* Node);
		/**
		 * A tenary operator may be an external input, if one of the used variables
		 * has been declared outside the code region.
		 * @param Node the node associated with the operator.
		 * @return true
		 */
		bool TraverseAbstractConditionalOperator(clang::AbstractConditionalOperator* Node);

		/**
		 * Called at the start of a code region, used to indicate that all further
		 * detected function points are a member of that region.
		 * @param PatternCodeRegion The code region that is entered.
		 */
		virtual void VisitPatternCodeRegion(PatternCodeRegion* PatternCodeRegion) override;
		/**
		 * Called at the start of a code region, used to indicate that all further
		 * detected function points are no longer a member of that region.
		 * @param PatternCodeRegion The code region that is left.
		 */
		virtual void EndVisitPatternCodeRegion(PatternCodeRegion* PatternCodeRegion) override;

	protected:
		/*
		 * A reference ot the AST context has to be kept in order to determine
		 * the location of the nodes with respect to pattern code regions.
		 */
		clang::ASTContext* Context;
		/**
		 * A list consisting of the current code region and all its parents.
		 * The latest entry will always be at the end of the vector.
		 * Note that this vector only contains the code regions of the
		 * **current translation unit**. In order to get all parent code regions,
		 * consider using {@link GraphAlgorithms::FindParentPatternCodeRegions}.
		 */
		std::vector<PatternCodeRegion*> CodeRegions;
	private:
		/**
		 * Adds the function point to all code regions containing it.
		 * @param myFunctionPoint an arbitrary function point
		 */
		void AddFunctionPoint(FunctionPoint* myFunctionPoint);
};
