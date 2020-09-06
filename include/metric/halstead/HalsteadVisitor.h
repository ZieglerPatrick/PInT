#pragma once

#include "visitor/ClangPatternVisitor.h"

class HalsteadVisitor : public ClangPatternVisitor<HalsteadVisitor>{
	public:
		explicit HalsteadVisitor(
			std::shared_ptr<PatternMap> myPatternBegin,
			std::shared_ptr<PatternMap> myPatternEnd
		);
		bool shouldVisitImplicitCode() const;
		// -----------------------------------------------------------------------------
		// Operands
		//   - Literals
		//   - Variables
		// -----------------------------------------------------------------------------
		// Override WalkUpFrom instead of Visit s.t. the nodes won't appear in VisitStmt
		bool WalkUpFromCharacterLiteral(clang::CharacterLiteral* Node);
		bool WalkUpFromCXXBoolLiteralExpr(clang::CXXBoolLiteralExpr* Node);
		bool WalkUpFromCXXNullPtrLiteralExpr(clang::CXXNullPtrLiteralExpr* Node);
		bool WalkUpFromFixedPointLiteral(clang::FixedPointLiteral* Node);
		bool WalkUpFromFloatingLiteral(clang::FloatingLiteral* Node);
		bool WalkUpFromImaginaryLiteral(clang::ImaginaryLiteral* Node);
		bool WalkUpFromIntegerLiteral(clang::IntegerLiteral* Node);
		bool WalkUpFromObjCArrayLiteral(clang::ObjCArrayLiteral* Node);
		bool WalkUpFromObjCBoolLiteralExpr(clang::ObjCBoolLiteralExpr* Node);
		bool WalkUpFromObjCDictionaryLiteral(clang::ObjCDictionaryLiteral* Node);
		bool WalkUpFromObjCStringLiteral(clang::ObjCStringLiteral* Node);
		bool WalkUpFromStringLiteral(clang::StringLiteral* Node);
		bool WalkUpFromDeclRefExpr(clang::DeclRefExpr* Node);
		// -----------------------------------------------------------------------------
		// Operators
		// 	- Keywords (goto, for, ;. ->)
		// 	- Operators (+, -, *, ...)
		// 	- Function Calls
		// 	- (everything not an operand)
		// -----------------------------------------------------------------------------
		bool VisitDecl(clang::Decl* Node);
		bool VisitStmt(clang::Stmt* Node);
		// -----------------------------------------------------------------------------
		// Operators
		// 	- Keywords (goto, for, ;. ->)
		// 	- Operators (+, -, *, ...)
		// 	- Function Calls
		// 	- (everything not an operand)
		// -----------------------------------------------------------------------------
		virtual void VisitParallelPattern(HPCParallelPattern* ParallelPattern) override;
		virtual void EndVisitParallelPattern(HPCParallelPattern* ParallelPattern) override;
	private:
		std::vector<HPCParallelPattern*> ParallelPatterns;
		bool HandleOperand(clang::Stmt* Node);
		bool HandleOperator(clang::Decl* Node);
		bool HandleOperator(clang::Stmt* Node);
		bool HandleOperator(std::string Node);
};
