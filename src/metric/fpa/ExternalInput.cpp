#include "metric/fpa/ExternalInput.h"
#include <vector>

#define DET_LOW		(4)
#define DET_MEDIUM 	(15)
#define FTR_LOW		(1)
#define FTR_MEDIUM	(2)

ExternalInput::ExternalInput(int myDataElementTypes, int myFileTypesReferenced, std::string myLabel) :
	FunctionPoint(myDataElementTypes, 0, myFileTypesReferenced, myLabel){
}

int ExternalInput::GetWeight(){
	static std::vector<int> Weights = {3, 4, 6};
	return (Weights[this -> GetComplexity()]);
}

std::string ExternalInput::GetType(){
	return ("EI");
}

FunctionPointComplexity ExternalInput::GetComplexity(){
	if(this -> FileTypesReferenced <= FTR_LOW)
		if(this -> DataElementTypes <= DET_LOW)
			return (LOW);
		else if(this -> DataElementTypes <= DET_MEDIUM)
			return (LOW);
		else
			return (AVERAGE);
	else if(this -> FileTypesReferenced <= FTR_MEDIUM )
		if(this -> DataElementTypes <= DET_LOW)
			return (LOW);
		else if(this -> DataElementTypes <= DET_MEDIUM)
			return (AVERAGE);
		else
			return (HIGH);
	else
		if(this -> DataElementTypes <= DET_LOW)
			return (AVERAGE);
		else if(this -> DataElementTypes <= DET_MEDIUM)
			return (HIGH);
		else
			return (HIGH);
}
