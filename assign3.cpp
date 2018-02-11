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

// the calculated result
struct Result {
  double straight;
  double overtime;
  int deductions;
  double net;
};

// parse one line of csv, construct employee struct
Employee parseEmployee(string line) {
  Employee emp;
  string wageStr, hoursStr, status;
  stringstream ss(line);
  // get all fields separated by tab
  getline(ss, emp.firstName, '\t');
  getline(ss, emp.lastName, '\t');
  getline(ss, emp.ssn, '\t');
  getline(ss, wageStr, '\t');
  getline(ss, hoursStr, '\t');
  getline(ss, status, '\t');
  // convert string into double and int
  emp.wage = atof(wageStr.c_str());
  emp.hours = atoi(hoursStr.c_str());
  emp.isFullTime = status == "F" ? true : false;
  return emp;
}

// parse TSV file and construct employees
void parseTSV(string tsvFile, Employee emps[]) {
  ifstream ifs(tsvFile.c_str());
  int cnt = 0;
  if (ifs.is_open()) {
    string line;
    while (getline(ifs, line)) {
      emps[cnt++] = parseEmployee(line);
    }
  } else {
    cout << "file " << tsvFile << " not found" << endl;
  }
}

Result calculate(int hours, double wage, bool isFullTime) {
  Result res;
  res.straight = hours <= 40 ? wage * hours : wage * 40;
  res.overtime = hours <= 40 ? 0.0 : (hours - 40) * wage * 1.5;
  res.deductions = isFullTime ? 10 : 0;
  res.net = res.straight + res.overtime - res.deductions;
  return res;
}

void report(Employee emps[], int length) {
  // display headers
  cout << "Name\t" << "SSN\t" << "Wage\t" << "Hours\t" << "Straight\t" << "Overtime\t" << "Deductions\t" << "Status\t" << "Net" << endl;
  // iterate employees, calculate and display all infos.
  for (int i = 0; i < length; i ++) {
    string name = emps[i].firstName + " " + emps[i].lastName;
    string status = emps[i].isFullTime ? "Full Time" : "Part Time";
    Result res = calculate(emps[i].hours, emps[i].wage, emps[i].isFullTime);
    cout << name << '\t'
         << emps[i].ssn << '\t'
         << emps[i].wage << '\t'
         << emps[i].hours << '\t'
         << res.straight << '\t'
         << res.overtime << '\t'
         << res.deductions << '\t'
         << status << '\t'
         << res.net << endl;
  }
}

int main() {
  // parse employee info from csv file
  Employee emps[5];
  parseTSV("employee.tsv", emps);
  // report output info
  report(emps, 5);
  return 0;
}
