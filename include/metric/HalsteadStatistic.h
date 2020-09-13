#pragma once

#include "HPCPatternStatistics.h"
#include "HPCParallelPattern.h"

/**
 * The Halstead metric gives an estimate for the complexity of a program.
 * The code is broken down into its building blocks where each piece is
 * then categorized as operator or operand.
 * Variables and constants are considered to be operands, while operators
 * include common symbols, like addition or multiplication, but also
 * language specific keywords.
 */
class HalsteadStatistic : public HPCPatternStatistic{
	public:
		/**
		 * An empty destructor.
		 */
		virtual ~HalsteadStatistic();
		/**
		 * Calculates the halstead metrics for every parallel pattern in the pattern graph.
		 */
		void Calculate();
		/**
		 * Prints the number of directly and indirectly connected patterns, in addition
		 * to the values derived by the Halstead metric. Those consist of:
		 * - Program Vocabulary
		 * - Program Length
		 * - Estimated Program Length
		 * - Volume
		 * - Difficulty
		 * - Effort
		 * - Time Required to Program (in s)
		 * - Number of Delivered Bugs
		 */
		void Print();
		/**
         * Writes the calculated values in a CSV file.
         * The output consists of 13 columns, the first containing the pattern name, folowed by:
         * - #Operators
         * - #Distinct Operators
         * - #Operands
         * - #Distinct Operands
         * - Program Vocabulary
		 * - Program Length
		 * - Estimated Program Length
		 * - Volume
		 * - Difficulty
		 * - Effort
		 * - Time Required to Program (in s)
		 * - Number of Delivered Bugs
		 * @param FileName The name of the CSV file.
		 */
		void CSVExport(std::string FileName);

	private:
		/**
		 * A container class storing the Halstead metrics.
		 */
		struct HalsteadCounter{
			/**
			 * Let \f$ \eta_1 \f$ be the number of distinct operators.<br>
			 * Let \f$ \eta_2 \f$ be the number of distinct operands.<br>
			 * Then the vocabulary is defined as \f$ \_eta = \eta_1 + \eta_2\f$.
			 */
			int Vocabulary;
			/**
			 * Let \f$ N_1 \f$ be the total number of operators.<br>
			 * Let \f$ N_2 \f$ be the total number of operands.<br>
			 * Then the program length is defined as \$f N = N_1 + N_2 \$f.
			 */
			int ProgramLength;
			/**
			 * Let \f$ \eta_1 \f$ be the number of distinct operators.<br>
			 * Let \f$ \eta_2 \f$ be the number of distinct operands.<br>
			 * Then the estimated program length is defined as
			 * \f$ \^{N} = \eta_1 \cdot log_2(\eta_1) + \eta_2 \cdot log_2(\eta_2)\f$.
			 */
			double EstimatedProgramLength;
			/**
			 * Let N be the program length.<br>
			 * Let \f$ \eta \f$ be the vocabulary.<br>
			 * Then the volume is defined as \f$ V = N \cdot log_2(\eta) \f$.
			 */
			double Volume;
			/**
			 * Let \f$ \eta_1 \f$ be the number of distinct operators.<br>
			 * Let \f$ \eta_2 \f$ be the number of distinct operands.<br>
			 * Let \f$ N_2 \f$ be the total number of operands.<br>
			 * Then the difficulty is defined as
			 * \f$ D = \frac{\eta_1}{2} \cdot \frac{N_2}{\eta_2} \f$.
			 */
			double Difficulty;
			/**
			 * Let D be the effort.<br>
			 * Let V be the volume.<br>
			 * Then the effort is defined as \f$ D \cdot V \f$.
			 */
			double Effort;
			/**
			 * Let E be the effort.<br>
			 * Then the required time is defined as \f$T = E / 18\f$.
			 */
			double TimeRequiredToProgram;
			/**
			 * Let E be the effort.<br>
			 * Then the number of delivered bugs is defined as
			 * \f$ B = \frac{E^{\frac{2}{3}}}{3000}\f$.
			 */
			double NumberOfDeliveredBugs;
		};

		/**
		 * Calculates the Halstead metrics for the corresponding pattern.
		 * @param Pattern The pattern associated with the Haldstead matrics.
		 */
		void Calculate(HPCParallelPattern* Pattern);
		/**
		 * Let \f$ \eta_1 \f$ be the number of distinct operators.<br>
		 * Let \f$ \eta_2 \f$ be the number of distinct operands.<br>
		 * Then the vocabulary is defined as \f$ \_eta = \eta_1 + \eta_2\f$.
		 * @param Pattern The pattern associated with the vocabulary.
		 * @return The vocabulary of the pattern.
		 */
		int CalculateProgramVocabulary(HPCParallelPattern* Pattern);
		/**
		 * Let \f$ N_1 \f$ be the total number of operators.<br>
		 * Let \f$ N_2 \f$ be the total number of operands.<br>
		 * Then the program length is defined as \$f N = N_1 + N_2 \$f.
		 * @param Pattern The pattern associated with the program length.
		 * @return The program length of the pattern.
		 */
		int CalculateProgramLength(HPCParallelPattern* Pattern);
		/**
		 * Let \f$ \eta_1 \f$ be the number of distinct operators.<br>
		 * Let \f$ \eta_2 \f$ be the number of distinct operands.<br>
		 * Then the estimated program length is defined as
		 * \f$ \^{N} = \eta_1 \cdot log_2(\eta_1) + \eta_2 \cdot log_2(\eta_2)\f$.
		 * @param Pattern The pattern associated with the estimated program length.
		 * @return The estimated program length of the pattern.
		 */
		double CalculateEstimatedProgramLength(HPCParallelPattern* Pattern);
		/**
		 * Let N be the program length.<br>
		 * Let \f$ \eta \f$ be the vocabulary.<br>
		 * Then the volume is defined as \f$ V = N \cdot log_2(\eta) \f$.
		 * @param Pattern The pattern associated with the volume.
		 * @return The volume of the pattern.
		 */
		double CalculateVolume(HPCParallelPattern* Pattern);
		/**
		 * Let \f$ \eta_1 \f$ be the number of distinct operators.<br>
		 * Let \f$ \eta_2 \f$ be the number of distinct operands.<br>
		 * Let \f$ N_2 \f$ be the total number of operands.<br>
		 * Then the difficulty is defined as
		 * \f$ D = \frac{\eta_1}{2} \cdot \frac{N_2}{\eta_2} \f$.
		 * @param Pattern The pattern associated with the difficulty.
		 * @return The difficulty of the pattern.
		 */
		double CalculateDifficulty(HPCParallelPattern* Pattern);
		/**
		 * Let E be the effort.<br>
		 * Then the required time is defined as \f$T = E / 18\f$.
		 * @param Pattern The pattern associated with the effort.
		 * @return The effort of the pattern.
		 */
		double CalculateEffort(HPCParallelPattern* Pattern);
		/**
		 * Let E be the effort.<br>
		 * Then the required time is defined as \f$T = E / 18\f$.
		 * @param Pattern The pattern associated with the time required to implement.
		 * @return The implementation time of the pattern in seconds.
		 */
		double CalculateTimeRequiredToProgram(HPCParallelPattern* Pattern);
		/**
		 * Let E be the effort.<br>
		 * Then the number of delivered bugs is defined as
		 * \f$ B = \frac{E^{\frac{2}{3}}}{3000}\f$.
		 * @param Pattern The pattern associated with the number of delivered bugs.
		 * @return The estimated amount of bugs in the pattern.
		 */
		double CalculateNumberOfDeliveredBugs(HPCParallelPattern* Pattern);
		/**
		 * Contains the Halstead metrics for all patterns.
		 */
		std::map<HPCParallelPattern*, HalsteadCounter> HalsteadMap;
};
