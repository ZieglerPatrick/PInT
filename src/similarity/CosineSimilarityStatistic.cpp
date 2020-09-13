#include "similarity/CosineSimilarityStatistic.h"

CosineSimilarityStatistic::CosineSimilarityStatistic(
	PatternGraphNode* myRootPattern,
	GraphSearchDirection mySearchDirection,
	SimilarityCriterion mySimilarityCriterion
)
	: SimilarityMeasure(myRootPattern, mySearchDirection, mySimilarityCriterion, "Cosine Similarity"){
}

float CosineSimilarityStatistic::ComputeSimilarity(PatternSequencePointer Left, PatternSequencePointer Right){
	size_t numerator = 0;
	float denominator = 0;
	std::set<std::string> CombinedPatternLabels;

	CombinedPatternLabels.insert(Left -> PatternLabels.begin(), Left -> PatternLabels.end());
	CombinedPatternLabels.insert(Right -> PatternLabels.begin(), Right -> PatternLabels.end());

	for(std::string PatternLabel : CombinedPatternLabels)
		numerator += Left -> PatternLabels.count(PatternLabel) * Right -> PatternLabels.count(PatternLabel);

	denominator = Magnitude(Left) * Magnitude(Right);

	return (static_cast<float>(numerator) / static_cast<float>(denominator));
}

float CosineSimilarityStatistic::Magnitude(PatternSequencePointer Sequence){
	float magnitude = 0;

	for(auto Label = Sequence -> PatternLabels.begin() ; Label != Sequence -> PatternLabels.end() ; Label = Sequence -> PatternLabels.upper_bound(*Label)){
		magnitude += Sequence -> PatternLabels.count(*Label) * Sequence -> PatternLabels.count(*Label);
	}

	return (std::sqrt(magnitude));
}
