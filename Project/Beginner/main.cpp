#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Course {
  std::string name;
  double credits;
  double percentageGrade;

  double calculateGradePoints() const {
    if (percentageGrade >= 90)
      return 4.0;
    if (percentageGrade >= 85)
      return 3.7;
    if (percentageGrade >= 82)
      return 3.3;
    if (percentageGrade >= 78)
      return 3.0;
    if (percentageGrade >= 75)
      return 2.7;
    if (percentageGrade >= 72)
      return 2.3;
    if (percentageGrade >= 68)
      return 2.0;
    if (percentageGrade >= 65)
      return 1.7;
    if (percentageGrade >= 62)
      return 1.3;
    if (percentageGrade >= 60)
      return 1.0;
    return 0.0;
  }
};

int main() {
  std::cout << "CGPA Calculator Project Started!" << std::endl;

  int numberOfCourses = 0;
  std::cout << "Enter the number of courses: ";
  std::cin >> numberOfCourses;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::vector<Course> courses;

  for (int i = 0; i < numberOfCourses; ++i) {
    Course currentCourse;
    std::cout << "\nEnter details for Course " << (i + 1) << ":" << std::endl;

    std::cout << "  Name: ";
    std::getline(std::cin, currentCourse.name);

    std::cout << "  Credits: ";
    std::cin >> currentCourse.credits;

    std::cout << "  Percentage Grade (0-100): ";
    std::cin >> currentCourse.percentageGrade;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    courses.push_back(currentCourse);
  }

  std::cout << "\n--- Courses Entered ---" << std::endl;
  for (const auto &course : courses) {
    std::cout << "Name: " << course.name << ", Credits: " << course.credits
              << ", Grade: " << course.percentageGrade << "%"
              << ", Points: " << course.calculateGradePoints() << std::endl;
  }
  std::cout << "----------------------" << std::endl;

  double totalCreditsAttempted = 0.0;
  double totalGradePointsEarned = 0.0;

  for (const auto &course : courses) {
    totalCreditsAttempted += course.credits;
    totalGradePointsEarned += course.credits * course.calculateGradePoints();
  }

  double semesterGPA = 0.0;
  if (totalCreditsAttempted > 0) {
    semesterGPA = totalGradePointsEarned / totalCreditsAttempted;
  }

  std::cout << "\n--- Semester Summary ---" << std::endl;
  std::cout << "Total Credits Attempted: " << totalCreditsAttempted
            << std::endl;
  std::cout << "Total Grade Points Earned: " << totalGradePointsEarned
            << std::endl;
  std::cout << "Semester GPA: " << std::fixed << std::setprecision(2)
            << semesterGPA << std::endl;
  std::cout << "-----------------------" << std::endl;

  double previousTotalCredits = 0.0;
  double previousTotalGradePoints = 0.0;

  std::cout << "\nEnter previous cumulative totals (enter 0 if this is your "
               "first semester):"
            << std::endl;
  std::cout << "  Previous Total Credits Attempted: ";
  std::cin >> previousTotalCredits;
  while (previousTotalCredits < 0) {
    std::cout << "Credits cannot be negative. Please re-enter: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> previousTotalCredits;
  }

  std::cout << "  Previous Total Grade Points Earned: ";
  std::cin >> previousTotalGradePoints;
  while (previousTotalGradePoints < 0) {
    std::cout << "Grade points cannot be negative. Please re-enter: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> previousTotalGradePoints;
  }

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  double cumulativeTotalCredits = previousTotalCredits + totalCreditsAttempted;
  double cumulativeTotalGradePoints =
      previousTotalGradePoints + totalGradePointsEarned;

  double cgpa = 0.0;
  if (cumulativeTotalCredits > 0) {
    cgpa = cumulativeTotalGradePoints / cumulativeTotalCredits;
  }

  std::cout << "\n--- Cumulative Summary ---" << std::endl;
  std::cout << "Cumulative Total Credits: " << cumulativeTotalCredits
            << std::endl;
  std::cout << "Cumulative Total Grade Points: " << cumulativeTotalGradePoints
            << std::endl;
  std::cout << "CGPA: " << std::fixed << std::setprecision(2) << cgpa
            << std::endl;
  std::cout << "-------------------------" << std::endl;

  return 0;
}
