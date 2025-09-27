#include "Student.h"

Student::Student(const std::string& n, int id, double g)
	: name(n), student_id(id), gpa(g) {}

std::string Student::getName() const {
	return name;
}


std::ostream& operator<<(std::ostream& os, const Student& s){
    os << "Name: " << s.name << ", ID: " << s.student_id << ", GPA: " << s.gpa;
    return os;
}
