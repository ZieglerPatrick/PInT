#include "metric/halstead/HalsteadVisitor.h"

HalsteadVisitor::HalsteadVisitor
(
	std::shared_ptr<PatternMap> NewPatternBegin,
	std::shared_ptr<PatternMap> NewPatternEnd
) :
	ClangPatternVisitor(NewPatternBegin, NewPatternEnd){
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
	static_cast<void>(Node); //Avoid unused parameter warning

	for(HPCParallelPattern* ParallelPattern : ParallelPatterns)
		ParallelPattern -> IncrementNumberOfOperands(Node ->getStmtClassName());
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
	static_cast<void>(Node); //Avoid unused parameter warning
	return (HandleOperator(Node -> getDeclKindName()));
}

bool HalsteadVisitor::HandleOperator(clang::Stmt* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
	return (HandleOperator(Node -> getStmtClassName()));
}

bool HalsteadVisitor::HandleOperator(std::string Node){
	for(HPCParallelPattern* ParallelPattern : ParallelPatterns)
		ParallelPattern -> IncrementNumberOfOperators(Node);
	return (true);
}

//
// Pattern Hook Point
//

void HalsteadVisitor::VisitParallelPattern(HPCParallelPattern* ParallelPattern){
	ParallelPatterns.push_back(ParallelPattern);
}

void HalsteadVisitor::EndVisitParallelPattern(HPCParallelPattern* ParallelPattern){
	Preconditions::CheckArgument(
		!ParallelPatterns.empty(),
		std::out_of_range("Tried to remove " + ParallelPattern -> GetPatternName() + " but stack was empty.")
	);

	ParallelPatterns.pop_back();
}
