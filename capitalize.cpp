#include <iostream>
#include <cstring>
using namespace std;

char* capitalizeChar(char* c) {
  if (c == NULL) {
    return c;
  }
  bool newWord = false;
  for (int i = 0; i < strlen(c); i++) {
    if (newWord == false && (c[i] >= 'a' && c[i] <= 'z')) {
      c[i] = c[i] + 'A'-'a';
    }

		if ((c[i] >= 'a' && c[i] <= 'z') || (c[i] >= 'A' && c[i] <= 'Z')) {
      newWord = true;
    } else {
      newWord = false;
    }
  }
  return c;
}

string capitalizeStr(string s) {
  bool newWord;
	newWord = false;
	for (int i = 0; i < s.length(); i++) {
		if (newWord == false && (s.at(i) >= 'a' && s.at(i) <= 'z')) {
      s.at(i) = s.at(i) + 'A'-'a';
    } 
		if ((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z')) {
      newWord = true;
    } else {
      newWord = false;
    }
	}
  return s;
}

int main() {
  char chrs1[] = "it is a fine day today";
  string str1 = "it is a fine day today";
  cout << capitalizeChar(chrs1) << endl;
  cout << capitalizeStr(str1) << endl;

  char chrs2[] = "hello world";
  string str2 = "hello world";
  cout << capitalizeChar(chrs2) << endl;
  cout << capitalizeStr(str2) << endl;
}
