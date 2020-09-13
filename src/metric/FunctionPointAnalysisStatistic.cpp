#include <metric/fpa/PrettyPrinter.h>
#include "metric/FunctionPointAnalysisStatistic.h"
#include <iostream>
#include <fstream>

#define VALUE_ADJUSTMENT_FACTOR_OFFSET (0.65)
#define VALUE_ADJUSTMENT_FACTOR_PERCENT (0.01)

FunctionPointAnalysisStatistic::~FunctionPointAnalysisStatistic(){}

void FunctionPointAnalysisStatistic::Calculate(){
	for(HPCParallelPattern* Pattern : PatternGraph::GetInstance() -> GetAllPatterns()){
		FunctionPointCounter Counter = Calculate(Pattern);
		FunctionPointMap.emplace(Pattern, Counter);
	}
}

void FunctionPointAnalysisStatistic::Print(){
	for(HPCParallelPattern* Pattern : PatternGraph::GetInstance() -> GetAllPatterns()){
		FunctionPointCounter Counter = FunctionPointMap[Pattern];
		std::cout << "Pattern " << Pattern -> GetPatternName() << " has:" << std::endl;

		#ifdef DEBUG
		for(auto& FunctionPoint : Pattern -> GetFunctionPoints()){
			std::cout << "\t"
					  << FunctionPoint -> GetType()
					  << "{"
					  << std::endl;

			std::cout << "\t\tLabel: "
					  << FunctionPoint -> Label
					  << std::endl;

			printf("\t\t| %5s | %5s | %5s | %10s |\n",
					"#DET",
					"#RET",
					"#FTR",
					"Complexity"
			);

			printf("\t\t| %5d | %5d | %5d | %10s |\n",
					FunctionPoint -> DataElementTypes,
					FunctionPoint -> RecordElementTypes,
					FunctionPoint -> FileTypesReferenced,
					PrettyPrinter::PrintPretty(FunctionPoint -> GetComplexity()).c_str()
			);

			std::cout << "\t}"
					  << std::endl;
		}
		#endif

		std::cout << "\tUnadjusted Function Points: " << Counter.UnadjustedFunctionPoints << std::endl;
		std::cout << "\tValue Adjustment Factor: " << Counter.ValueAdjustmentFactor << std::endl;
		std::cout << "\tFunction Point Count: " << Counter.FunctionPointCount << std::endl;
		std::cout << std::endl;
	}
}

void FunctionPointAnalysisStatistic::FunctionPointAnalysisStatistic::CSVExport(std::string FileName){
	std::ofstream File;
	File.open(FileName, std::ios::app);

	File << IO::CSVPrintLine("PatterName", "UFP", "VAF", "FPC");

	for(HPCParallelPattern* Pattern : PatternGraph::GetInstance() -> GetAllPatterns()){
		FunctionPointCounter Counter = FunctionPointMap[Pattern];
		File << IO::CSVPrintLine(
				Pattern -> GetPatternName(),
				Counter.UnadjustedFunctionPoints,
				Counter.ValueAdjustmentFactor,
				Counter.FunctionPointCount
		);
	}

	File.close();
}

FunctionPointAnalysisStatistic::FunctionPointCounter FunctionPointAnalysisStatistic::Calculate(HPCParallelPattern* Pattern){
	FunctionPointCounter Counter;

	Counter.FunctionPointCount = CalculateUnadjustedFunctionPoints(Pattern);
	Counter.ValueAdjustmentFactor = CalculateValueAdjustmentFactor();
	Counter.UnadjustedFunctionPoints = CalculateFunctionPointCount(Pattern);

	return (Counter);
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
