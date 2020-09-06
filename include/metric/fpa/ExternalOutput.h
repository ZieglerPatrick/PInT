#pragma once

#include "metric/fpa/FunctionPoint.h"

/**
 * Information flows out of the application. Similar to {@link #EXTERNAL_INPUT},
 * this can happen when a variable outside of the pattern is modified using a
 * local value. Alternatively, it also occurs whenever a function is called and
 * an internal value is used as an argument.
 */
struct ExternalOutput : FunctionPoint{
	ExternalOutput(int DataElementType, int FileTypeReferenced, std::string Label);

	std::string GetType() override;
	int GetWeight() override;
	FunctionPointComplexity GetComplexity() override;
};
