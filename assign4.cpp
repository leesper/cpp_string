#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class PolyTerm {
public:
  char sign;
  int coefficient;
  int exponent;
  PolyTerm *next;
  PolyTerm(char sgn, int coeff, int expo);
  void print();
};

PolyTerm::PolyTerm(char sgn, int coeff, int expo) {
  sign = sgn;
  coefficient = coeff;
  exponent = expo;
  next = NULL;
}

void PolyTerm::print() {
  cout << sign << coefficient << "X^" << exponent;
}

class Polynomial {
private:
  PolyTerm *polyHead;
  void dealWithCoeff0();
  int dealWithSum(char sign1, int coeff1, char sign2, int coeff2);
public:
  Polynomial();
  void insertAtBeginning(char sgn, int coeff, int expo);
  void insertAtEnd(char sgn, int coeff, int expo);
  void insertInOrder(char sgn, int coeff, int expo);
  void print();
};

Polynomial::Polynomial() {
  polyHead = NULL;
}

void Polynomial::insertAtBeginning(char sgn, int coeff, int expo) {
  PolyTerm *term = new PolyTerm(sgn, coeff, expo);
  if (polyHead) {
    term->next = polyHead;
  }
  polyHead = term;
}

void Polynomial::insertAtEnd(char sgn, int coeff, int expo) {
  PolyTerm *term = new PolyTerm(sgn, coeff, expo);
  if (!polyHead) {
    polyHead = term;
    return;
  }

  PolyTerm *iter = polyHead;
  while (iter->next) {
    iter = iter->next;
  }
  iter->next = term;
}

void Polynomial::insertInOrder(char sgn, int coeff, int expo) {
  if (!polyHead || polyHead->exponent < expo) {
    insertAtBeginning(sgn, coeff, expo);
    return;
  }

  PolyTerm *prev = polyHead;
  PolyTerm *next = polyHead->next;
  while (next && next->exponent > expo) {
    prev = next;
    next = next->next;
  }

  if (prev->exponent < expo) {
    PolyTerm *term = new PolyTerm(sgn, coeff, expo);
    term->next = prev;
    prev = term;
  } else if (prev->exponent == expo) {
    int sum = dealWithSum(prev->sign, prev->coefficient, sgn, coeff);
    prev->sign = sum >= 0 ? '+' : '-';
    prev->coefficient = sum >= 0 ? sum : -sum;
  } else if (next && next->exponent == expo) {
    int sum = dealWithSum(next->sign, next->coefficient, sgn, coeff);
    next->sign = sum >= 0 ? '+' : '-';
    next->coefficient = sum >= 0 ? sum : -sum;
  } else {
    PolyTerm *term = new PolyTerm(sgn, coeff, expo);
    prev->next = term;
    term->next = next;
  }

  dealWithCoeff0();
}

void Polynomial::print() {
  PolyTerm *iter = polyHead;
  while (iter) {
    iter->print();
    cout << " ";
    iter = iter->next;
  }
  cout << endl;
}

void Polynomial::dealWithCoeff0() {
  if (polyHead->coefficient == 0) {
    polyHead = polyHead->next;
  }

  PolyTerm *prev = polyHead;
  PolyTerm *next = polyHead->next;;

  while (next && next->coefficient != 0) {
    prev = next;
    next = next->next;
  }

  if (next && next->coefficient == 0) {
    prev->next = next->next;
  }
}

int Polynomial::dealWithSum(char sign1, int abs1, char sign2, int abs2) {
  int coeff1 = sign1 == '+' ? abs1 : -abs1;
  int coeff2 = sign2 == '+' ? abs2 : -abs2;

  return coeff1 + coeff2;
}

Polynomial input(string poly) {
  char sign;
  int coeff;
  char x;
  int expo;
  Polynomial polynomial;

  stringstream stream(poly);
  while (stream >> sign >> coeff >> x >> expo) {
    polynomial.insertInOrder(sign, coeff, expo);
  }

  return polynomial;
}

void runPolyTermTests() {
  PolyTerm term1 = PolyTerm('+', 23, 1);
  term1.print();
  cout << endl;

  PolyTerm term2 = PolyTerm('-', 5, 2);
  term2.print();
  cout << endl;

  PolyTerm term3 = PolyTerm('+', 0, 3);
  term3.print();
  cout << endl;
}

void runPolynomialTests() {
  Polynomial poly1 = input("+ 3 x 2 - 8 x 7 + 1 x 5 - 2 x 2 + 1 x 1 - 7 x 0 + 4 x 3");
  poly1.print();

  Polynomial poly2 = input("+7x4-5x6+3x3");
  poly2.print();

  Polynomial poly3 = input("-7x4+5x6-3x3+3x3+1x0");
  poly3.print();
}

int main() {
  cout << "Testing for PolyTerm" << endl;
  runPolyTermTests();

  cout << "Testing for Polynomial" << endl;
  runPolynomialTests();

  Polynomial poly;
  cout << "INPUT: + 3 x 2 - 8 x 7 + 1 x 5 - 2 x 2 + 1 x 1 - 7 x 0 + 4 x 3" << endl;
  poly.insertInOrder('+', 3, 2); poly.print();
  poly.insertInOrder('-', 8, 7); poly.print();
  poly.insertInOrder('+', 1, 5); poly.print();
  poly.insertInOrder('-', 2, 2); poly.print();
  poly.insertInOrder('+', 1, 1); poly.print();
  poly.insertInOrder('-', 7, 0); poly.print();
  poly.insertInOrder('+', 4, 3); poly.print();
  cout << "OUTPUT: - 8 x 7 + 1 x 5 + 4 x 3 + 1 x 2 + 1 x 1 - 7 x 0 " << endl;
}
