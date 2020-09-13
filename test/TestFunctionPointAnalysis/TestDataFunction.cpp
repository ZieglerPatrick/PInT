#include "TestDataFunction.h"
#include "PatternInstrumentation.h"

void foo(){}

void testInternalLogicalFile(){
	PatternInstrumentation::Pattern_Begin("Test ILF ILFDeclRefExpr");
	{
		int x;
		foo();
		x = 42;
	}
	PatternInstrumentation::Pattern_End("ILFDeclRefExpr");
	
	PatternInstrumentation::Pattern_Begin("Test ILF ILFVarDecl");
	{
		Person A(32, "Olaf");
	}
	PatternInstrumentation::Pattern_End("ILFVarDecl");
}

void testExternalInterfaceFile(){
	int x;
	PatternInstrumentation::Pattern_Begin("Test EIF EIFDeclRefExpr");
	{
		x = 42;
	}
	PatternInstrumentation::Pattern_End("EIFDeclRefExpr");
	
	PatternInstrumentation::Pattern_Begin("Test Empty Empty");
	PatternInstrumentation::Pattern_End("Empty");
}
