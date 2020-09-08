#include "SimilarityMetrics.h"
#include "similarity/SimilarityPair.h"
#include "similarity/visitor/BottomUpCompositionVisitor.h"
#include "similarity/visitor/TopDownCompositionVisitor.h"

SimilarityMeasure::SimilarityMeasure
(
	PatternGraphNode* myRootNode,
	GraphSearchDirection mySearchDirection,
	SimilarityCriterion mySimilarityCriterion,
	std::string mySimilarityLabel
)
:
	SimilarityLabel(mySimilarityLabel)
{
	switch(mySearchDirection){
		case DIR_Children:{
			TopDownCompositionVisitor Visitor(mySimilarityCriterion);
			this -> PatternSequences = Visitor.CalculatePatternSequences(myRootNode);
 			break;
		}
		case DIR_Parents:{
			BottomUpCompositionVisitor Visitor(mySimilarityCriterion);
			this -> PatternSequences = Visitor.CalculatePatternSequences(myRootNode);
 			break;
		}
		default:{
			break;
		}
	}
}

SimilarityMeasure::~SimilarityMeasure(){}

/**
 * @brief Calculates the similarity statistic for all sequences extracted.
 */
void SimilarityMeasure::Calculate(){
	for(size_t Column = 0 ; Column < PatternSequences.size() ; ++Column){
		for(size_t Row = 0 ; Row < Column ; ++Row){
			PatternSequencePointer Left = PatternSequences[Row];
			PatternSequencePointer Right = PatternSequences[Column];
			float Similarity = ComputeSimilarity(Left, Right);

			SimilarityPair* mySimilarityPair = new SimilarityPair(Left, Right, Similarity);
			Similarities.emplace_back(SimilarityPairPointer(mySimilarityPair));
		}
	}
}

/**
 * @brief Prints similarities for all pairs of pattern sequences.
 */
void SimilarityMeasure::Print(){
	//Print the name of the similarity measure
	std::cout << SimilarityLabel << std::endl;

	//Print the labels for the column/rows
	for(size_t Index = 0 ; Index < PatternSequences.size() ; ++Index){
		std::cout << "["<< Index << "] -> {";
		for(std::string Label : PatternSequences[Index] -> PatternLabels){
			std::cout << Label << " ";
		}
		std::cout << "}" << std::endl;
	}

	//Print the column of the  matrix frame
	printf("Pattern\t");
	for(size_t Column = 0 ; Column < PatternSequences.size() ; ++Column)
		printf("| [%zu]\t", Column);
	printf("\n");

	for(size_t Column = 0, Index = 0 ; Column < PatternSequences.size() ; ++Column){
		//Print the row of the matrix frame
		printf("[%zu]\t", Column);

		for(size_t Row = 0 ; Row < Column ; ++Row, ++Index){
			SimilarityPairPointer& Similarity = Similarities[Index];
			printf("| %.2f\t", Similarity -> Similarity);
		}
		//Print diagonal element
		printf("| \\\n");
	}

	std::cout << std::endl;
}

/**
 * @brief Dummy function
 *
 * @param FileName File name of the output file.
 **/
void SimilarityMeasure::CSVExport(std::string FileName){
	//TODO
}
