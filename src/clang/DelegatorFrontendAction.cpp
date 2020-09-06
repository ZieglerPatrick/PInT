#include "clang/DelegatorFrontendAction.h"
#include "clang/ASTConsumerDelegator.h"

std::unique_ptr<clang::ASTConsumer> DelegatorFrontendAction::CreateASTConsumer(clang::CompilerInstance &Compiler, llvm::StringRef InFile){
	static_cast<void>(InFile); //Avoid unused parameter warning
	return (std::unique_ptr<clang::ASTConsumer>(new ASTConsumerDelegator(&Compiler.getASTContext())));
}
