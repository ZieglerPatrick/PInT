#include "similarity/WeightedJaccardSimilarityStatistic.h"

WeightedJaccardSimilarityStatistic::WeightedJaccardSimilarityStatistic(
	PatternGraphNode* myRootPattern,
	GraphSearchDirection mySearchDirection,
	SimilarityCriterion mySimilarityCriterion
)
	: SimilarityMeasure(myRootPattern, mySearchDirection, mySimilarityCriterion, "Weighted Jaccard Similarity"){
}

float WeightedJaccardSimilarityStatistic::ComputeSimilarity(PatternSequencePointer Left, PatternSequencePointer Right){
	size_t numerator = 0;
	size_t denominator = 0;
	std::set<std::string> CombinedPatternLabels;

	CombinedPatternLabels.insert(Left -> PatternLabels.begin(), Left -> PatternLabels.end());
	CombinedPatternLabels.insert(Right -> PatternLabels.begin(), Right -> PatternLabels.end());

	for(std::string PatternLabel : CombinedPatternLabels){
		numerator += std::min(Left -> PatternLabels.count(PatternLabel), Right -> PatternLabels.count(PatternLabel));
		denominator += std::max(Left -> PatternLabels.count(PatternLabel), Right -> PatternLabels.count(PatternLabel));
	}
	return (static_cast<float>(numerator) / static_cast<float>(denominator));
}
