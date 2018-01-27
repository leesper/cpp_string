#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
using namespace std;

// the employee info
struct Employee {
  string firstName;
  string lastName;
  string ssn;
  double wage;
  int hours;
  bool isFullTime;
};

// parse one line of csv, construct employee struct
Employee parseEmployee(string line) {
  Employee emp;
  string wageStr, hoursStr, status;
  stringstream ss(line);
  // get all fields separated by comma
  getline(ss, emp.firstName, ',');
  getline(ss, emp.lastName, ',');
  getline(ss, emp.ssn, ',');
  getline(ss, wageStr, ',');
  getline(ss, hoursStr, ',');
  getline(ss, status, ',');
  // convert string into double and int
  emp.wage = atof(wageStr.c_str());
  emp.hours = atoi(hoursStr.c_str());
  emp.isFullTime = status == "F" ? true : false;
  return emp;
}

// parse CSV file and construct employees
vector<Employee> parseCSV(string csvFile) {
  vector<Employee> emps;
  ifstream ifs(csvFile.c_str());
  int lineno = 0;
  if (ifs.is_open()) {
    string line;
    while (getline(ifs, line)) {
      emps.push_back(parseEmployee(line));
    }
  } else {
    cout << "file " << csvFile << " not found" << endl;
  }
  return emps;
}

void report(vector<Employee> employees) {
  // display headers
  cout << "Name\t" << "SSN\t" << "Wage\t" << "Hours\t" << "Straight\t" << "Overtime\t" << "Deductions\t" << "Status\t" << "Net" << endl;
  // iterate employees, calculate and display all infos.
  for (vector<Employee>::iterator it = employees.begin(); it != employees.end(); ++it) {
    string name = it->firstName + " " + it->lastName;
    double straight = it->hours <= 40 ? it->wage * it->hours : it->wage * 40;
    double overtime = it->hours <= 40 ? 0.0 : (it->hours - 40) * it->wage * 1.5;
    int deductions = it->isFullTime ? 10 : 0;
    string status = it->isFullTime ? "Full Time" : "Part Time";
    double net = straight + overtime - deductions;
    cout << name << '\t'
         << it->ssn << '\t'
         << it->wage << '\t'
         << it->hours << '\t'
         << straight << '\t'
         << overtime << '\t'
         << deductions << '\t'
         << status << '\t'
         << net << endl;
  }
}

int main() {
  // parse employee info from csv file
  vector<Employee> employees = parseCSV("employee.csv");
  // report output info
  report(employees);

}
