#pragma once
#include "metric/fpa/FunctionPoint.h"

/**
 * A comparator for function points. Two function points are considered to be equal,
 * if they share the same type and label.
 */
struct FunctionPointComparator{
	bool operator()(FunctionPointPointer lhs, FunctionPointPointer rhs){
		return ((lhs -> GetType() + lhs -> Label) < (rhs -> GetType() + rhs -> Label));
	}
};
