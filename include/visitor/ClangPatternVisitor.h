#pragma once

#include "PatternGraph.h"
#include "HPCPatternInstrASTTraversal.h"
#include "visitor/PatternGraphNodeVisitor.h"
#include "metric/fpa/PrettyPrinter.h"

#define PatternMap std::map<clang::CallExpr*, PatternCodeRegion*>

/**
 * The ClangPatternVisitor acts as an adapter between clangs AST visitor and PInTs pattern visitor.<br>
 * Each pattern is associated with two call expressions, representing the Pattern_Begin and Pattern_End
 * functions. This visitor traverses through the AST. Whenever a call expression is encountered, that matches
 * a Pattern_Begin, the Visit methods of the corresponding pattern are called. Analogously, when visiting an
 * expression matching a Pattern_End, the respective EndVisit methods are called.<br>
 * This ensures that the Visit and EndVisit methods are executed in the correct order.
 * @tparam Derived
 */
template <typename Derived> class ClangPatternVisitor : public PatternGraphNodeVisitor, public clang::RecursiveASTVisitor<Derived>{
	private:
		clang::SourceManager& SourceManager;

		bool Equals(clang::SourceLocation Source, clang::SourceLocation Target){
			//Might be overkill and Source==Target may be enough,
			//But I want to avoid undocumented sideeffects when possible
			clang::FullSourceLoc FullSource(Source, SourceManager);
			clang::FullSourceLoc FullTarget(Target, SourceManager);
			//#TODO May cause issues if a line consists of multiple statements
			return (FullSource == FullTarget);
		}

		bool Equals(clang::CallExpr* CallExpression, PatternCodeRegion* PatternCodeRegion){
			return (
					Equals(CallExpression -> getBeginLoc(), PatternCodeRegion -> GetStartLoc()) ||
					Equals(CallExpression -> getEndLoc(), PatternCodeRegion -> GetEndLoc())
			);
		}

		bool IsPatternEnd(clang::CallExpr* Node, PatternCodeRegion* PatternCodeRegion){
			clang::FunctionDecl* Callee;
			if((Callee = Node -> getDirectCallee()) == NULL)
				return (false);

			std::string FunctionName = Callee -> getNameInfo().getName().getAsString();

			if(FunctionName != PATTERN_END_CXX_FNNAME && FunctionName != PATTERN_END_C_FNNAME)
				return (false);

			//#TODO Compare the argument of the call expression with the parameters of the code region
			return (Equals(Node, PatternCodeRegion));
		}

		bool IsPatternBegin(clang::CallExpr* Node, PatternCodeRegion* PatternCodeRegion){
			clang::FunctionDecl* Callee;
			if((Callee = Node -> getDirectCallee()) == NULL)
				return (false);

			std::string FunctionName = Callee -> getNameInfo().getName().getAsString();

			if(FunctionName != PATTERN_BEGIN_CXX_FNNAME && FunctionName != PATTERN_BEGIN_C_FNNAME)
				return (false);

			//#TODO Compare the argument of the call expression with the parameters of the code region
			return (Equals(Node, PatternCodeRegion));
		}

		PatternCodeRegion* GetPatternCodeRegion(clang::CallExpr* Node){
			//#TODO maybe store the code regions in a map with their range as key?
			for(PatternCodeRegion* CodeRegion : PatternGraph::GetInstance() -> GetAllPatternCodeRegions()){
				if(IsPatternBegin(Node, CodeRegion) || IsPatternEnd(Node, CodeRegion))
					return (CodeRegion);
			}
			return (NULL);
		}

	public:
		ClangPatternVisitor(clang::ASTContext* myContext) : SourceManager(myContext -> getSourceManager()){}

		bool TraverseCallExpr(clang::CallExpr* Node){
			PatternCodeRegion* PatternCodeRegion;

			//Call expression is either a Pattern_Begin or Pattern_End
			if((PatternCodeRegion = GetPatternCodeRegion(Node)) != NULL){
				//Pattern_Begin
				if(IsPatternBegin(Node, PatternCodeRegion)){
					VisitPatternCodeRegion(PatternCodeRegion);
					VisitPatternOccurrence(PatternCodeRegion -> GetPatternOccurrence());
					VisitParallelPattern(PatternCodeRegion -> GetPatternOccurrence() -> GetPattern());
					return (true);
				//Pattern_End
				}else{
					EndVisitParallelPattern(PatternCodeRegion -> GetPatternOccurrence() -> GetPattern());
					EndVisitPatternOccurrence(PatternCodeRegion -> GetPatternOccurrence());
					EndVisitPatternCodeRegion(PatternCodeRegion);
					return (true);
				}
			}
			//Continue traversal if it isn't a Pattern_Begin or Pattern_End
			return (clang::RecursiveASTVisitor<Derived>::TraverseCallExpr(Node));
		};
};
