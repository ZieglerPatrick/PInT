#pragma once

#include <set>
#include "visitor/PatternOccurrenceVisitor.h"

//Forward declaration due to PatternGraphNode::Accept(PatternGraphNodeVisitor);
class PatternGraphNode;
class PatternCodeRegion;
class FunctionNode;

/**
 * This visitor is used to access all nodes in a given pattern graph.<br>
 * A node may either be a {@link PatternCodeRegion} or a {@link FunctionNode}.
 * The visitor will traverse through those nodes in a top-down fashion and each
 * node in the order they appear in the pattern graph.
 */
class PatternGraphNodeVisitor : public PatternOccurrenceVisitor{
	public:
		virtual void VisitPatternCodeRegion(PatternCodeRegion* Node);
		virtual void TraversePatternCodeRegion(PatternCodeRegion* Node);
		virtual void EndVisitPatternCodeRegion(PatternCodeRegion* Node);
		virtual void HandlePatternCodeRegion(PatternCodeRegion* Node);

		virtual void VisitFunctionNode(FunctionNode* Node);
		virtual void TraverseFunctionNode(FunctionNode* Node);
		virtual void EndVisitFunctionNode(FunctionNode* Node);
		virtual void HandleFunctionNode(FunctionNode* Node);
	private:
		//Function calls may be cyclic. In that case, only visit the first occurrence.
		std::set<PatternGraphNode*> VisitedNodes;
		//Pattern occurrences and parallel patterns may only be visited once.
		std::set<PatternOccurrence*> VisitedPatternOccurrences;
		std::set<HPCParallelPattern*> VisitedParallelPatterns;
}; 
