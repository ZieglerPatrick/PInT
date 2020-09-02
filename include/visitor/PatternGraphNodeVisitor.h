#pragma once

#include <set>
#include "visitor/PatternOccurrenceVisitor.h"

//Forward declaration due to PatternGraphNode::Accept(PatternGraphNodeVisitor);
class PatternGraphNode;
class PatternCodeRegion;
class FunctionNode;

/**
 * This visitor is used to access all nodes in a given pattern graph.<br>
 * Since the nodes are stored as instances of PatternGraphNode, each
 * of these nodes has to implement an Accept method, expecting an instance
 * of this visitor as an argument, to break up the encapsulation.
 */
class PatternGraphNodeVisitor : public PatternOccurrenceVisitor{
	public:
		virtual ~PatternGraphNodeVisitor();
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
}; 
