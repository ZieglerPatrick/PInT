#include "similarity/PatternSequence.h"

std::string PatternSequence::ToString(){
	std::string Result = "";

	Result += "{";

	auto iterator = PatternLabels.begin();
	while(iterator != PatternLabels.end()){
		Result += *iterator;
		iterator++;
		if(iterator != PatternLabels.end())
			Result += " ";
	}

	Result += "}";

	return (Result);
}
