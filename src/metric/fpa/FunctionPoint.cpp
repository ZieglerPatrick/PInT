#include "metric/fpa/FunctionPoint.h"

FunctionPoint::FunctionPoint
(
	int myDataElementTypes,
	int myRecordElementTypes,
	int myFileTypesReferenced,
	std::string myLabel
) :
	DataElementTypes(myDataElementTypes),
	RecordElementTypes(myRecordElementTypes),
	FileTypesReferenced(myFileTypesReferenced),
	Label(myLabel){
}

FunctionPoint::~FunctionPoint(){}
