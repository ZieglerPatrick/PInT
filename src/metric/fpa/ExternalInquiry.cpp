#include "metric/fpa/ExternalInquiry.h"
#include <vector>

#define DET_LOW		(5)
#define DET_MEDIUM 	(19)
#define FTR_LOW		(1)
#define FTR_MEDIUM	(3)

ExternalInquiry::ExternalInquiry(int myDataElementTypes, int myFileTypesReferenced, std::string myLabel) :
	FunctionPoint(myDataElementTypes, 0, myFileTypesReferenced, myLabel){
}

int ExternalInquiry::GetWeight(){
	static std::vector<int> Weights = {3, 4, 6};
	return (Weights[this -> GetComplexity()]);
}

std::string ExternalInquiry::GetType(){
	return ("EQ");
}

FunctionPointComplexity ExternalInquiry::GetComplexity(){
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
		else if(this -> DataElementTypes <= DET_LOW)
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
