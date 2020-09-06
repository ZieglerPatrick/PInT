#pragma once
#include <string>

struct Person{
	Person();
	Person(int age);
	Person(int age, std::string name);
	
	int age;
	std::string name;
	
	void birthday();
	void die();
};

void testInternalLogicalFile();
void testExternalInterfaceFile();
