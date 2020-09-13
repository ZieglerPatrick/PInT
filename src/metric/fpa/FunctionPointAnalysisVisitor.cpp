#include "metric/fpa/FunctionPointAnalysisVisitor.h"
#include "metric/fpa/visitor/DeclRefExprVisitor.h"
#include "metric/fpa/visitor/BinaryOperatorVisitor.h"
#include "metric/fpa/visitor/AssignmentOperatorVisitor.h"
#include "metric/fpa/visitor/VarDeclVisitor.h"
#include "metric/fpa/visitor/UnaryOperatorVisitor.h"
#include "metric/fpa/visitor/AbstractConditionalOperatorVisitor.h"

FunctionPointAnalysisVisitor::FunctionPointAnalysisVisitor(clang::ASTContext* myContext) :
		ClangPatternVisitor(myContext),
		Context(myContext){
}

bool FunctionPointAnalysisVisitor::TraverseDeclRefExpr(clang::DeclRefExpr* Node){
	if(!CodeRegions.empty()){
		DeclRefExprVisitorImplementation Visitor(Context, CodeRegions.back() -> GetSourceRange());
		Visitor.TraverseDeclRefExpr(Node);

		for(FunctionPoint* FunctionPoint : Visitor.FunctionPoints)
			AddFunctionPoint(FunctionPoint);
	}

	return (true);
}

bool FunctionPointAnalysisVisitor::TraverseVarDecl(clang::VarDecl* Node){
	if(!CodeRegions.empty()){
		VarDeclVisitor Visitor(Context, CodeRegions.back() -> GetSourceRange());
		Visitor.TraverseVarDecl(Node);

		for(FunctionPoint* FunctionPoint : Visitor.FunctionPoints)
			AddFunctionPoint(FunctionPoint);
	}
	return (true);
}

bool FunctionPointAnalysisVisitor::TraverseUnaryOperator(clang::UnaryOperator* Node){
	if(!CodeRegions.empty()){
		UnaryOperatorVisitor Visitor(Context, CodeRegions.back() -> GetSourceRange());
		Visitor.TraverseUnaryOperator(Node);

		for(FunctionPoint* FunctionPoint : Visitor.FunctionPoints)
			AddFunctionPoint(FunctionPoint);
	}

	return (true);
}

bool FunctionPointAnalysisVisitor::TraverseBinaryOperator(clang::BinaryOperator* Node){
	if(!CodeRegions.empty()){
		std::vector<FunctionPoint*> FunctionPoints;
		if(Node ->isCompoundAssignmentOp() || Node -> isAssignmentOp()){
			AssignmentOperatorVisitor Visitor(Context, CodeRegions.back() -> GetSourceRange());
			Visitor.TraverseBinaryOperator(Node);
			FunctionPoints = Visitor.FunctionPoints;
		}else{
			BinaryOperatorVisitor Visitor(Context, CodeRegions.back() -> GetSourceRange());
			Visitor.TraverseBinaryOperator(Node);
			FunctionPoints = Visitor.FunctionPoints;
		}

		for(FunctionPoint* FunctionPoint : FunctionPoints)
			AddFunctionPoint(FunctionPoint);
	}

	return (true);
}

bool FunctionPointAnalysisVisitor::TraverseAbstractConditionalOperator(clang::AbstractConditionalOperator* Node){
	if(!CodeRegions.empty()){
		AbstractConditionalOperatorVisitor Visitor(Context, CodeRegions.back() -> GetSourceRange());

		//No idea why TraverseAbstractConditionalOperator doesn't exist
		//¯\_(ツ)_/¯
		Visitor.TraverseStmt(Node);

		for(FunctionPoint* FunctionPoint : Visitor.FunctionPoints)
			AddFunctionPoint(FunctionPoint);
	}

	return (true);
}

void FunctionPointAnalysisVisitor::VisitPatternCodeRegion(PatternCodeRegion* PatternCodeRegion){
	CodeRegions.push_back(PatternCodeRegion);
}

void FunctionPointAnalysisVisitor::EndVisitPatternCodeRegion(PatternCodeRegion* PatternCodeRegion){
	Preconditions::CheckArgument(
		!CodeRegions.empty(),
		std::out_of_range("Tried to remove " + PatternCodeRegion -> GetPatternOccurrence() -> GetPattern() -> GetPatternName() + " but stack was empty.")
	);

	CodeRegions.pop_back();
}

//-------------------------------------------------------------------------------//
//
//		Helper Functions
//
//-------------------------------------------------------------------------------//

void FunctionPointAnalysisVisitor::AddFunctionPoint(FunctionPoint* NewFunctionPoint){
	if(CodeRegions.empty())
		return;

	std::vector<PatternCodeRegion*> AllCodeRegions;
	PatternCodeRegion* Current = CodeRegions.back();

	GraphAlgorithms::FindAllParentPatternCodeRegions(Current, AllCodeRegions);
	AllCodeRegions.push_back(Current);

	for(auto CodeRegion : AllCodeRegions){
		CodeRegion -> GetPatternOccurrence() -> GetPattern() -> AddFunctionPoint(
				NewFunctionPoint
		);
	}
}
