#pragma once

#include "metric/fpa/FunctionPoint.h"

/**
 * Internal logical files are data functions that represent data structures
 * managed by the application.
 */
struct InternalLogicalFile : FunctionPoint{
	/**
	 * Creates a new instance of this object.
	 * @param myDataElementTypes The number of data element types.
	 * @param myRecordElementTypes The number of record element types.
	 * @param myLabel A descriptive label for this function point.
	 */
	InternalLogicalFile(int myDataElementTypes, int myRecordElementTypes, std::string myLabel);
	/**
	 * Identifies this function point as internal logical file.
	 * @return "ILF"
	 */
	std::string GetType() override;
	/**
	 * The weight is determined by the complexity of this function point.
	 * | Complexity | Weight |
	 * | ---------- | ------ |
	 * | Low        | 7      |
	 * | Medium     | 10     |
	 * | High       | 15     |
	 * @return The weight of this function point.
	 */
	int GetWeight() override;
	/**
	 * The complexity is determined by the number of data element types
	 * and record element types.
	 *
	 * | Complexity | 1-19 DET | 20 - 50 DET | 51+ DET |
	 * | ---------- | -------- | ----------- | ------- |
	 * |   1 RET    | Low      | Low         | Average |
	 * | 2-5 RET    | Low      | Average     | High    |
	 * |  6+ RET    | Average  | High        | High    |
	 * @return The weight of this function point.
	 */
	FunctionPointComplexity GetComplexity() override;
};
