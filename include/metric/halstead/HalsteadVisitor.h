#pragma once

#include "visitor/ClangPatternVisitor.h"

class HalsteadVisitor : public ClangPatternVisitor<HalsteadVisitor>{
	public:
		/**
		 * Creates a new instance of this visitor.
		 *
		 * @param myContext The context required when comparing two source locations.
		 */
		explicit HalsteadVisitor(
				clang::ASTContext* myContext
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
		// Sink
		// Some artificial expressions are excluded
		// -----------------------------------------------------------------------------
		bool WalkUpFromExprWithCleanups(clang::ExprWithCleanups* Node);
		bool WalkUpFromImplicitCastExpr(clang::ImplicitCastExpr* Node);
		// -----------------------------------------------------------------------------
		// Operators
		// 	- Keywords (goto, for, ;. ->)
		// 	- Operators (+, -, *, ...)
		// 	- Function Calls
		// 	- (everything not an operand)
		// -----------------------------------------------------------------------------
		virtual void VisitPatternCodeRegion(PatternCodeRegion* CodeRegion) override;
		virtual void EndVisitPatternCodeRegion(PatternCodeRegion* CodeRegion) override;

	private:
		std::vector<PatternCodeRegion*> CodeRegions;
		bool HandleOperand(clang::Stmt* Node);
		bool HandleOperator(clang::Decl* Node);
		bool HandleOperator(clang::Stmt* Node);
		bool HandleOperator(std::string Node);
};
