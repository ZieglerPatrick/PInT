#include "visitor/CallTreeVisitor.h"
#include "PatternGraph.h"
#include "Helpers.h"

CallTreeVisitor::~CallTreeVisitor(){}


CallTreeVisitor::CallTreeVisitor(int myMaximumRecursionDepth) :
	MaximumRecursionDepth(myMaximumRecursionDepth){
}

//--------------------------------------------------
//
//  Root
//
//--------------------------------------------------

void CallTreeVisitor::VisitRoot(CallTreeNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}
void CallTreeVisitor::TraverseRoot(CallTreeNode* Node){
	auto Children = Node -> GetCallees();

	for(auto Child = Children -> begin() ; Child != Children -> end() ; ++Child)
		Child -> second -> Accept(this);
}
void CallTreeVisitor::EndVisitRoot(CallTreeNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}
void CallTreeVisitor::HandleRoot(CallTreeNode* Node){
	BeforeCall(Node);

	if(CanHandleCall(Node)){
		VisitRoot(Node);
		TraverseRoot(Node);
		EndVisitRoot(Node);
	}

	AfterCall(Node);
}

//--------------------------------------------------
//
//  FunctionDeclaration
//
//--------------------------------------------------

void CallTreeVisitor::VisitFunctionDeclaration(CallTreeNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}
void CallTreeVisitor::TraverseFunctionDeclaration(CallTreeNode* Node){
	auto Children = Node -> GetCallees();

	for(auto Child = Children -> begin() ; Child != Children -> end() ; ++Child)
		Child -> second -> Accept(this);
}
void CallTreeVisitor::EndVisitFunctionDeclaration(CallTreeNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}
void CallTreeVisitor::HandleFunctionDeclaration(CallTreeNode* Node){
	BeforeCall(Node);

	if(CanHandleCall(Node)){
		VisitFunctionDeclaration(Node);
		TraverseFunctionDeclaration(Node);
		EndVisitFunctionDeclaration(Node);
	}

	AfterCall(Node);
}

//--------------------------------------------------
//
//  Pattern Begin
//
//--------------------------------------------------

void CallTreeVisitor::VisitPatternBegin(CallTreeNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}
void CallTreeVisitor::TraversePatternBegin(CallTreeNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
	//Pattern_Begin is not part of the original source code
}
void CallTreeVisitor::EndVisitPatternBegin(CallTreeNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}
void CallTreeVisitor::HandlePatternBegin(CallTreeNode* Node){
	BeforeCall(Node);

	if(CanHandleCall(Node)){
		VisitPatternBegin(Node);
		TraversePatternBegin(Node);
		EndVisitPatternBegin(Node);
	}

	AfterCall(Node);
}

//--------------------------------------------------
//
//  Pattern End
//
//--------------------------------------------------

void CallTreeVisitor::VisitPatternEnd(CallTreeNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}
void CallTreeVisitor::TraversePatternEnd(CallTreeNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
	//Pattern_End is not part of the original source code
}
void CallTreeVisitor::EndVisitPatternEnd(CallTreeNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}
void CallTreeVisitor::HandlePatternEnd(CallTreeNode* Node){
	BeforeCall(Node);

	if(CanHandleCall(Node)){
		VisitPatternEnd(Node);
		TraversePatternEnd(Node);
		EndVisitPatternEnd(Node);
	}

	AfterCall(Node);
}

//--------------------------------------------------
//
//  Function Call
//
//--------------------------------------------------

void CallTreeVisitor::VisitFunctionCall(CallTreeNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}
void CallTreeVisitor::TraverseFunctionCall(CallTreeNode* Node){
	for(CallTreeNode* Declaration : *ClTre -> GetDeclarationVector()){
		if(Declaration -> compare(Node))
			Declaration -> Accept(this);
			//TODO Break? Wouldn't a match only occur once?
	}
}
void CallTreeVisitor::EndVisitFunctionCall(CallTreeNode* Node){
	static_cast<void>(Node); //Avoid unused parameter warning
}
void CallTreeVisitor::HandleFunctionCall(CallTreeNode* Node){
	BeforeCall(Node);

	if(CanHandleCall(Node)){
		VisitFunctionCall(Node);
		TraverseFunctionCall(Node);
		EndVisitFunctionCall(Node);
	}

	AfterCall(Node);
}

//--------------------------------------------------
//
//  Helper
//
//--------------------------------------------------

void CallTreeVisitor::BeforeCall(CallTreeNode* Node){
	auto myRecursionDepth = RecursionDepth.find(Node);

	//The node is isn't in the map -> initialize and set to 1
	if(myRecursionDepth == RecursionDepth.end()){
		RecursionDepth[Node] = 1;
	}else{
		RecursionDepth[Node]++;
	}
}

void CallTreeVisitor::AfterCall(CallTreeNode* Node){
	Preconditions::CheckArgument(
			RecursionDepth.find(Node) != RecursionDepth.end(),
			std::invalid_argument("RecursionDepth does not contain " + Node -> GetID() -> getIdentificationString())
	);

	auto myRecursionDepth = RecursionDepth.find(Node);

	//This is the last instance of the node -> remove entry
	if(myRecursionDepth -> second == 1){
		RecursionDepth.erase(Node);
	}else{
		RecursionDepth[Node]--;
	}
}

bool CallTreeVisitor::CanHandleCall(CallTreeNode* Node){
	Preconditions::CheckArgument(
			RecursionDepth.find(Node) != RecursionDepth.end(),
			std::invalid_argument("RecursionDepth does not contain " + Node -> GetID() -> getIdentificationString())
	);

	return (RecursionDepth.find(Node) -> second < MaximumRecursionDepth);
}
