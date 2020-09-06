#pragma once

#include "metric/fpa/FunctionPoint.h"

/**
 * Whenever information is forwarded to the user. For example using "printf".
 * They are currently ignored.
 */
struct ExternalInquiry : FunctionPoint{
	ExternalInquiry(int DataElementType, int FileTypeReferenced, std::string Label);

	std::string GetType() override;
	int GetWeight() override;
	FunctionPointComplexity GetComplexity() override;
};
