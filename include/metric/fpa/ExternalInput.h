#pragma once

#include "metric/fpa/FunctionPoint.h"

/**
 * Information flows into the application. This happens during variable
 * modifications using the (conditional) assignment operator, where one of
 * the arguments on the right-hand side has been declared outside of the pattern.
 */
struct ExternalInput : FunctionPoint{
	ExternalInput(int DataElementType, int FileTypeReferenced, std::string Label);

	std::string GetType() override;
	int GetWeight() override;
	FunctionPointComplexity GetComplexity() override;
};
