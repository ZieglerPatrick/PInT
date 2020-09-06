#include "metric/FunctionPointAnalysisStatistic.h"
#include "metric/fpa/PrintPretty.h"

#include <iostream>
#include <fstream>

#define NUMBER_OF_CSV_ENTRIES (4)
#define VALUE_ADJUSTMENT_FACTOR_OFFSET (0.65)
#define VALUE_ADJUSTMENT_FACTOR_PERCENT (0.01)

FunctionPointAnalysisStatistic::~FunctionPointAnalysisStatistic(){}

void FunctionPointAnalysisStatistic::Calculate(){
	//Calculated for each pattern individually
}

void FunctionPointAnalysisStatistic::Print(){
	for(HPCParallelPattern* Pattern : PatternGraph::GetInstance() -> GetAllPatterns()){
		std::cout << "Pattern " << Pattern -> GetPatternName() << " has:" << std::endl;

		#ifdef DEBUG
		for(auto& FunctionPoint : Pattern -> GetFunctionPoints()){
			std::cout << "\t"
					  << FunctionPoint -> GetType()
					  << "{"
					  << std::endl;

			std::cout << "\t\tLabel: "
					  << FunctionPoint -> label
					  << std::endl;

			printf("\t\t| %5s | %5s | %5s | %10s |\n",
					"#DET",
					"#RET",
					"#FTR",
					"Complexity"
			);

			printf("\t\t| %5d | %5d | %5d | %10s |\n",
					FunctionPoint -> det,
					FunctionPoint -> ret,
					FunctionPoint -> ftr,
					FunctionPointAnalysis::PrintPretty(FunctionPoint -> GetComplexity()).c_str()
			);

			std::cout << "\t}"
					  << std::endl;
		}
		#endif

		std::cout << "\tUnadjusted Function Points: " << CalculateUnadjustedFunctionPoints(Pattern) << std::endl;
		std::cout << "\tValue Adjustment Factor: " << CalculateValueAdjustmentFactor() << std::endl;
		std::cout << "\tFunction Point Count: " << CalculateFunctionPointCount(Pattern) << std::endl;
		std::cout << std::endl;
	}
}

void FunctionPointAnalysisStatistic::FunctionPointAnalysisStatistic::CSVExport(std::string FileName){
	std::ofstream File;
	File.open(FileName, std::ios::app);

	File << IO::CSVPrintLine(NUMBER_OF_CSV_ENTRIES, "PatterName", "UFP", "VAF", "FPC");

	for(HPCParallelPattern* Pattern : PatternGraph::GetInstance() -> GetAllPatterns()){
		File << IO::CSVPrintLine(
				NUMBER_OF_CSV_ENTRIES,
				Pattern -> GetPatternName(),
				CalculateUnadjustedFunctionPoints(Pattern),
				CalculateValueAdjustmentFactor(),
				CalculateFunctionPointCount(Pattern)
		);
	}

	File.close();
}


int FunctionPointAnalysisStatistic::CalculateUnadjustedFunctionPoints(HPCParallelPattern* Pattern){
	int UnadjustedFunctionPoints = 0;

	for(auto& FunctionPoint : Pattern -> GetFunctionPoints())
		UnadjustedFunctionPoints += FunctionPoint -> GetWeight();

	return (UnadjustedFunctionPoints);
}
double FunctionPointAnalysisStatistic::CalculateValueAdjustmentFactor(){
	static std::vector<int> GeneralSystemCharacteristics = {
			4,	//DataCommunications
			5,	//DistributedDataProcessing
			4,	//Performance
			2,	//HeavilyUsedConfiguration
			0,	//TransactionRate
			0,	//OnlineDataEntry
			0,	//EndUserEfficiency
			0,	//OnlineUpdate
			5,	//ComplexProcessing
			1,	//Reusability
			0,	//InstallationEase
			0,	//OperationalEase
			5,	//MultipleSites
			0	//FacilitateChange
	};

	int ValueAdjustmentWeight = 0;

	for(int Characteristic : GeneralSystemCharacteristics)
		ValueAdjustmentWeight += Characteristic;

	return ((ValueAdjustmentWeight * VALUE_ADJUSTMENT_FACTOR_PERCENT) + VALUE_ADJUSTMENT_FACTOR_OFFSET);
}

double FunctionPointAnalysisStatistic::CalculateFunctionPointCount(HPCParallelPattern* Pattern){
	return (CalculateUnadjustedFunctionPoints(Pattern) * CalculateValueAdjustmentFactor());
}
