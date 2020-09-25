#pragma once

#include "clang/AST/RecursiveASTVisitor.h"

/**
 * Counts the attributes for data functions. More specifically,
 * it counts the number of data element types and record element types.
 * Data functions are represented via variables which occur either as
 * explicit declarations or via implicit references.
 */
class DataFunctionVisitor : public clang::RecursiveASTVisitor<DataFunctionVisitor>{
	public:
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
		 * Reference to the AST context to retrieve primitive data types.
		 */
		clang::ASTContext* Context;

		/**
		 * Creates a new instance of the visitor.
		 * @param myContext The context over the current translation unit.
		 */
		DataFunctionVisitor(clang::ASTContext* myContext);
		/**
		 * As much information as possible should be used
		 * to count the attributes.
		 *
		 * @return true
		 */
		bool shouldVisitImplicitCode() const;
		/**
		 * Continues the tree traversal with the declaration of argument.
		 * @param Node The node associated with the expression.
		 * @return false if the visitation was terminated early, true otherwise
		 */
		bool VisitDeclRefExpr(clang::DeclRefExpr* Node);
		/**
		 * Primitive data types only have a single data and record element type.
		 * More complex structures use the number of fields for the former
		 * and the number of constructors for the latter.
		 * @param Node The node associated with the declaration.
		 * @return false if the visitation was terminated early, true otherwise
		 */
		bool VisitVarDecl(clang::VarDecl* Node);
};

/**
 * Counts the attributes of a complex data type.
 */
class ObjectVisitor : public clang::RecursiveASTVisitor<ObjectVisitor>{
	public:
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
		/**
		 * Classes contain additional bloat invisible to the user that
		 * has to be ignored.
		 *
		 * @return false
		 */
		bool shouldVisitImplicitCode() const;
		/**
		 * A field represents a variable and counts as a data element type.
		 * @param Node The node associated with the field.
		 * @return true
		 */
		bool VisitFieldDecl(clang::FieldDecl* Node);
		/**
		 * Represents a single method declaration and counts as a data element type.
		 * @param Node The node associated with the method.
		 * @return false if the visitation was terminated early, true otherwise
		 */
		bool VisitCXXMethodDecl(clang::CXXMethodDecl* Node);
		//Has to be done this way to filter methods from constructors & stuff
		/**
		 * Represents a constructor and counts as record element type.
		 * @param Node The node associated with the constructor.
		 * @return true
		 */
		bool WalkUpFromCXXConstructorDecl(clang::CXXConstructorDecl* Node);
		/**
		 * A dummy method the destructors. They are considered to be methods,
		 * so this function has to be implemented in order to exclude
		 * the node from {@link VisitCXXMethodDecl}.
		 *
		 * @param Node the node associated with the destructor.
		 * @return true
		 */
		bool WalkUpFromCXXDestructorDecl(clang::CXXDestructorDecl* Node);
		/**
		 * A dummy method for conversion declarations. They are considered to
		 * be methods, so this function has to be implemented in order to exclude
		 * the node from {@link VisitCXXMethodDecl}.
		 *
		 * @param Node the node associated with the conversion declarations.
		 * @return true
		 */
		bool WalkUpFromCXXConversionDecl(clang::CXXConversionDecl* Node);
		/**
		 * Visits the class declaration to count the total number of base classes.
		 * Each base class is a potential subgroup and thus a record element type.
		 *
		 * @param Node the node associated with the current class.
		 * @return true
		 */
		bool VisitCXXRecordDecl(clang::CXXRecordDecl* Node);
};
