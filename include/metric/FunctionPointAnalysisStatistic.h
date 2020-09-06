#pragma once

#include "HPCPatternStatistics.h"
#include "HPCParallelPattern.h"
#include "metric/fpa/FunctionPoint.h"

class FunctionPointAnalysisStatistic : public HPCPatternStatistic{
	public:
		virtual ~FunctionPointAnalysisStatistic();
		void Calculate();
		void Print();
		void CSVExport(std::string FileName);

	private:
		int CalculateUnadjustedFunctionPoints(HPCParallelPattern* Pattern);
		double CalculateValueAdjustmentFactor();
		double CalculateFunctionPointCount(HPCParallelPattern* Pattern);
};
