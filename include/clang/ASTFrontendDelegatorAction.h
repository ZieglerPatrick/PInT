#pragma once

#include "clang/Frontend/FrontendActions.h"

/**
 * This class is the hook point for the AST traversal.
 * @see ASTDelegatorConsumer
 */
class ASTFrontendDelegatorAction : public clang::ASTFrontendAction {
	protected:
		/**
		 * Creates the consumer for processing the nodes
		 * @param myCompiler The current compiler instance.
		 * @param myFile The current input file.
		 * @return The new AST consumer. May be null.
		 */
		virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
				clang::CompilerInstance& myCompiler,
				llvm::StringRef myFile
		) override;
};
