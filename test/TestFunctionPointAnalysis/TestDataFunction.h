#pragma once
#include <string>

class Person{
	protected:
		int age;
		std::string name;
	
	public:
		Person(int age, std::string name);
		Person(std::string name);
		bool isBirthday();
};

class Student : public Person{
	protected:
		std::string id;

	public:
		Student(std::string name, std::string id);
};

void testInternalLogicalFile();
void testExternalInterfaceFile();
