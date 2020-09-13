#pragma once

#include "SimilarityMetrics.h"
#include "PatternGraph.h"

/**
 * This class implements the Jaccard similarity statistic.
 * Jaccard coefficient is a metric that can be used to quantify similarity between two sets.
 * We adapted this metric for parallel patterns.
 * It is calculated as the size of the intersection divided by size of the union.
 * J = size(intersection(A, B)) / size(union(A, B)).
 * The intersection criterion can be chosen upon statistic object creation.
 * The order of patterns in the pattern sequences is irrelevant for this set-based similarity measure.
 */
class JaccardSimilarityStatistic : public SimilarityMeasure {
	public:
		JaccardSimilarityStatistic(
				PatternGraphNode* myRootPattern,
				GraphSearchDirection mySearchDirection,
				SimilarityCriterion mySimilarityCriterion
		);
	protected:
		float ComputeSimilarity(PatternSequencePointer Left, PatternSequencePointer Right) override;
};
