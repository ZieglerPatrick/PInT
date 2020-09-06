#pragma once

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include "clang/AST/Decl.h"
#include "llvm/Support/Casting.h"

#include "DesignSpaces.h"
#include "PatternGraph.h"

#include "visitor/HPCParallelPatternVisitor.h"
#include "visitor/PatternGraphNodeVisitor.h"
#include "visitor/PatternOccurrenceVisitor.h"

#include "metric/fpa/FunctionPoint.h"
#include "metric/fpa/FunctionPointComparator.h"

/* Forward declarations */
class PatternOccurrence;
class PatternCodeRegion;

/**
 * This class describes a parallel pattern identified by the design space and the pattern name.
 * The pattern name is not the same as the pattern identifier, as only PatternOccurrence can have an identifier.
 * A parallel pattern can have one or multiple PatternOccurrences which are registered in this object.
 */
class HPCParallelPattern
{
public:
	HPCParallelPattern(DesignSpace DesignSp, std::string PatternName);
	
	/**
	 * The entry point for the pattern visitor.
	 * Modification of the original code to include visitors.
	 * 
	 * @param Visitor an instance of the pattern visitor.
	 * @since Sept. 2nd 2020
	 * @author Patrick Ziegler
	 */
	void Accept(HPCParallelPatternVisitor* Visitor);

	void Print();

	void PrintShort();

	void AddOccurrence(PatternOccurrence* Occurrence);

	std::vector<PatternOccurrence*> GetOccurrences();

	std::vector<PatternCodeRegion*> GetCodeRegions();

	std::string GetPatternName() { return this->PatternName; }

	std::string GetDesignSpaceStr() { return DesignSpaceToStr(this->DesignSp); }

	DesignSpace GetDesignSpace() { return DesignSp; }

	int GetTotalLinesOfCode();

	bool Equals(HPCParallelPattern* Pattern);
	/**
	 * @brief Increase operators count by one.
	 * Modification of the original code for the Halstead statistic.
	 *
	 * @since Sept. 4th 2020
	 * @author Patrick Ziegler
	 */
	void IncrementNumberOfOperators();

	/**
	 * @brief Number of operators.
	 * Returns the number of operators according to the Halstead metric.
	 * Modification of the original code for the Halstead statistic.
	 *
	 * @since Sept. 4th 2020
	 * @author Patrick Ziegler
	 * @return the number of operands inside the pattern.
	 */
	int GetNumberOfOperators();

	/**
	 * @brief Increase operands count by one.
	 * Modification of the original code for the Halstead statistic.
	 *
	 * @since Sept. 4th 2020
	 * @author Patrick Ziegler
	 */
	void IncrementNumberOfOperands();

	/**
	 * @brief Number of operands.
	 * Returns the number of operands according to the Halstead metric.
	 * Modification of the original code for the Halstead statistic.
	 *
	 * @since Sept. 4th 2020
	 * @author Patrick Ziegler
	 */
	int GetNumberOfOperands();

	/**
	 * @brief Adds a function point.	 *
	 * @param NewFunctionPoint the function point
	 *
	 * @since Sept. 4th 2020
	 * @author Patrick Ziegler
	 */
	void AddFunctionPoint(FunctionPointPointer NewFunctionPoint);

	/**
	 * @brief Number of unique function points.
	 * Returns the number of distinct function points in the pattern. Two function points
	 * are equal, if and only if they share the same type and label. This may happen when
	 * referring to the same variable multiple time, where each time may be counted as
	 * an independent function point.
	 *
	 * @since Sept. 4th 2020
	 * @author Patrick Ziegler
	 * @return a set containing the unique function points.
	 */
	const std::set<FunctionPointPointer, FunctionPointComparator>& GetFunctionPoints();



private:
	DesignSpace DesignSp;
	std::string PatternName;

	int numberOfOperators = 0;
	int numberOfOperands = 0;
	std::set<FunctionPointPointer, FunctionPointComparator> functionPoints;

	std::vector<PatternOccurrence*> Occurrences;
};



/**
 * The PatternOccurrence is a hypothetical construct that represents a collection for all code regions
 * with the same identifier.
 * It is linked to a unique HPCParallelPattern.
 * Each PatternCodeRegion with this identifier is accessible from this object.
 */
class PatternOccurrence
{
public:
	PatternOccurrence(HPCParallelPattern* Pattern, std::string ID);
	
	/**
	 * The entry point for the pattern visitor.
	 * Modification of the original code to include visitors.
	 * 
	 * @param Visitor an instance of the pattern visitor.
	 * @since Sept. 2nd 2020
	 * @author Patrick Ziegler
	 */
	void Accept(PatternOccurrenceVisitor* Visitor);

	HPCParallelPattern* GetPattern() { return this->Pattern; }

	void Print();

	std::string GetID() { return this->ID; }

	void AddCodeRegion(PatternCodeRegion* CodeRegion) { this->CodeRegions.push_back(CodeRegion); }

	std::vector<PatternCodeRegion*> GetCodeRegions() { return this->CodeRegions; }

	int GetTotalLinesOfCode();

	int GetNumberOfCodeRegions() { return this->CodeRegions.size(); }

	bool Equals(PatternOccurrence* PatternOcc);

private:
	HPCParallelPattern* Pattern;

	std::vector<PatternCodeRegion*> CodeRegions;

	std::string ID;
};

/**
 * This class represents a block of code that is enclosed with the instrumentation calls.
 * It is a node in the pattern tree, hence has children and parents in the tree.
 * A PatternCodeRegion belongs to a PatternOccurrence.
 */
class PatternCodeRegion : public PatternGraphNode
{
public:
	~PatternCodeRegion();
	PatternCodeRegion(PatternOccurrence* PatternOcc);
	
	/**
	 * The entry point for the pattern visitor.
	 * Modification of the original code to include visitors.
	 * 
	 * @param Visitor an instance of the pattern visitor.
	 * @since Sept. 2nd 2020
	 * @author Patrick Ziegler
	 */
	void Accept(PatternGraphNodeVisitor* Visitor);

	PatternOccurrence* GetPatternOccurrence() { return this->PatternOcc; }

	static bool classof(const PatternGraphNode* Node)
	{
		return Node->GetKind() == PatternGraphNode::GNK_Pattern;
	}

	void Print();

	void AddChild(PatternGraphNode* Child);

	void AddParent(PatternGraphNode* Parent);

	void AddOnlyPatternChild(PatternGraphNode* PatChild);

	void AddOnlyPatternParent(PatternGraphNode* PatParent);

	std::vector<PatternGraphNode*> GetChildren() { return this->Children; }

	std::vector<PatternCodeRegion*> GetOnlyPatternChildren() { return this->PatternChildren; }

	std::vector<PatternGraphNode*> GetParents() { return this->Parents; }

	std::vector<PatternCodeRegion*> GetOnlyPatternParents() { return this->PatternParents; }

	void SetFirstLine (int FirstLine);

	void SetLastLine (int LastLine);


	void SetStartSourceLoc(clang::SourceLocation StartLoc);

	void SetEndSourceLoc(clang::SourceLocation EndLoc);

	clang::SourceLocation GetStartLoc();

	clang::SourceLocation GetEndLoc();

	int GetLinesOfCode() { return this->LinesOfCode; }

	std::string GetID() { return this->PatternOcc->GetID(); }

	bool HasNoPatternParents();

	bool HasNoPatternChildren();

	bool isInMain = false;

	void PrintVecOfPattern(std::vector<PatternCodeRegion*> RegionVec);

	void insertCorrespondingCallTreeNode(CallTreeNode* Node){
		CorrespondingCallTreeNodes.push_back(Node);
	}

	std::vector<CallTreeNode*>* getCorrespondingCallTreeNodes(){return &CorrespondingCallTreeNodes;}

	bool isSuitedForNestingStatistics = true;

	/**
	 * @brief The source range.
	 * Modification of the original code for the Function Point Analysis.
	 *
	 * @since Sept. 6th 2020
	 * @author Patrick Ziegler
	 */
	clang::SourceRange GetSourceRange();
private:
	PatternOccurrence* PatternOcc;

	clang::SourceLocation SurLoc;

	clang::SourceLocation StartSLocation;
	clang::SourceLocation EndSLocation;


	std::vector<PatternGraphNode*> Parents;
	std::vector<PatternGraphNode*> Children;
	std::vector<PatternCodeRegion*> PatternParents;
	std::vector<PatternCodeRegion*> PatternChildren;
	std::vector<int> LOCofCallTree;
	int LinesOfCode = 0;

	std::vector<CallTreeNode*> CorrespondingCallTreeNodes;

};



/**
 * The pattern stack is used to keep track of the nesting of patterns and functions.
 */
extern std::vector<PatternCodeRegion*> PatternContext;
/**
	*The OnlyPatternContext only keeps track of the nesting of patterns.
	*/
extern std::vector<PatternCodeRegion*> OnlyPatternContext;

extern std::vector<PatternOccurrence*> OccStackForHalstead;

void AddToPatternStack(PatternCodeRegion* PatternOcc);

void AddToOnlyPatternStack(PatternCodeRegion* PatternCodeReg);

PatternCodeRegion* GetTopPatternStack();

PatternCodeRegion* GetTopOnlyPatternStack();

void RemoveFromPatternStack(std::string ID);

void RemoveFromOnlyPatternStack(std::string ID);

PatternCodeRegion* PatternIDisUsed(std::string ID);
