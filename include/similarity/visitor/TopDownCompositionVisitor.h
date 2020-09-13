#pragma once

#include "similarity/visitor/CompositionVisitor.h"

class TopDownCompositionVisitor : public CompositionVisitor{
	public:
		explicit TopDownCompositionVisitor(SimilarityCriterion mySimilarityCriterion);
		void VisitPatternCodeRegion(PatternCodeRegion* Node) override;
		void EndVisitPatternCodeRegion(PatternCodeRegion* Node) override;
		void HandlePatternCodeRegion(PatternCodeRegion* Node) override;
};
