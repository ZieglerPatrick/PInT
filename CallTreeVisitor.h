#pragma once

#include <map>
#include <memory>

//Forward declaration due to CallTreeNode::Accept(CallTreeVisitor);
class CallTreeNode;
/**
 * Each source file is handled as an independent translation unit, which are
 * traversed in an arbitrary order. As such, the order in which the call expressions
 * are visited may not match with the order they are called in the source code.
 * This visitor connects those units and traverses the call tree in the correct order.
 */
class CallTreeVisitor{
	public:
		CallTreeVisitor(int myMaximumRecursionDepth);
		virtual ~CallTreeVisitor();

		virtual void VisitRoot(CallTreeNode* Node);
		virtual void TraverseRoot(CallTreeNode* Node);
		virtual void EndVisitRoot(CallTreeNode* Node);
		virtual void HandleRoot(CallTreeNode* Node);

		virtual void VisitFunctionDeclaration(CallTreeNode* Node);
		virtual void TraverseFunctionDeclaration(CallTreeNode* Node);
		virtual void EndVisitFunctionDeclaration(CallTreeNode* Node);
		virtual void HandleFunctionDeclaration(CallTreeNode* Node);

		virtual void VisitPatternBegin(CallTreeNode* Node);
		virtual void TraversePatternBegin(CallTreeNode* Node);
		virtual void EndVisitPatternBegin(CallTreeNode* Node);
		virtual void HandlePatternBegin(CallTreeNode* Node);

		virtual void VisitPatternEnd(CallTreeNode* Node);
		virtual void TraversePatternEnd(CallTreeNode* Node);
		virtual void EndVisitPatternEnd(CallTreeNode* Node);
		virtual void HandlePatternEnd(CallTreeNode* Node);

		virtual void VisitFunctionCall(CallTreeNode* Node);
		virtual void TraverseFunctionCall(CallTreeNode* Node);
		virtual void EndVisitFunctionCall(CallTreeNode* Node);
		virtual void HandleFunctionCall(CallTreeNode* Node);
	private:
		/**
		 * Handles the recursion depth before a call is handled.
		 * If this is the first time the node is called, a new entry in
		 * #RecursionDepth is created and its value is set to 1.
		 * @param Node The node associated with the call.
		 */
		void BeforeCall(CallTreeNode* Node);
		/**
		 * Handles the recursion depth after a call has been handled.
		 * If the depth of the node is 1, then its entry is removed from
		 * #RecursionDepth. Otherwise its value is decreased by 1.
		 * @param Node The node associated with the call.
		 */
		void AfterCall(CallTreeNode* Node);
		/**
		 * Checks if the depth of the node is valid. If is smaller that
		 * #MaximumRecursionDepth, this method returns true, otherwise false.
		 * @param Node The node associated with the call.
		 * @return true, if the node and its childs can be handled.
		 */
		bool CanHandleCall(CallTreeNode* Node);

		/**
		 * Due to recursion, a function may be called an arbitrary amount of time,
		 * causing an infinite regress.
		 */
		int MaximumRecursionDepth;
		/**
		 * Each call tree node is associated with a recursion depth.
		 * A node is only handled, if its corresponding value is lower than
		 * #MaximumRecursionDepth. Otherwise, at the start of the handle function,
		 * the depth is increased by one and decreased again, once the end of the 
		 * function has been reached.
		 */
		std::map<CallTreeNode*, int> RecursionDepth;
};
 
