#include "TreeVisualisation.h"

#include <iostream>



/**
 * @brief Prints the call tree recursively, beginning with the main function.
 *
 * @param maxdepth The maximum recursion (i.e., output depth)
 **/
void CallTreeVisualisation::PrintCallTree(int maxdepth)
{
	FunctionDeclDatabase* FuncDB = FunctionDeclDatabase::GetInstance();
	
	FunctionDeclDatabaseEntry* MainFnEntry = FuncDB->GetMainFnEntry();
	PrintFunction(MainFnEntry, 0, maxdepth);
}

/**
 * @brief Prints a pattern in the pattern tree with spacing according to the recursion depth.
 *
 * @param CodeRegion The code region from which the pattern is printed.
 * @param depth The current depth of recursion.
 * @param maxdepth The maximum depth of recursion.
 **/
void CallTreeVisualisation::PrintPattern(PatternCodeRegion* CodeRegion, int depth, int maxdepth)
{
	if (depth > maxdepth)
	{	
		return;
	}
	
	PrintIndent(depth);

	HPCParallelPattern* Pattern = CodeRegion->GetPatternOccurence()->GetPattern();
	std::cout << "\033[36m" << Pattern->GetDesignSpaceStr() << ":\33[33m " << Pattern->GetPatternName() << "\33[0m";

	std::cout << "(" << CodeRegion->GetPatternOccurence()->GetID() << ")" << std::endl;
 
	for (PatternTreeNode* Child : CodeRegion->GetChildren())
	{
		if (FunctionDeclDatabaseEntry* FnCall = clang::dyn_cast<FunctionDeclDatabaseEntry>(Child))
		{
			PrintFunction(FnCall, depth + 1, maxdepth);
		}
		else if (PatternCodeRegion* CodeRegion = clang::dyn_cast<PatternCodeRegion>(Child))
		{
			PrintPattern(CodeRegion, depth + 1, maxdepth);
		}
	}
}
	
/**
 * @brief Prints a function in the pattern tree with indent. 
 *
 * @param FnCall Function call.
 * @param depth Current recursion depth.
 * @param maxdepth Maximum recursion depth.
 **/
void CallTreeVisualisation::PrintFunction(FunctionDeclDatabaseEntry* FnCall, int depth, int maxdepth)
{
	if (depth > maxdepth)
	{	
		return;
	}

	PrintIndent(depth);
	std::cout << "\033[31m" << FnCall->GetFnName() << "\033[0m" << " (Hash: " << FnCall->GetHash() << ")" << std::endl;

	for (PatternTreeNode* Child : FnCall->GetChildren())
	{
		if (FunctionDeclDatabaseEntry* FnCall = clang::dyn_cast<FunctionDeclDatabaseEntry>(Child))
		{
			PrintFunction(FnCall, depth + 1, maxdepth);
		}
		else if (PatternCodeRegion* CodeRegion = clang::dyn_cast<PatternCodeRegion>(Child))
		{
			PrintPattern(CodeRegion, depth + 1, maxdepth);
		}
	}
}
	
/**
 * @brief Prints an indent according to the passed depth.
 *
 * @param depth Depth of indent.
 **/
void CallTreeVisualisation::PrintIndent(int depth)
{
	int i = 0;

	for (; i < depth - 1; i++)
	{
		std::cout << "    ";
	}

	for (; i < depth; i++)
	{
		std::cout << "--> ";
	}
}
