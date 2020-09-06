#pragma once

#include "metric/fpa/FunctionPoint.h"

/**
 * Variables that have been declared outside the pattern.
 */
struct ExternalInterfaceFile : FunctionPoint{
	ExternalInterfaceFile(int DataElementType, int RecordElementType, std::string Label);

	std::string GetType() override;
	int GetWeight() override;
	FunctionPointComplexity GetComplexity() override;
};
