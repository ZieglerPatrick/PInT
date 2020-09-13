#pragma once

#include "cohesion/ConnectedPatternCounter.h"
#include "HPCPatternStatistics.h"
#include "HPCParallelPattern.h"

/**
 * The cohesion describes the connectivity between parallel patterns.
 * Given the pattern graph, two patterns are connected, if there is a
 * path from one pattern to the other. Note that we assume the path
 * to be directed.<br>
 * If the patterns are connected by an edge, we consider them to be
 * directly connected, otherwise they are indirectly connected.
 * The cohesion is then expressed using Tight Class Cohesion and
 * Loose Class cohesion.
 *
 */
class CohesionStatistic : public HPCPatternStatistic{
	public:
		/**
		 * An empty destructor.
		 */
		virtual ~CohesionStatistic();
		/**
		 * Calculates the cohesion for every parallel pattern in the pattern graph.
		 */
		void Calculate() override;
		/**
		 * Prints the number of directly and indirectly connected patterns, in addition
		 * to the TCC and LCC for each parallel pattern.
		 */
		void Print() override;
		/**
         * Writes the calculated values in a CSV file.
         * The output consists of three columns, the first containing the pattern name,
         * followed by the TCC and LCC.
		 * @param FileName The name of the CSV file.
		 */
		void CSVExport(std::string FileName) override;

	private:
		/**
		 * A container class storing the data required for computing the cohesion.
		 */
		struct CohesionCounter{
			/**
			 * Contains all directly connected patterns.
			 */
			std::set<HPCParallelPattern*> DirectlyConnectedPatterns;
			/**
			 * Contains all indirectly connected patterns.
			 */
			std::set<HPCParallelPattern*> IndirectlyConnectedPatterns;
			/**
			 * Contains the tight class cohesion.
			 * It is computed by dividing the number of directly connected
			 * patterns by the total number of patterns.
			 */
			double TCC;
			/**
			 * Contains the loose class cohesion.
			 * It is computed by dividing the total number of connected
			 * patterns by the total number of patterns.
			 */
			double LCC;
		};

		/**
		 * Derives the directly and indirectly connected patterns.
		 * The detected patterns are stored in the return structure.
		 * @param Pattern The pattern associated with the connectivity.
		 * @return A structure containing the cohesion of the pattern.
		 */
		CohesionCounter CalculateConnectivity(HPCParallelPattern* Pattern);
		/**
		 * The tight class cohesion is calculated by dividing the number
		 * of directly connected patterns by the total number of patterns.
		 * The result is stored in the provided argument.
		 * @param CohesionCounter The counter associated with a parallel pattern.
		 */
		void CalculateTCC(CohesionCounter& CohesionCounter);
		/**
		 * The loose class cohesion is calculated by dividing the total number
		 * of connected patterns by the total number of patterns.
		 * The result is stored in the provided argument.
		 * @param CohesionCounter The counter associated with a parallel pattern.
		 */
		void CalculateLCC(CohesionCounter& CohesionCounter);
		/**
		 * Contains the cohesion for all patterns in the graph.
		 */
		std::map<HPCParallelPattern*, CohesionCounter> CohesionMap;
};
