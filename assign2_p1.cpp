#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

int numberOfWords(string line){
  int count = 0;
  size_t i = 0;
  bool isWord = false;

  for (size_t i = 0; i < line.length(); i++) {
    // use blank, tab and newline characters as separators, all the others are
    // treated as "words"
    if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') {
      isWord = false;
      continue;
    }
    // new word coming
    if (!isWord) {
      isWord = true;
      count++;
    }
  }

  return count;
}

int numberOfSpecials(string line) {
  int count = 0;
  for (size_t i = 0; i < line.length(); i++) {
    if (!isalnum(line[i])) {
      count ++;
    }
  }
  return count;
}

void parseFile(string fname) {
  ifstream ifs(fname.c_str());
  if (ifs.is_open()) {
    string line;
    int lineno = 0; // line number
    while (getline(ifs, line)) {
      cout << ++lineno << ": " << line << endl;
      cout << "characters: " << line.length()
           << " words: " << numberOfWords(line)
           << " specials: " << numberOfSpecials(line)
           << endl;
    }
  } else {
    cout << "file " << fname << " not found" << endl;
  }
}

int main() {
  cout << "Please enter the name of file" << endl;
  string fname;
  cin >> fname;
  parseFile(fname);
  return 0;
}
