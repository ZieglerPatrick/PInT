#pragma once

#include "visitor/HPCParallelPatternVisitor.h"

//Forward declaration due to PatternOccurrence::Accept(PatternOccurrenceVisitor);
class PatternOccurrence;

/**
 * This visitor is used to access all pattern occurrences 
 * in the underlying pattern graph.
 */
class PatternOccurrenceVisitor : public HPCParallelPatternVisitor{
	public:
		virtual ~PatternOccurrenceVisitor();
		virtual void VisitPatternOccurrence(PatternOccurrence* PatternOccurrence);
		virtual void TraversePatternOccurrence(PatternOccurrence* PatternOccurrence);
		virtual void EndVisitPatternOccurrence(PatternOccurrence* PatternOccurrence);
		virtual void HandlePatternOccurrence(PatternOccurrence* PatternOccurrence);
};
