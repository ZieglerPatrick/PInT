#include "TestTransactionalFunction.h"
#include "PatternInstrumentation.h"

void testExternalInput(){
	int x = 1, y = 2;
	PatternInstrumentation::Pattern_Begin("Test EI Test3");
	int z = x * y * y;
	
	int a;
	//Is not an external input
	a = 42;
	//Is an external input
	a = z;
	PatternInstrumentation::Pattern_End("Test3");
}

void testExternalOutput(){
	double x = 1;
	int y = 2;
	PatternInstrumentation::Pattern_Begin("Test EO Test4");
	int z = 3;
	x = x * y * z;
	PatternInstrumentation::Pattern_End("Test4");	
}
