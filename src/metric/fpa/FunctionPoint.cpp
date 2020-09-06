#include "metric/fpa/FunctionPoint.h"

FunctionPoint::FunctionPoint
(
	int DataElementType,
	int RecordElementType,
	int FileTypeReferenced,
	std::string Label
) :
	det(DataElementType),
	ret(RecordElementType),
	ftr(FileTypeReferenced),
	label(Label){
}

FunctionPoint::~FunctionPoint(){}
