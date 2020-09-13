#pragma once

#include "metric/fpa/PrettyPrinter.h"
#include "metric/fpa/visitor/FunctionPointVisitor.h"
#include "metric/fpa/visitor/DataFunctionVisitor.h"
#include "metric/fpa/visitor/TransactionalFunctionVisitor.h"
#include "metric/fpa/InternalLogicalFile.h"
#include "metric/fpa/ExternalInterfaceFile.h"
#include "metric/fpa/ExternalOutput.h"

/**
 * Extracts the data functions in an expression. If a variable has been declared outside
 * the range of the closest pattern code region, it is an external interface file, otherwise
 * an internal logical file.
 * @tparam Derived The the visitor implementing this template.
 */
template <typename Derived> class DeclRefExprVisitor : public FunctionPointVisitor<Derived>{
	public:
		/**
		 * Creates a new instance of the visitor.
		 *
		 * @param myContext The context required when comparing two source locations.
		 * @param mySourceRange The range of the closest pattern code region.
		 */
		explicit DeclRefExprVisitor(
				clang::ASTContext* myContext,
				clang::SourceRange mySourceRange
		) :
			FunctionPointVisitor<Derived>(myContext, mySourceRange){
		}

		/**
		 * A declaration reference may be a function call or a variable reference. In the latter case,
		 * the variable will be counted as an internal logical file, if it has been declared inside the
		 * closest pattern code region. Otherwise it is an external interface file.
		 * @param Node the node associated with the expression.
		 * @return false if the visitation was terminated early, true otherwise.
		 */
		bool TraverseDeclRefExpr(clang::DeclRefExpr* Node){
			return (this -> TraverseDecl(Node ->getFoundDecl()));
		}

		/**
		 * A function will be counted as an external output if it has been declared
		 * outside the code region.
		 * @param Node the node associated with the function reference.
		 * @return true
		 */
		bool VisitFunctionDecl(clang::FunctionDecl* Node){
			TransactionalFunctionVisitor Visitor;
			Visitor.TraverseDecl(Node);

			if(FunctionPointVisitor<Derived>::OverlapsWithEnvironment(Node)){
				FunctionPoint* FunctionPoint = new ExternalOutput(
						Visitor.det,
						Visitor.ftr,
						PrettyPrinter::PrintPretty(Node)
				);

				this -> FunctionPoints.push_back(FunctionPoint);
			}

			return (true);
		}

		/**
		 * A variable will be counted as an internal logical file, if it has been declared inside the
		 * closest pattern code region. Otherwise it is an external interface file.
		 * @param Node the node associated with the variable reference.
		 * @return true
		 */
		bool VisitVarDecl(clang::VarDecl* Node){
			DataFunctionVisitor Visitor(this -> Context);
			Visitor.TraverseDecl(Node);

			if(FunctionPointVisitor<Derived>::OverlapsWithPattern(Node)){
				FunctionPoint* FunctionPoint = new InternalLogicalFile(
						Visitor.det,
						Visitor.ret,
						PrettyPrinter::PrintPretty(Node)
				);

				this -> FunctionPoints.push_back(FunctionPoint);
			}else{
				FunctionPoint* FunctionPoint = new ExternalInterfaceFile(
						Visitor.det,
						Visitor.ret,
						PrettyPrinter::PrintPretty(Node)
				);

				this -> FunctionPoints.push_back(FunctionPoint);
			}

			return (true);
		}
};

/**
 * A concrete implementation of the template, only counting the data functions inside an expression.
 */
class DeclRefExprVisitorImplementation : public DeclRefExprVisitor<DeclRefExprVisitorImplementation>{
	public:
		/**
		 * Creates a new instance of the visitor.
		 *
		 * @param myContext The context required when comparing two source locations.
		 * @param mySourceRange The range of the closest pattern code region.
		 */
		explicit DeclRefExprVisitorImplementation(
				clang::ASTContext* myContext,
				clang::SourceRange mySourceRange
		);
};
