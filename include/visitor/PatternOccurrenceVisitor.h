#pragma once

#include "visitor/HPCParallelPatternVisitor.h"

//Forward declaration due to PatternOccurrence::Accept(PatternOccurrenceVisitor);
class PatternOccurrence;

/**
 * This visitor is used to access the pattern occurrence corresponding to a pattern code region.
 * A pattern may occur multiple times, once for each patter code region. In that
 * case, only the first occurrence is taken into consideration.
 */
class PatternOccurrenceVisitor : public HPCParallelPatternVisitor{
	public:
		virtual void VisitPatternOccurrence(PatternOccurrence* PatternOccurrence);
		virtual void TraversePatternOccurrence(PatternOccurrence* PatternOccurrence);
		virtual void EndVisitPatternOccurrence(PatternOccurrence* PatternOccurrence);
		virtual void HandlePatternOccurrence(PatternOccurrence* PatternOccurrence);
};
