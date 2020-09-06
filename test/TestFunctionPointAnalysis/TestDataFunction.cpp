#include "TestDataFunction.h"
#include "PatternInstrumentation.h"

void testInternalLogicalFile(){
	PatternInstrumentation::Pattern_Begin("Test ILF Test1");
	Person A(32, "Olaf");
	PatternInstrumentation::Pattern_End("Test1");
}

void testExternalInterfaceFile(){
	int x;
	PatternInstrumentation::Pattern_Begin("Test EIF Test2");
	x = 42;
	PatternInstrumentation::Pattern_End("Test2");
}
