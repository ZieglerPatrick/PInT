#pragma once

#include "visitor/PatternGraphNodeVisitor.h"
#include <set>

class ConnectedPatternCounter : public PatternGraphNodeVisitor {
	public:
		std::set<HPCParallelPattern*> ConnectedPatterns;
		void VisitParallelPattern(HPCParallelPattern* Node) override;
};
