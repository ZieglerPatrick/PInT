#include "clang/ASTFrontendDelegatorAction.h"
#include "clang/ASTDelegatorConsumer.h"

std::unique_ptr<clang::ASTConsumer> ASTFrontendDelegatorAction::CreateASTConsumer(
		clang::CompilerInstance& myCompiler,
		llvm::StringRef myFile
)
{
	static_cast<void>(myFile); //Avoid unused parameter warning
	return (std::unique_ptr<clang::ASTConsumer>(new ASTDelegatorConsumer(&myCompiler.getASTContext())));
}
