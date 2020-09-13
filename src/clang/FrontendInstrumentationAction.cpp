#include "clang/ASTFrontendInstrumentationAction.h"
#include "clang/ASTInstrumentationConsumer.h"

std::unique_ptr<clang::ASTConsumer> ASTFrontendInstrumentationAction::CreateASTConsumer(
		clang::CompilerInstance& myCompiler,
		llvm::StringRef myFile
)
{
	static_cast<void>(myFile); //Avoid unused parameter warning
	return (std::unique_ptr<clang::ASTConsumer>(new ASTInstrumentationConsumer(&myCompiler.getASTContext())));
}
