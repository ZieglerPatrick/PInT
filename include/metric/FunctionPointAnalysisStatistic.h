#pragma once

#include "HPCPatternStatistics.h"
#include "HPCParallelPattern.h"
#include "metric/fpa/FunctionPoint.h"

/**
 * The function point analysis breaks the source code into
 * its building blocks and then maps then to their corresponding
 * function points. The analysis is applied to all patterns individually
 * in the graph.
 * There are 5 types of function points in total, further grouped
 * under data functions and transactional functions. Data functions
 * are represented by external interfaces files and internal logical files,
 * both describing a data structure, with their location being the deciding factor.<br>
 * In this statistic, both refer to variables, with internal logicals files
 * representing all variables that have been declared inside the corresponding pattern.
 * Analogously, external interface files are variables declared outside the pattern.<br>
 * Transactional functions consist of external inputs, external outputs and external inquiries
 * and describe the flow of information between an instrumented code region and the remaining
 * source program. This happens via the usage of operators and function calls. Such an expression
 * is an external input, if it references a variable that has been declared outside the pattern.
 * In case of a function call or a variable modification, it is an external output, if either
 * have been declared outside the pattern. External inquiries occur when representing data to
 * the end user, without altering the state of the program. However, in the context of the analysis,
 * those are omitted.
 */
class FunctionPointAnalysisStatistic : public HPCPatternStatistic{
	public:
		/**
		 * An empty destructor.
		 */
		virtual ~FunctionPointAnalysisStatistic();
		/**
		 * Performs the function point analysis on every parallel pattern.
		 */
		void Calculate();
		/**
		 * Prints the unadjusted function point count, the value adjustment factor
		 * and the final function point count for each parallel pattern.
		 */
		void Print();
		/**
         * Writes the calculated values in a CSV file.
         * The output consists of four columns, the first containing the pattern name,
         * followed by the unadjusted function points, value adjustmment factor and
         *  function point count.
		 * @param FileName The name of the CSV file.
		 */
		void CSVExport(std::string FileName);

	private:
		/**
		 * A container class storing the data required for performing the function point analysis.
		 */
		struct FunctionPointCounter{
			/**
			 * The unadjusted function points are calculating the sum over the weight
			 * of all function points in the corresponding pattern.
			 */
			int UnadjustedFunctionPoints;
			/**
			 * The value adjustment factor is a constant scalar and depends on characteristics
			 * of the program.
			 */
			double ValueAdjustmentFactor;
			/**
			 * The function point count is the product of the unadjusted function points
			 * and the value adjustment factor.
			 */
			double FunctionPointCount;
		};

		/**
		 * Performs the function point analysis on the corresponding pattern.
		 * @param Pattern The pattern associated with the function point analysis.
		 * @return A structure containing the results of the analysis.
		 */
		FunctionPointCounter Calculate(HPCParallelPattern* Pattern);
		/**
		 * The unadjusted function points count is the sum over the weights of
		 * all patterns in the corresponding parallel pattern.
		 * @param Pattern The pattern associated with the unadjusted function point count.
		 * @return The unadjusted function point count of the pattern.
		 */
		int CalculateUnadjustedFunctionPoints(HPCParallelPattern* Pattern);
		/**
		 * The value adjustment factor is a constant derived from the characteristics of the program
		 * which is loosely based on parallel programs.
		 * In the future, one may derive individual factors for each pattern.
		 * @return The value adjustment factor.
		 */
		double CalculateValueAdjustmentFactor();
		/**
		 * The function point count is the product of the unadjusted function point count
		 * and the value adjustment factor.
		 * @param Pattern The pattern associated with the function point count.
		 * @return The function point count of the pattern.
		 */
		double CalculateFunctionPointCount(HPCParallelPattern* Pattern);
		/**
		 * Contains the results of the function point analysis for all patterns in the graph.
		 */
		std::map<HPCParallelPattern*, FunctionPointCounter> FunctionPointMap;
};
