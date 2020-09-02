#pragma once

//Forward declaration due to HPCParallelPattern::Accept(HPCParallelPatternVisitor);
class HPCParallelPattern;

/**
 * This visitor is used to access the pattern corresponding to
 * an pattern occurrence. This visitor might be accessed multiple
 * times per pattern graph, if the pattern occurs more than once.<br>
 * However, the pattern instance should remain unique for each of those
 * occurrences.
 */
class HPCParallelPatternVisitor{
	public:
		virtual ~HPCParallelPatternVisitor();
		virtual void VisitParallelPattern(HPCParallelPattern* ParallelPattern);
		virtual void TraverseParallelPattern(HPCParallelPattern* ParallelPattern);
		virtual void EndVisitParallelPattern(HPCParallelPattern* ParallelPattern);
		virtual void HandleParallelPattern(HPCParallelPattern* ParallelPattern);
};
