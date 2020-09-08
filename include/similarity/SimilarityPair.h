#pragma once
#include "similarity/PatternSequence.h"

#define SimilarityPairPointer std::unique_ptr<SimilarityPair>

class SimilarityPair{
	public:
		PatternSequencePointer Left;
		PatternSequencePointer Right;
		float Similarity;

		/**
		 * Constructor for similarity pairs.
		 *
		 * @param myLeft First sequence.
		 * @param myRight Second sequence.
		 * @param mySimilarity Calculated similarity.
		 */
		SimilarityPair(PatternSequencePointer myLeft, PatternSequencePointer myRight, float mySimilarity);
};
