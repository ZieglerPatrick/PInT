#include "metric/CohesionStatistic.h"
#include "metric/cohesion/ConnectedPatternCounter.h"

#include <iostream>
#include <fstream>

#define NUMBER_OF_CSV_ENTRIES (3)

CohesionStatistic::~CohesionStatistic(){}

void CohesionStatistic::Calculate(){
	for(HPCParallelPattern* Pattern : PatternGraph::GetInstance() -> GetAllPatterns()){
		CohesionCounter CohesionCounter = CalculateConnectivity(Pattern);
		CalculateTCC(CohesionCounter);
		CalculateLCC(CohesionCounter);
		CohesionMap.emplace(Pattern, CohesionCounter);
	}
}

CohesionStatistic::CohesionCounter CohesionStatistic::CalculateConnectivity(HPCParallelPattern* Pattern){
	CohesionCounter CohesionCounter;

	//Root Code Regions
	for(PatternCodeRegion* CodeRegion : Pattern -> GetCodeRegions()){
		ConnectedPatternCounter ConnectedPatternCounter;

		//Children are directly connected
		for(PatternCodeRegion* Child : CodeRegion -> GetOnlyPatternChildren()){
			CohesionCounter.DirectlyConnectedPatterns.emplace(
					Child -> GetPatternOccurrence() -> GetPattern()
			);

			//Grand children are the first indirectly connected patterns
			for(PatternCodeRegion* GrandChild : Child -> GetOnlyPatternChildren()){
				GrandChild -> Accept(&ConnectedPatternCounter);
			}
		}

		//All indirect children are also indirectly connected
		CohesionCounter.IndirectlyConnectedPatterns.insert(
				ConnectedPatternCounter.ConnectedPatterns.begin(),
				ConnectedPatternCounter.ConnectedPatterns.end()
		);
	}

	return (CohesionCounter);
}

void CohesionStatistic::CalculateTCC(CohesionCounter& CohesionCounter){
	double TotalNumberOfPatterns = PatternGraph::GetInstance() -> GetAllPatterns().size();

	CohesionCounter.TCC = CohesionCounter.DirectlyConnectedPatterns.size() / TotalNumberOfPatterns;
}

void CohesionStatistic::CalculateLCC(CohesionCounter& CohesionCounter){
	double TotalNumberOfPatterns = PatternGraph::GetInstance() -> GetAllPatterns().size();
	double NumberOfConnectedPatterns = (CohesionCounter.IndirectlyConnectedPatterns.size() + CohesionCounter.DirectlyConnectedPatterns.size());

	CohesionCounter.LCC = NumberOfConnectedPatterns / TotalNumberOfPatterns;
}

void CohesionStatistic::Print(){
	for(auto MapEntry : CohesionMap){
		std::cout << "Pattern " << MapEntry.first -> GetPatternName() << " has:" << std::endl;
		std::cout << "\t" << MapEntry.second.DirectlyConnectedPatterns.size() << " directly connected patterns" << std::endl;
		std::cout << "\t" << MapEntry.second.IndirectlyConnectedPatterns.size() << " indirectly connected patterns" << std::endl;
		std::cout << "\tTCC of " <<MapEntry.second.TCC << std::endl;
		std::cout << "\tLCC of " <<MapEntry.second.LCC << std::endl;
		std::cout << std::endl;
	}
}

void CohesionStatistic::CSVExport(std::string FileName){
	std::ofstream File;
	File.open(FileName, std::ios::app);

	File << IO::CSVPrintLine(NUMBER_OF_CSV_ENTRIES, "PatterName", "TCC", "LCC");

	for(auto MapEntry : CohesionMap){
		File << IO::CSVPrintLine(
				NUMBER_OF_CSV_ENTRIES,
				MapEntry.first -> GetPatternName(),
				MapEntry.second.TCC,
				MapEntry.second.LCC
		);
	}

	File.close();
}
