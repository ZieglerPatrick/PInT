#pragma once

#include "clang/Frontend/FrontendActions.h"

/**
 * This class is the hook point for the clang library.
 * @see ASTConsumerDelegator
 */
class DelegatorFrontendAction : public clang::ASTFrontendAction {
	public:
		virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &Compiler, llvm::StringRef InFile);
};
