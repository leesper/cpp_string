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
  if (!polyHead) {
    polyHead = new PolyTerm(sgn, coeff, expo);
    return;
  }

  PolyTerm *iter = polyHead;
  while (iter->next && iter->next->exponent > expo) {
    iter = iter->next;
  }

  if (!iter->next) {
    if (expo > iter->exponent) {
      PolyTerm *term = new PolyTerm(sgn, coeff, expo);
      term->next = iter;
      iter = term;
    } else if (expo == iter->exponent) {
      int coeff1 = iter->sign == '+' ? iter->coefficient : -iter->coefficient;
      int coeff2 = sgn == '+' ? coeff : -coeff;
      int sum = coeff1 + coeff2;
      iter->coefficient = sum >= 0 ? sum : -sum;
      iter->sign = sum >= 0 ? '+' : '-';
    } else {
      iter->next = new PolyTerm(sgn, coeff, expo);
    }
  } else if (iter->next->exponent == expo) {
    int coeff1 = iter->sign == '+' ? iter->coefficient : -iter->coefficient;
    int coeff2 = sgn == '+' ? coeff : -coeff;
    int sum = coeff1 + coeff2;
    iter->next->coefficient = sum >= 0 ? sum : -sum;
    iter->next->sign = sum >= 0 ? '+' : '-';
  } else {
    PolyTerm *term = new PolyTerm(sgn, coeff, expo);
    term->next = iter->next;
    iter->next = term;
  }
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
}

int main() {
  runPolyTermTests();

  runPolynomialTests();
}
