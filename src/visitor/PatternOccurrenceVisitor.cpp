#include "visitor/PatternOccurrenceVisitor.h"
#include "HPCParallelPattern.h"

void PatternOccurrenceVisitor::VisitPatternOccurrence(PatternOccurrence* PatternOccurrence){
	static_cast<void>(PatternOccurrence); //Avoid unused parameter warning
}

void PatternOccurrenceVisitor::TraversePatternOccurrence(PatternOccurrence* PatternOccurrence){
	static_cast<void>(PatternOccurrence); //Avoid unused parameter warning
}
void PatternOccurrenceVisitor::EndVisitPatternOccurrence(PatternOccurrence* PatternOccurrence){
	static_cast<void>(PatternOccurrence); //Avoid unused parameter warning
}

void PatternOccurrenceVisitor::HandlePatternOccurrence(PatternOccurrence* PatternOccurrence){
	//Treat this as an inheritance visitor
	//i.e. a Pattern Occurrence is also a Parallel Pattern
	VisitParallelPattern(PatternOccurrence -> GetPattern());
	VisitPatternOccurrence(PatternOccurrence);
	TraversePatternOccurrence(PatternOccurrence);
	EndVisitPatternOccurrence(PatternOccurrence);
	EndVisitParallelPattern(PatternOccurrence -> GetPattern());
}
