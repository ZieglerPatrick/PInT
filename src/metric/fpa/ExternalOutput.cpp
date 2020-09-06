#include "metric/fpa/ExternalOutput.h"
#include <vector>

#define DET_LOW		(5)
#define DET_MEDIUM 	(19)
#define FTR_LOW		(1)
#define FTR_MEDIUM	(3)

ExternalOutput::ExternalOutput(int DataElementType, int FileTypeReferenced, std::string Label) :
	FunctionPoint(DataElementType, 0, FileTypeReferenced, Label){
}

int ExternalOutput::GetWeight(){
	static std::vector<int> Weights = {4, 5, 7};
	return (Weights[this -> GetComplexity()]);
}

std::string ExternalOutput::GetType(){
	return ("EO");
}

FunctionPointComplexity ExternalOutput::GetComplexity(){
	if(this -> ftr <= FTR_LOW)
		if(this -> det <= DET_LOW)
			return (LOW);
		else if(this -> det <= DET_MEDIUM)
			return (LOW);
		else
			return (AVERAGE);
	else if(this -> ftr <= FTR_MEDIUM )
		if(this -> det <= DET_LOW)
			return (LOW);
		else if(this -> det <= DET_LOW)
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
