#include "similarity/visitor/TopDownCompositionVisitor.h"
#include "SimilarityMetrics.h"
#include "Helpers.h"

TopDownCompositionVisitor::TopDownCompositionVisitor(SimilarityCriterion mySimilarityCriterion) :
	CompositionVisitor(mySimilarityCriterion){
}


void TopDownCompositionVisitor::VisitPatternCodeRegion(PatternCodeRegion* Node){
	Preconditions::CheckArgument(!PatternSequences.empty(), std::out_of_range("Missing pattern sequence for "+Node ->GetID()));

	SequenceCodeRegions.push_back(Node);
	PatternSequences.back() -> PatternLabels.emplace(ToString(Node));
}

void TopDownCompositionVisitor::HandlePatternCodeRegion(PatternCodeRegion* Node){
	//The first code region defines a pattern sequence. All children are members
	if(SequenceCodeRegions.empty()){
		PatternSequencePointer myPatternSequence(new PatternSequence());
		PatternSequences.push_back(myPatternSequence);
	}

	//Call super method
	CompositionVisitor::HandlePatternCodeRegion(Node);
}

void TopDownCompositionVisitor::EndVisitPatternCodeRegion(PatternCodeRegion* Node){
	Preconditions::CheckArgument(!SequenceCodeRegions.empty(), std::out_of_range("Missing Pattern_Begin for "+Node -> GetID()));
	SequenceCodeRegions.pop_back();
}
