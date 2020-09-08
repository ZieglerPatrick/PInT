#include "similarity/SimilarityPair.h"

SimilarityPair::SimilarityPair(PatternSequencePointer myLeft, PatternSequencePointer myRight, float mySimilarity):
	Left(myLeft),
	Right(myRight),
	Similarity(mySimilarity){
}
