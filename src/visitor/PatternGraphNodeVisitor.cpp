#include "visitor/PatternGraphNodeVisitor.h"
#include "HPCParallelPattern.h"

void PatternGraphNodeVisitor::VisitPatternCodeRegion(PatternCodeRegion* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}

void PatternGraphNodeVisitor::TraversePatternCodeRegion(PatternCodeRegion* Node){
	for(auto Child : Node -> GetChildren())
		Child -> Accept(this);
}

void PatternGraphNodeVisitor::EndVisitPatternCodeRegion(PatternCodeRegion* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}

void PatternGraphNodeVisitor::HandlePatternCodeRegion(PatternCodeRegion* Node){
	//Treat this as an inheritance visitor
	//i.e. a Pattern Code Region is also a Pattern Occurrence and a Parallel Pattern
	VisitParallelPattern(Node -> GetPatternOccurrence() -> GetPattern());
	VisitPatternOccurrence(Node -> GetPatternOccurrence());
	VisitPatternCodeRegion(Node);

	TraversePatternCodeRegion(Node);

	EndVisitPatternCodeRegion(Node);
	EndVisitPatternOccurrence(Node -> GetPatternOccurrence());
	EndVisitParallelPattern(Node -> GetPatternOccurrence() -> GetPattern());
}

void PatternGraphNodeVisitor::VisitFunctionNode(FunctionNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}
void PatternGraphNodeVisitor::TraverseFunctionNode(FunctionNode* Node){
	VisitedNodes.emplace(Node);
	
	for(auto Child : Node -> GetChildren())
		if(VisitedNodes.find(Child) == VisitedNodes.end())
			Child -> Accept(this);
}
void PatternGraphNodeVisitor::EndVisitFunctionNode(FunctionNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}
void PatternGraphNodeVisitor::HandleFunctionNode(FunctionNode* Node){
	VisitFunctionNode(Node);
	TraverseFunctionNode(Node);
	EndVisitFunctionNode(Node);
}
