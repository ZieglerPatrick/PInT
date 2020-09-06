#pragma once

#include "metric/fpa/FunctionPointComplexity.h"
#include <string>

#define FunctionPointPointer FunctionPoint*

/**
 * The common superclass of all function points.
 */
struct FunctionPoint{
	int det;
	int ret;
	int ftr;
	std::string label;

	FunctionPoint(int DataElementType, int RecordElementType, int FileTypeReferenced, std::string Label);
	virtual ~FunctionPoint();

	virtual int GetWeight() = 0;
	virtual FunctionPointComplexity GetComplexity() = 0;
	virtual std::string GetType() = 0;
};
