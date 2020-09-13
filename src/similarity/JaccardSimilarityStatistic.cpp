#include "similarity/JaccardSimilarityStatistic.h"

JaccardSimilarityStatistic::JaccardSimilarityStatistic(
	PatternGraphNode* myRootPattern,
	GraphSearchDirection mySearchDirection,
	SimilarityCriterion mySimilarityCriterion
)
	: SimilarityMeasure(myRootPattern, mySearchDirection, mySimilarityCriterion, "Jaccard Similarity"){
}

float JaccardSimilarityStatistic::ComputeSimilarity(PatternSequencePointer Left, PatternSequencePointer Right){
	std::set<std::string> numerator;
	std::set<std::string> denominator;

	std::set_intersection(
		Left -> PatternLabels.begin(), Left -> PatternLabels.end(),
		Right -> PatternLabels.begin(), Right -> PatternLabels.end(),
		std::inserter(numerator, numerator.begin())
	);

	std::set_union(
		Left -> PatternLabels.begin(), Left -> PatternLabels.end(),
		Right -> PatternLabels.begin(), Right -> PatternLabels.end(),
		std::inserter(denominator, denominator.begin())
	);

	return (static_cast<float>(numerator.size()) / static_cast<float>(denominator.size()));
}
