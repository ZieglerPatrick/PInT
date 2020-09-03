#pragma once

#include "clang/Frontend/FrontendActions.h"

class DelegatorFrontendAction : public clang::ASTFrontendAction {
	public:
		virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &Compiler, llvm::StringRef InFile);
};
