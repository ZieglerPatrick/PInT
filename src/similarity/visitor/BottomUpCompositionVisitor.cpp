#include "similarity/visitor/BottomUpCompositionVisitor.h"

BottomUpCompositionVisitor::BottomUpCompositionVisitor(SimilarityCriterion mySimilarityCriterion):
	CompositionVisitor(mySimilarityCriterion),
	PatternCodeRegionIsLeaf(false){
}

void BottomUpCompositionVisitor::VisitPatternCodeRegion(PatternCodeRegion* Node){
	//When traversing top-down, every new code region may be a leaf
	PatternCodeRegionIsLeaf = true;
	SequenceCodeRegions.push_back(Node);
}

void BottomUpCompositionVisitor::EndVisitPatternCodeRegion(PatternCodeRegion* Node){
	Preconditions::CheckArgument(!SequenceCodeRegions.empty(), std::out_of_range("Missing Pattern_Begin for "+Node -> GetID()));

	//The first endVisit indicates that the code region is indeed a leaf
	if(PatternCodeRegionIsLeaf){
		PatternCodeRegionIsLeaf = false;

		PatternSequencePointer myPatternSequence(new PatternSequence());

		//The sequence consists of all patterns on the path from the root to the leaf
		for(PatternCodeRegion* SequenceNode : SequenceCodeRegions)
			myPatternSequence -> PatternLabels.emplace(ToString(SequenceNode));

		PatternSequences.push_back(myPatternSequence);
	}

	SequenceCodeRegions.pop_back();
}
