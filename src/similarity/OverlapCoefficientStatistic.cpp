#include "similarity/OverlapCoefficientStatistic.h"

OverlapCoefficientStatistic::OverlapCoefficientStatistic(
	PatternGraphNode* myRootPattern,
	GraphSearchDirection mySearchDirection,
	SimilarityCriterion mySimilarityCriterion
)
	: SimilarityMeasure(myRootPattern, mySearchDirection, mySimilarityCriterion, "Overlap Coefficient"){
}

float OverlapCoefficientStatistic::ComputeSimilarity(PatternSequencePointer Left, PatternSequencePointer Right){
	std::set<std::string> numerator;
	size_t denominator;

	std::set_intersection(
		Left -> PatternLabels.begin(),
		Left -> PatternLabels.end(),
		Right -> PatternLabels.begin(),
		Right -> PatternLabels.end(),
		std::inserter(numerator, numerator.begin())
	);

	denominator = std::min(CountUniqueElements(Left), CountUniqueElements(Right));

	return (static_cast<float>(numerator.size()) / static_cast<float>(denominator));
}

size_t OverlapCoefficientStatistic::CountUniqueElements(PatternSequencePointer Sequence){
	std::set<std::string> UniqueElements;
	UniqueElements.insert(Sequence -> PatternLabels.begin(), Sequence -> PatternLabels.end());
	return (UniqueElements.size());
}
