#pragma once

#include "SimilarityMetrics.h"
#include "PatternGraph.h"

class WeightedJaccardSimilarityStatistic : public SimilarityMeasure {
	public:
	WeightedJaccardSimilarityStatistic(
				PatternGraphNode* myRootPattern,
				GraphSearchDirection mySearchDirection,
				SimilarityCriterion mySimilarityCriterion
		);
	protected:
		float ComputeSimilarity(PatternSequencePointer Left, PatternSequencePointer Right) override;
};
