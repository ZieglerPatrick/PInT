#pragma once

#include "Helpers.h"
#include "PatternGraph.h"
#include "HPCPatternStatistics.h"
#include "similarity/PatternSequence.h"
#include "similarity/SimilarityPair.h"


/**
 * Similarity Criterion for intersection of pattern sets.
 * Intersection by design space means that both patterns have the same design space.
 * By Pattern means pattern identity.
 */
enum SimilarityCriterion
{
	DesignSpace, Pattern
};

/**
 * An abstract class for similarity measures which provides mutual methods and standard implementations.
 * All similarity measures should inherit from this class.
 * Most importantly, extraction of pattern sequences from the pattern tree for later similarity investigations is implemented.
 * Furthermore, miscellaneous implementations are provided here.
 * E.g. sorting by similarity etc.
 */
class SimilarityMeasure : public HPCPatternStatistic{
	public:
		SimilarityMeasure(
				PatternGraphNode* myRootNode,
				GraphSearchDirection mySearchDirection,
				SimilarityCriterion mySimilarityCriterion,
				std::string mySimilarityLabel
		);

		virtual ~SimilarityMeasure();

		void Calculate() override;
		void Print() override;
		void CSVExport(std::string FileName) override;

	protected:
		/**
 		 * A vector containing all pattern sequences found in the pattern graph.
 		 */
		std::vector<PatternSequencePointer> PatternSequences;
		/**
 		 * A vector containing the similarities of all sequence pairs.
 		 * The similarities are stored in a strictly lower triangular matrix.
 		 * The elements of the matrix are stored by row.
 		 */
		std::vector<SimilarityPairPointer> Similarities;
		/**
 		 * An id associated with the type of similarity metric. This name is only used in combination with the Print method.
 		 */
		std::string SimilarityLabel;
		/**
 		 * Calculates the similarity between the two pattern sequences.
 		 */
		virtual float ComputeSimilarity(PatternSequencePointer First, PatternSequencePointer Second) = 0;
};
