// student: Yuan Tian
// Assign1_P1
//#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void Problem_1(void);

int main(void)
{
    cout << "Assign1_P1" << endl;
    Problem_1();
    return (0);
}

void Problem_1(void)
{
    cout << "Please input the set of 15 numbers:" << endl;
    string input;
    getline(cin, input);
    stringstream ss(input);

    int cnt = 0;
    int numbers[15];

    int num;
    while (ss >> num) {
      numbers[cnt++] = num;
      if (ss.peek() == ',') {
        ss.ignore();
      }
    }

    int min = 0, sum = 0;
    float count = 0.0;
    for (int i = 0; i < 15; i++)
    {
        if (numbers[i] < min) {
          min = numbers[i];
        }
        switch (numbers[i] > 0) {
            case 1:
              sum = sum + numbers[i];
              count = count + 1.0;
              break;
        }
    }

    double avg = sum / count;
    cout << "The lowest of the input numbers: "<<min<<endl;
    cout << "The average of the input numbers greater than 0: "<<avg<<endl;
}
