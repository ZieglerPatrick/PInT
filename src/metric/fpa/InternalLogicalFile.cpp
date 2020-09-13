#include "metric/fpa/InternalLogicalFile.h"
#include <vector>

#define RET_LOW		(1)
#define RET_MEDIUM	(5)
#define DET_LOW		(19)
#define DET_MEDIUM 	(50)

InternalLogicalFile::InternalLogicalFile(int myDataElementTypes, int myRecordElementTypes, std::string myLabel) :
	FunctionPoint(myDataElementTypes, myRecordElementTypes, 0, myLabel){
}

int InternalLogicalFile::GetWeight(){
	static std::vector<int> Weights = {7, 10, 15};
	return (Weights[this -> GetComplexity()]);
}

std::string InternalLogicalFile::GetType(){
	return ("ILF");
}

FunctionPointComplexity InternalLogicalFile::GetComplexity(){
	if(this -> RecordElementTypes <= RET_LOW)
		if(this -> DataElementTypes <= DET_LOW)
			return (LOW);
		else if(this -> DataElementTypes <= DET_MEDIUM)
			return (LOW);
		else
			return (AVERAGE);
	else if(this -> RecordElementTypes <= RET_MEDIUM)
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
