#pragma once

#include "cohesion/ConnectedPatternCounter.h"
#include "HPCPatternStatistics.h"
#include "HPCParallelPattern.h"

class CohesionStatistic : public HPCPatternStatistic{
	public:
		virtual ~CohesionStatistic();
		void Calculate();
		void Print();
		void CSVExport(std::string FileName);

	private:
		class CohesionCounter{
			public:
				std::set<HPCParallelPattern*> DirectlyConnectedPatterns;
				std::set<HPCParallelPattern*> IndirectlyConnectedPatterns;
				double TCC;
				double LCC;
		};

		CohesionCounter CalculateConnectivity(HPCParallelPattern* Pattern);
		void CalculateTCC(CohesionCounter& CohesionCounter);
		void CalculateLCC(CohesionCounter& CohesionCounter);

		std::map<HPCParallelPattern*, CohesionCounter> CohesionMap;
};
