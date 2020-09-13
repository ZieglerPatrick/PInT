#pragma once

#include "SimilarityMetrics.h"
#include "PatternGraph.h"

class CosineSimilarityStatistic : public SimilarityMeasure {
	public:
		CosineSimilarityStatistic(
				PatternGraphNode* myRootPattern,
				GraphSearchDirection mySearchDirection,
				SimilarityCriterion mySimilarityCriterion
		);
	protected:
		float ComputeSimilarity(PatternSequencePointer Left, PatternSequencePointer Right) override;
	private:
		float Magnitude(PatternSequencePointer Sequence);
};
