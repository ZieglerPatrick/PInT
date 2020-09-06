#pragma once

//Forward declaration due to HPCParallelPattern::Accept(HPCParallelPatternVisitor);
class HPCParallelPattern;

/**
 * This visitor is used to access the pattern corresponding to a pattern occurrence.
 * A pattern may appear multiple times, once for each patter occurrence. In that
 * case, only the first occurrence is taken into consideration.
 */
class HPCParallelPatternVisitor{
	public:
		virtual ~HPCParallelPatternVisitor();
		virtual void VisitParallelPattern(HPCParallelPattern* ParallelPattern);
		virtual void TraverseParallelPattern(HPCParallelPattern* ParallelPattern);
		virtual void EndVisitParallelPattern(HPCParallelPattern* ParallelPattern);
		virtual void HandleParallelPattern(HPCParallelPattern* ParallelPattern);
};
