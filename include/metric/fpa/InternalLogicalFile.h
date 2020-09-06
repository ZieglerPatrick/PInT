#pragma once

#include "metric/fpa/FunctionPoint.h"

/**
 * Variables that have been declared inside the pattern.
 */
struct InternalLogicalFile : FunctionPoint{
	InternalLogicalFile(int DataElementType, int RecordElementType, std::string Label);

	std::string GetType() override;
	int GetWeight() override;
	FunctionPointComplexity GetComplexity() override;
};
