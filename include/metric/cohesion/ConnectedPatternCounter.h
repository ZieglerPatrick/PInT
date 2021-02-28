#pragma once

#include "visitor/PatternGraphNodeVisitor.h"
#include <set>

/**
 * The set of connected patterns consists of all patterns that are reachable
 * from a given node.
 */
class ConnectedPatternCounter : public PatternGraphNodeVisitor {
	public:
		/**
		 * Contains all distinct patterns in the subtree.
		 */
		std::set<HPCParallelPattern*> ConnectedPatterns;

		/**
		 * Includes the visited node to the connected patterns.
		 * @param Node One of the nested patterns of the root node.
		 */
		void VisitParallelPattern(HPCParallelPattern* Node) override;
};
