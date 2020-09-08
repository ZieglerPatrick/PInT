#pragma once

#include "PatternGraph.h"
#include "SimilarityMetrics.h"
#include "similarity/PatternSequence.h"

#include <vector>

class CompositionVisitor : public PatternGraphNodeVisitor{
	public:
		explicit CompositionVisitor(SimilarityCriterion mySimilarityCriterion);
		std::vector<PatternSequencePointer>& CalculatePatternSequences(PatternGraphNode* RootNode);
		std::string ToString(PatternCodeRegion* Node);
	protected:
		//Contains the code regions within a pattern sequence
		std::vector<PatternCodeRegion*> SequenceCodeRegions;
		//Contains all pattern sequences
		std::vector<PatternSequencePointer> PatternSequences;
	private:
		SimilarityCriterion Criterion;
};
