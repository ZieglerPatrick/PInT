#pragma once

#include "similarity/visitor/CompositionVisitor.h"

class BottomUpCompositionVisitor : public CompositionVisitor{
	public:
		explicit BottomUpCompositionVisitor(SimilarityCriterion mySimilarityCriterion);
		void VisitPatternCodeRegion(PatternCodeRegion* Node) override;
		void EndVisitPatternCodeRegion(PatternCodeRegion* Node) override;
	private:
		bool PatternCodeRegionIsLeaf;
};
