#include "metric/fpa/ExternalInterfaceFile.h"
#include <vector>

#define RET_LOW		(1)
#define RET_MEDIUM	(5)
#define DET_LOW		(19)
#define DET_MEDIUM 	(50)

ExternalInterfaceFile::ExternalInterfaceFile(int DataElementType, int RecordElementType, std::string Label) :
	FunctionPoint(DataElementType, RecordElementType, 0, Label){
}

int ExternalInterfaceFile::GetWeight(){
	static std::vector<int> Weights = {5, 7, 10};
	return (Weights[this -> GetComplexity()]);
}

std::string ExternalInterfaceFile::GetType(){
	return ("EIF");
}

FunctionPointComplexity ExternalInterfaceFile::GetComplexity(){
	if(this -> ret <= RET_LOW)
		if(this -> det <= DET_LOW)
			return (LOW);
		else if(this -> det <= DET_MEDIUM)
			return (LOW);
		else
			return (AVERAGE);
	else if(this -> ret <= RET_MEDIUM)
		if(this -> det <= DET_LOW)
			return (LOW);
		else if(this -> det <= DET_MEDIUM)
			return (AVERAGE);
		else
			return (HIGH);
	else
		if(this -> det <= DET_LOW)
			return (AVERAGE);
		else if(this -> det <= DET_MEDIUM)
			return (HIGH);
		else
			return (HIGH);
}
