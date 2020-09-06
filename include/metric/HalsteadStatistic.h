#pragma once

#include "HPCPatternStatistics.h"
#include "HPCParallelPattern.h"

class HalsteadStatistic : public HPCPatternStatistic{
	public:
		virtual ~HalsteadStatistic();
		void Calculate();
		void Print();
		void CSVExport(std::string FileName);

	private:
		struct HalsteadCounter{
			int Vocabulary;
			int ProgramLength;
			double EstimatedProgramLength;
			double Volume;
			double Difficulty;
			double Effort;
			double TimeRequiredToProgram;
			double NumberOfDeliveredBugs;
		};

		void Calculate(HPCParallelPattern* Pattern);
		int CalculateProgramVocabulary(HPCParallelPattern* Pattern);
		int CalculateProgramLength(HPCParallelPattern* Pattern);
		double CalculateEstimatedProgramLength(HPCParallelPattern* Pattern);
		double CalculateVolume(HPCParallelPattern* Pattern);
		double CalculateDifficulty(HPCParallelPattern* Pattern);
		double CalculateEffort(HPCParallelPattern* Pattern);
		double CalculateTimeRequiredToProgram(HPCParallelPattern* Pattern);
		double CalculateNumberOfDeliveredBugs(HPCParallelPattern* Pattern);

		std::map<HPCParallelPattern*, HalsteadCounter> HalsteadMap;
};
