#include "metric/fpa/ExternalInterfaceFile.h"
#include <vector>

#define RET_LOW		(1)
#define RET_MEDIUM	(5)
#define DET_LOW		(19)
#define DET_MEDIUM 	(50)

ExternalInterfaceFile::ExternalInterfaceFile(int myDataElementTypes, int myRecordElementTypes, std::string myLabel) :
	FunctionPoint(myDataElementTypes, myRecordElementTypes, 0, myLabel){
}

int ExternalInterfaceFile::GetWeight(){
	static std::vector<int> Weights = {5, 7, 10};
	return (Weights[this -> GetComplexity()]);
}

std::string ExternalInterfaceFile::GetType(){
	return ("EIF");
}

FunctionPointComplexity ExternalInterfaceFile::GetComplexity(){
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
