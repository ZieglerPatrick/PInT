#include "similarity/visitor/CompositionVisitor.h"
#include "SimilarityMetrics.h"

CompositionVisitor::CompositionVisitor(SimilarityCriterion mySimilarityCriterion) :
	Criterion(mySimilarityCriterion){
}

std::vector<PatternSequencePointer>& CompositionVisitor::CalculatePatternSequences(PatternGraphNode* RootNode){
	PatternSequences.clear();

	RootNode -> Accept(this);

	return (PatternSequences);
}

std::string CompositionVisitor::ToString(PatternCodeRegion* Node){
	switch(Criterion){
		case DesignSpace:
			return (Node -> GetPatternOccurrence() -> GetPattern() -> GetDesignSpaceStr());
			break;
		case Pattern:
			return (Node -> GetPatternOccurrence() -> GetPattern() -> GetPatternName());
			break;
		default:
			return (Node -> GetID());
	}
}
