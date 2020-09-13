#include "metric/halstead/HalsteadVisitor.h"

HalsteadVisitor::HalsteadVisitor(clang::ASTContext* myContext) :
		ClangPatternVisitor(myContext){
}

bool HalsteadVisitor::shouldVisitImplicitCode() const{
	return (true);
}

//
// Operands
//

bool HalsteadVisitor::WalkUpFromCharacterLiteral(clang::CharacterLiteral* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::WalkUpFromCXXBoolLiteralExpr(clang::CXXBoolLiteralExpr* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::WalkUpFromCXXNullPtrLiteralExpr(clang::CXXNullPtrLiteralExpr* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::WalkUpFromFixedPointLiteral(clang::FixedPointLiteral* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::WalkUpFromFloatingLiteral(clang::FloatingLiteral* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::WalkUpFromImaginaryLiteral(clang::ImaginaryLiteral* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::WalkUpFromIntegerLiteral(clang::IntegerLiteral* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::WalkUpFromObjCArrayLiteral(clang::ObjCArrayLiteral* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::WalkUpFromObjCBoolLiteralExpr(clang::ObjCBoolLiteralExpr* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::WalkUpFromObjCDictionaryLiteral(clang::ObjCDictionaryLiteral* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::WalkUpFromObjCStringLiteral(clang::ObjCStringLiteral* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::WalkUpFromStringLiteral(clang::StringLiteral* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::WalkUpFromDeclRefExpr(clang::DeclRefExpr* Node){
	return (HandleOperand(Node));
}

bool HalsteadVisitor::HandleOperand(clang::Stmt* Node){
	if(CodeRegions.empty())
		return (true);

	std::vector<PatternCodeRegion*> AllCodeRegions;
	PatternCodeRegion* Current = CodeRegions.back();

	GraphAlgorithms::FindAllParentPatternCodeRegions(Current, AllCodeRegions);
	AllCodeRegions.push_back(Current);

	for(PatternCodeRegion* CodeRegion : CodeRegions)
		CodeRegion -> GetPatternOccurrence() -> GetPattern() -> IncrementNumberOfOperands(Node -> getStmtClassName());
	return (true);
}

//
// Operators
//

bool HalsteadVisitor::VisitDecl(clang::Decl* Node){
	return (HandleOperator(Node));
}

bool HalsteadVisitor::VisitStmt(clang::Stmt* Node){
	return (HandleOperator(Node));
}

bool HalsteadVisitor::HandleOperator(clang::Decl* Node){
	return (HandleOperator(Node -> getDeclKindName()));
}

bool HalsteadVisitor::HandleOperator(clang::Stmt* Node){
	return (HandleOperator(Node -> getStmtClassName()));
}

bool HalsteadVisitor::HandleOperator(std::string Node){
	if(CodeRegions.empty())
		return (true);

	std::vector<PatternCodeRegion*> AllCodeRegions;
	PatternCodeRegion* Current = CodeRegions.back();

	GraphAlgorithms::FindAllParentPatternCodeRegions(Current, AllCodeRegions);
	AllCodeRegions.push_back(Current);

	for(PatternCodeRegion* CodeRegion : AllCodeRegions)
		CodeRegion -> GetPatternOccurrence() -> GetPattern() -> IncrementNumberOfOperators(Node);
	return (true);
}

//
// Pattern Hook Point
//

void HalsteadVisitor::VisitPatternCodeRegion(PatternCodeRegion* CodeRegion){
	CodeRegions.push_back(CodeRegion);
}

void HalsteadVisitor::EndVisitPatternCodeRegion(PatternCodeRegion* CodeRegion){
	Preconditions::CheckArgument(
		!CodeRegions.empty(),
		std::out_of_range("Tried to remove " + CodeRegion -> GetPatternOccurrence() -> GetPattern() -> GetPatternName() + " but stack was empty.")
	);

	CodeRegions.pop_back();
}

//
// Misc
//

bool HalsteadVisitor::WalkUpFromExprWithCleanups(clang::ExprWithCleanups* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
	//Fuck if I know where they come from...
	//They appear in combination with Pattern_Begin and Pattern_End, so we void 'em
	return (true);
}

bool HalsteadVisitor::WalkUpFromImplicitCastExpr(clang::ImplicitCastExpr* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
	return (true);
}
