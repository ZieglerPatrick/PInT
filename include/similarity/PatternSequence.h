#pragma once

#include <set>
#include <string>
#include <memory>

#define PatternSequencePointer std::shared_ptr<PatternSequence>

/**
 * Class that contains a sequence of patterns and similarities to other PatternSequence objects.
 */
class PatternSequence{
	public:
		/**
		 * A collection of all patterns that are contained in this sequence.<br>
		 * Instead of storing the patterns directly, we only keep a string representation.
		 * The advantages of this are two-fold: The label can be chosen depending on the used
		 * similarity criterion. In addition, it also allows us to use the native comparator.
		 * The order in which the patterns occur is of no importance, hence a set is used.
		 */
		std::multiset<std::string> PatternLabels;

		std::string ToString();
};
