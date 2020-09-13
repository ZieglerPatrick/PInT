#pragma once

#include "metric/fpa/FunctionPoint.h"

/**
 * External inputs are transactional functions and represent a flow
 * of information from the code region into the application.
 */
struct ExternalOutput : FunctionPoint{
	/**
	 * Creates a new instance of this object.
	 * @param myDataElementTypes The number of data element types.
	 * @param myFileTypeReferenced The number of file type referenced.
	 * @param myLabel A descriptive label for this function point.
	 */
	ExternalOutput(int myDataElementTypes, int myFileTypeReferenced, std::string myLabel);
	/**
	 * Identifies this function point as external output.
	 * @return "EO"
	 */
	std::string GetType() override;
	/**
	 * The weight is determined by the complexity of this function point.
	 *
	 * | Complexity | Weight |
	 * | ---------- | ------ |
	 * | Low        | 4      |
	 * | Medium     | 5      |
	 * | High       | 7      |
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
