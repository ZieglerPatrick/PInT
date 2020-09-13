#include "TestTransactionalFunction.h"
#include "PatternInstrumentation.h"

void testExternalInput(){
	int x = 1, y = 2;
	PatternInstrumentation::Pattern_Begin("Test EI EIConditional");
	{
		x = x > 0 ? x : y;
	}
	PatternInstrumentation::Pattern_End("EIConditional");
	
	PatternInstrumentation::Pattern_Begin("Test EI EIAssignment");
	{
		int z;
		z = 42;		//Not an external input
		z = y;		//External input
	}
	PatternInstrumentation::Pattern_End("EIAssignment");	
	
	PatternInstrumentation::Pattern_Begin("Test EI EIBinary");
	{
		x = x + y;
	}
	PatternInstrumentation::Pattern_End("EIBinary");

	PatternInstrumentation::Pattern_Begin("Test EI EIUnary");
	{
		x++;
	}
	PatternInstrumentation::Pattern_End("EIUnary");

	PatternInstrumentation::Pattern_Begin("Test EI EIVarDecl");
	{
		int z = x;
	}
	PatternInstrumentation::Pattern_End("EIVarDecl");
	
}

void testExternalOutput(){
	double x = 1;
	int y = 2;
	int z = 3;
	
	PatternInstrumentation::Pattern_Begin("Test EO EOAssignment");
	{
		x = x * y * z;
	}
	PatternInstrumentation::Pattern_End("EOAssignment");	
}
