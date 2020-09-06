#pragma once

#include "HPCParallelPattern.h"
#include "PatternGraph.h"
#include <vector>
#include <string>

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
	/**
	 * @param argc the number of entries
	 * @param entries all row entries
 	 * @since September 4th, 2020
 	 * @author Patrick Ziegler
 	 * return a concatenated row string containing all entries.
	 */
	extern std::string CSVPrintLine(int argc, std::string entries...);
}
