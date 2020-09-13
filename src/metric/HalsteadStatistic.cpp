#include "metric/HalsteadStatistic.h"
#include "HPCParallelPattern.h"
#include "Helpers.h"

#include <iostream>
#include <fstream>

HalsteadStatistic::~HalsteadStatistic(){}

void HalsteadStatistic::Calculate(){
	for(HPCParallelPattern* Pattern : PatternGraph::GetInstance() -> GetAllPatterns())
		Calculate(Pattern);
}

void HalsteadStatistic::Print(){
	for(auto MapEntry : HalsteadMap){
		std::cout << "Pattern " << MapEntry.first -> GetPatternName() << " has:" << std::endl;
		std::cout <<               "\t#Operators : " << MapEntry.first -> GetNumberOfOperators() << std::endl;
		std::cout <<      "\t#Distinct Operators : " << MapEntry.first -> GetNumberOfDistinctOperators() << std::endl;
		std::cout <<                "\t#Operands : " << MapEntry.first -> GetNumberOfOperands() << std::endl;
		std::cout <<       "\t#Distinct Operands : " << MapEntry.first -> GetNumberOfDistinctOperands() << std::endl;
		std::cout <<       "\tProgram Vocabulary : " << MapEntry.second.Vocabulary << std::endl;
		std::cout <<           "\tProgram Length : " << MapEntry.second.ProgramLength << std::endl;
		std::cout << "\tEstimated Program Length : " << MapEntry.second.EstimatedProgramLength << std::endl;
		std::cout <<                   "\tVolume : " << MapEntry.second.Volume << std::endl;
		std::cout <<               "\tDifficulty : " << MapEntry.second.Difficulty << std::endl;
		std::cout <<                   "\tEffort : " << MapEntry.second.Effort << std::endl;
		std::cout <<            "\tTime Required : " << MapEntry.second.TimeRequiredToProgram << " (sec)" << std::endl;
		std::cout << "\tNumber of Delivered Bugs : " << MapEntry.second.NumberOfDeliveredBugs << std::endl;
		std::cout << std::endl;
	}
}

void HalsteadStatistic::CSVExport(std::string FileName){
	std::ofstream File;
	File.open(FileName, std::ios::app);

	File << IO::CSVPrintLine(
			"PatternName",
			"#Operators",
			"#Distinct Operators",
			"#Operands",
			"#Distinct Operands",
			"Program Vocabulary",
			"Program Length",
			"Estimated Program Length",
			"Volume",
			"Difficulty",
			"Effort",
			"Time Required (sec)",
			"Number of Delivered Bugs"
	);

	for(auto MapEntry : HalsteadMap){
		File << IO::CSVPrintLine(
				MapEntry.first -> GetPatternName(),
				MapEntry.first -> GetNumberOfOperators(),
				MapEntry.first -> GetNumberOfDistinctOperators(),
				MapEntry.first -> GetNumberOfOperands(),
				MapEntry.first -> GetNumberOfDistinctOperands(),
				MapEntry.second.Vocabulary,
				MapEntry.second.ProgramLength,
				MapEntry.second.EstimatedProgramLength,
				MapEntry.second.Volume,
				MapEntry.second.Difficulty,
				MapEntry.second.Effort,
				MapEntry.second.TimeRequiredToProgram,
				MapEntry.second.NumberOfDeliveredBugs
		);
	}

	File.close();
}

void HalsteadStatistic::Calculate(HPCParallelPattern* Pattern){
	HalsteadCounter HalsteadCounter;

	HalsteadCounter.Vocabulary = CalculateProgramVocabulary(Pattern);
	HalsteadCounter.ProgramLength = CalculateProgramLength(Pattern);
	HalsteadCounter.EstimatedProgramLength = CalculateEstimatedProgramLength(Pattern);
	HalsteadCounter.Volume = CalculateVolume(Pattern);
	HalsteadCounter.Difficulty = CalculateDifficulty(Pattern);
	HalsteadCounter.Effort = CalculateEffort(Pattern);
	HalsteadCounter.TimeRequiredToProgram = CalculateTimeRequiredToProgram(Pattern);
	HalsteadCounter.NumberOfDeliveredBugs = CalculateNumberOfDeliveredBugs(Pattern);

	HalsteadMap.emplace(Pattern, HalsteadCounter);
}

int HalsteadStatistic::CalculateProgramVocabulary(HPCParallelPattern* Pattern){
	return (Pattern -> GetNumberOfDistinctOperators() + Pattern -> GetNumberOfDistinctOperands());
}

int HalsteadStatistic::CalculateProgramLength(HPCParallelPattern* Pattern){
	return (Pattern -> GetNumberOfOperators() + Pattern -> GetNumberOfOperands());
}

double HalsteadStatistic::CalculateEstimatedProgramLength(HPCParallelPattern* Pattern){
	return (
			Pattern -> GetNumberOfDistinctOperators() * log2(Pattern -> GetNumberOfDistinctOperators()) +
			Pattern -> GetNumberOfDistinctOperands() * log2(Pattern -> GetNumberOfDistinctOperands())
	);
}
double HalsteadStatistic::CalculateVolume(HPCParallelPattern* Pattern){
	return (CalculateProgramLength(Pattern) * log2(CalculateProgramVocabulary(Pattern)));
}
double HalsteadStatistic::CalculateDifficulty(HPCParallelPattern* Pattern){
	return (
			Pattern -> GetNumberOfDistinctOperators() / 2.0 +
			Pattern -> GetNumberOfOperands() / (static_cast<double>(Pattern -> GetNumberOfDistinctOperands()))
	);
}
double HalsteadStatistic::CalculateEffort(HPCParallelPattern* Pattern){
	return (CalculateDifficulty(Pattern) * CalculateVolume(Pattern));
}

double HalsteadStatistic::CalculateTimeRequiredToProgram(HPCParallelPattern* Pattern){
	return (CalculateEffort(Pattern) / 18.0);
}

double HalsteadStatistic::CalculateNumberOfDeliveredBugs(HPCParallelPattern* Pattern){
	return (pow(CalculateEffort(Pattern), 2.0/3.0) / 3000.0);
}
