#pragma once

#include "SimilarityMetrics.h"
#include "PatternGraph.h"

class OverlapCoefficientStatistic : public SimilarityMeasure {
	public:
		OverlapCoefficientStatistic(
				PatternGraphNode* myRootPattern,
				GraphSearchDirection mySearchDirection,
				SimilarityCriterion mySimilarityCriterion
		);
	protected:
		float ComputeSimilarity(PatternSequencePointer Left, PatternSequencePointer Right) override;
	private:
		size_t CountUniqueElements(PatternSequencePointer Sequence);
};
