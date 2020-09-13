#include "metric/cohesion/ConnectedPatternCounter.h"
#include "HPCParallelPattern.h"

void ConnectedPatternCounter::VisitParallelPattern(HPCParallelPattern* Node){
	this -> ConnectedPatterns.emplace(Node);
}
