#pragma once

#include "metric/fpa/FunctionPoint.h"

/**
 * External inquiries are transactional functions and represent a flow
 * of information from application to the end user. Inquiries
 * do not affect the state of the application.
 */
struct ExternalInquiry : FunctionPoint{
	/**
	 * Creates a new instance of this object.
	 * @param myDataElementTypes The number of data element types.
	 * @param myFileTypeReferenced The number of file type referenced.
	 * @param myLabel A descriptive label for this function point.
	 */
	ExternalInquiry(int myDataElementTypes, int myFileTypeReferenced, std::string myLabel);

	/**
	 * Identifies this function point as external inquiry.
	 * @return "EQ"
	 */
	std::string GetType() override;
	/**
	 * The weight is determined by the complexity of this function point.
	 *
	 * | Complexity | Weight |
	 * | ---------- | ------ |
	 * | Low        | 3      |
	 * | Medium     | 4      |
	 * | High       | 6      |
	 * @return The weight of this function point.
	 */
	int GetWeight() override;
	/**
	 * The complexity is determined by the number of data element types
	 * and file type referenced.
	 *
	 * | Complexity | 1-5 DET | 6 - 19 DET | 20+ DET |
	 * | ---------- | ------- | ---------- | ------- |
	 * | 0-1 FTR    | Low     | Low        | Average |
	 * | 2-3 FTR    | Low     | Average    | High    |
	 * |  4+ FTR    | Average | High       | High    |
	 * @return The weight of this function point.
	 */
	FunctionPointComplexity GetComplexity() override;
};
