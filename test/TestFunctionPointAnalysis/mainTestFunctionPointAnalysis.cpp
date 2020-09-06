#include "TestDataFunction.h"
#include "TestTransactionalFunction.h"

int main(int argc, char* argv[]){
	testInternalLogicalFile();
	testExternalInterfaceFile();
	testExternalInput();
	testExternalOutput();
	return 0;
}
