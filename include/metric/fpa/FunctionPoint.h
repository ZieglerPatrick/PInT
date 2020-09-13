#pragma once

#include "metric/fpa/FunctionPointComplexity.h"
#include <string>

#define FunctionPointPointer FunctionPoint*

/**
 * The common superclass of all function points.
 */
struct FunctionPoint{
	/**
	 * The number of data element types.
	 */
	int DataElementTypes;
	/**
	 * The number of record element types.
	 */
	int RecordElementTypes;
	/**
	 * The number of file type referenced.
	 */
	int FileTypesReferenced;
	/**
	 * The label for this function point.
	 */
	std::string Label;
	/**
	 * Creates a new instance of this object.
	 * @param myDataElementTypes The number of data element types.
	 * @param myRecordElementTypes The number of record element types.
	 * @param myFileTypesReferenced The number of file type referenced.
	 * @param myLabel A descriptive label for this function point.
	 */
	FunctionPoint(int myDataElementTypes, int myRecordElementTypes, int myFileTypesReferenced, std::string myLabel);
	/**
	 * Destructor for freeing potentially allocated memory.
	 */
	virtual ~FunctionPoint();

	/**
	 * The weight is determined by the complexity of this function point.
	 * @return The weight of this function point.
	 */
	virtual int GetWeight() = 0;
	/**
	 * The complexity is determined by the number of data element types,
	 * record element types and file type referenced. Function points
	 * may omit some of them.
	 *
	 * @return The weight of this function point.
	 */
	virtual FunctionPointComplexity GetComplexity() = 0;
	/**
	 * Each function point has a short identifier representing the type.
	 * return The type of function point.
	 */
	virtual std::string GetType() = 0;
};
