#pragma once

#include "clang/AST/RecursiveASTVisitor.h"

/**
 * Counts the attributes for data functions. More specifically,
 * it counts the number of data element types and record element types.
 */
struct DataFunctionVisitor : public clang::RecursiveASTVisitor<DataFunctionVisitor>{
	/**
	 * Contains the number of data element types. It relates to the total
	 * number of attributes of the type.
	 */
	int det = 0;
	/**
	 * Contains the number of record element types. It relates to the total
	 * number of constructors.
	 */
	int ret = 0;
	/**
	 * Flag indicating that the declaration is a variable.
	 */
	bool IsVariable;
	/**
	 * Reference to the AST context to retrieve primitive data types.
	 */
	clang::ASTContext* Context;

	DataFunctionVisitor(clang::ASTContext* myContext);
	bool shouldVisitImplicitCode() const;
	bool VisitDeclRefExpr(clang::DeclRefExpr* Node);
	bool VisitVarDecl(clang::VarDecl* Node);
};

struct RecordVisitor : public clang::RecursiveASTVisitor<RecordVisitor>{
	/**
	 * Contains the number of data element types. It relates to the total
	 * number of methods and variables.
	 */
	int det = 0;
	/**
	 * Contains the number of data element types. It relates to the total
	 * number of constructors.
	 */
	int ret = 0;

	bool shouldVisitImplicitCode() const;
	bool VisitFieldDecl(clang::FieldDecl* Node);
	bool VisitCXXMethodDecl(clang::CXXMethodDecl* Node);
	//Has to be done this way to filter methods from constructors & stuff
	bool WalkUpFromCXXConstructorDecl(clang::CXXConstructorDecl* Node);
	bool WalkUpFromCXXDestructorDecl(clang::CXXDestructorDecl* Node);
	bool WalkUpFromCXXConversionDecl(clang::CXXConversionDecl* Node);
};
