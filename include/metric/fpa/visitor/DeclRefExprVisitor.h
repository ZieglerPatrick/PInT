#pragma once

#include "metric/fpa/visitor/FunctionPointVisitor.h"
#include "metric/fpa/visitor/DataFunctionVisitor.h"
#include "metric/fpa/InternalLogicalFile.h"
#include "metric/fpa/ExternalInterfaceFile.h"
#include "metric/fpa/PrintPretty.h"

/**
 * Extracts the function points of declaration reference.
 * If a variable is referenced,
 */
template <typename Derived> class DeclRefExprVisitor : public FunctionPointVisitor<Derived>{
	public:
		explicit DeclRefExprVisitor(clang::ASTContext* myContext, clang::SourceRange mySourceRange) :
			FunctionPointVisitor<Derived>(myContext, mySourceRange){
		}

		bool VisitDeclRefExpr(clang::DeclRefExpr* Node){
			DataFunctionVisitor Visitor(this -> Context);
			Visitor.TraverseDeclRefExpr(Node);

			if(Visitor.IsVariable){
				if(FunctionPointVisitor<Derived>::OverlapsWithPattern(Node)){
					FunctionPoint* FunctionPoint = new InternalLogicalFile(
							Visitor.det,
							Visitor.ret,
							FunctionPointAnalysis::PrintPretty(Node -> getFoundDecl())
					);

					this -> FunctionPoints.push_back(FunctionPoint);
				}else{
					FunctionPoint* FunctionPoint = new ExternalInterfaceFile(
							Visitor.det,
							Visitor.ret,
							FunctionPointAnalysis::PrintPretty(Node -> getFoundDecl())
					);

					this -> FunctionPoints.push_back(FunctionPoint);
				}
			}
			return (true);
		}
};

class DeclRefExprVisitorImplementation : public DeclRefExprVisitor<DeclRefExprVisitorImplementation>{
	public:
		explicit DeclRefExprVisitorImplementation(clang::ASTContext* myContext, clang::SourceRange mySourceRange);
};
