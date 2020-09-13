#pragma once

#include "HPCParallelPattern.h"
#include "PatternGraph.h"
#include <vector>
#include <string>
#include <sstream>

/**
 * Has to be redefined here for some godforsaken reasons, otherwise the CSVPrint template complains.
 */
#define CSV_SEPARATOR_CHAR ","

/**
 * GraphSearchDirection for recursive descent.
 */
enum GraphSearchDirection
{
	DIR_Children, DIR_Parents
};

namespace PatternHelpers
{
	extern std::vector<PatternOccurrence*> GetPatternOccurrences(std::vector<PatternCodeRegion*> CodeRegions, bool MakeUnique);
}

namespace GraphAlgorithms
{

	extern void MarkConnectedComponents();

	extern void MarkConnectedComponents(PatternGraphNode* Node, int ComponentID);

	/**
	 * Calculates all parent pattern code regions of the provided code regions.
	 * @param Start The current code region.
	 * @param Parents A reference to the vector where all found parent code regions are  stored in.
	 * @since Sept. 13th 2020
	 * @author Patrick Ziegler
	 */
	extern void FindAllParentPatternCodeRegions(PatternCodeRegion* Start, std::vector<PatternCodeRegion*>& Parents);

	extern void FindParentPatternCodeRegions(PatternCodeRegion* Start, std::vector<PatternCodeRegion*>& Parents, int maxdepth);

	extern void FindChildPatternCodeRegions(PatternCodeRegion* Start, std::vector<PatternCodeRegion*>& Children, int maxdepth);

	extern void FindNeighbourPatternCodeRegions(PatternGraphNode* Current, std::vector<PatternCodeRegion*>& Results, GraphSearchDirection dir, int depth, int maxdepth);
	extern void FindNeighbourPatternCodeRegionss(PatternGraphNode* Current, std::vector<PatternCodeRegion*>& Results, GraphSearchDirection dir, int * depth, int maxdepth);
}

namespace SetAlgorithms
{
	extern std::vector<PatternOccurrence*> GetUniquePatternOccList(std::vector<PatternOccurrence*> PatternOccs);

	extern std::vector<HPCParallelPattern*> GetUniquePatternList(std::vector<HPCParallelPattern*> Patterns);
}

namespace Preconditions
{
	/**
 	 * @brief An easy way to apply sanity checks.
	 * Inspired by the Guava preconditions, this function will check if a given condition is satisfied.
 	 * If it is not, then an exception will be thrown.<br>
 	 * The purpose of this function to catch simple errors inside the code, like modifying array elements
 	 * outside of its range, before they lead to segmentation faults.
 	 *
 	 * @param Condition a condition that is expected to be satisifed.
 	 * @param Exception is thrown when the condition is violated.
 	 * @since September 3rd, 2020
 	 * @author Patrick Ziegler
 	 */
	extern void CheckArgument(bool Condition, std::exception Exception);
}

namespace IO
{
	template<typename Entry> std::string CSVPrint(Entry entry){
		std::stringstream joiner;
		joiner << entry;
		return (joiner.str());
	}

	template<typename First, typename... Rest > std::string CSVPrint(First first, Rest... rest){
		return (CSVPrint(first) + CSV_SEPARATOR_CHAR + CSVPrint(rest...));
	}

	template<typename First, typename... Rest> std::string CSVPrintLine(First first, Rest ... rest){
		return (CSVPrint(first, rest...) + "\n");
	}
}
