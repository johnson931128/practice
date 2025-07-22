#pragma once

#include <string>
#include <iostream>

class Student {
private:
	std::string name;
	int student_id;
	double gpa;
public:
	Student(const std::string& n, int id, double g);
	std::string getName() const;

	friend std::ostream& operator<<(std::ostream& os, const Student& s);

};
